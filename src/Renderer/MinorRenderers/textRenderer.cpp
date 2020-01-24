#include "textRenderer.hpp"
#include "Renderer/renderer.hpp"
#include "quadRenderer.hpp"
#include "Renderer/API/shader.hpp"
#include "Renderer/Shaders/embeddedShaders.hpp"
#include <GL/glew.h>
#include <stb_truetype.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

namespace ph {

namespace {
	struct CharacterQuad
	{
		IntRect textureRect;
		sf::Vector2f pos;
		sf::Vector2f size;
		float advance;
	};

	CharacterQuad getCharacterQuad(const stbtt_bakedchar *chardata, int charIndex, sf::Vector2f* pos, int textureWidth)
	{
		const stbtt_bakedchar* bc = chardata + charIndex;
		CharacterQuad q;
		q.pos.x = std::floorf(pos->x + bc->xoff + 0.5f);
		q.pos.y = std::floorf(pos->y + bc->yoff + 0.5f);
		unsigned short width = bc->x1 - bc->x0;
		unsigned short height = bc->y1 - bc->y0;
		q.size = {float(width), float(height)};
		q.textureRect = {bc->x0, textureWidth - bc->y0 - height, width, height};
		q.advance = bc->xadvance;
		return q;
	}
}

void TextRenderer::init()
{
	mTextShader.init(shader::textSrc());
	mTextShader.initUniformBlock("SharedData", 0);
}

void TextRenderer::shutDown()
{
	mTextShader.remove();
	mFontHolder.clear();
}

void TextRenderer::beginDebugDisplay()
{
	mDebugTextPosition = {1150.f, 0.f};

	if(mWasDebugTextDrawnInLastFrame)
		Renderer::submitQuad(nullptr, nullptr, &sf::Color::Black, nullptr, {1120.f, 0.f}, {500.f, 300.f}, 5, 0.f, {}, ProjectionType::gui);
	mWasDebugTextDrawnInLastFrame = false;
}

void TextRenderer::drawText(const char* text, const char* fontFilename, sf::Vector2f position, float size, sf::Color color,
                            unsigned char z, ProjectionType projectionType)
{
	drawTextInternal(text, fontFilename, position, size, color, z, projectionType);
}

void TextRenderer::drawDebugText(const char* text, const char* fontFilename, float size, float upMargin, float downMargin, sf::Color color)
{
	mWasDebugTextDrawnInLastFrame = true;
	mDebugTextPosition.y += upMargin;
	drawTextInternal(text, fontFilename, mDebugTextPosition, size, color, 0, ProjectionType::gui);
	mDebugTextPosition.y += downMargin + size;
}

void TextRenderer::drawTextInternal(const char* text, const char* fontFilename, sf::Vector2f position, float fontSize,
                                    sf::Color color, unsigned char z, ProjectionType projectionType)
{
	SizeSpecificFontData& data = mFontHolder.getSizeSpecificFontData(fontFilename, fontSize);

	position.y += fontSize;

	while(*text) {
		if(*text >= '!' && *text <= '~') {
			auto cq = getCharacterQuad(data.charactersData, *text - 32, &position, data.textureAtlas->getWidth());
			Renderer::submitQuad(data.textureAtlas.get(), &cq.textureRect, &color, &mTextShader, cq.pos, cq.size, z, 0.f, {}, projectionType);
			position.x += cq.advance;
		}
		else {
			position.x += fontSize;
		}
		++text;
	}
}

void TextRenderer::drawTextArea(const char* text, const char* fontFilename, sf::Vector2f worldPos, const float textAreaWidth,
                                TextAligment aligment, float fontSize, sf::Color textColor, unsigned char z, ProjectionType projectionType)
{
	SizeSpecificFontData& data = mFontHolder.getSizeSpecificFontData(fontFilename, fontSize);

	worldPos.y += fontSize;

	std::vector<CharacterQuad> rowCharacters;
	sf::Vector2f localPos;
	unsigned wordsInCurrentRow = 0;
	unsigned lettersInCurrentWord = 0;

	auto getXOffset = [textAreaWidth, aligment, fontSize](float mostRightCharacterPosX)
	{
		switch(aligment)
		{
			case ph::TextAligment::left: return 0.f;
			case ph::TextAligment::center: return (textAreaWidth - mostRightCharacterPosX) / 2.f;
			case ph::TextAligment::right: return textAreaWidth - mostRightCharacterPosX + fontSize;
			default: break;
		}
	};

	auto submitCharacterToQuadRenderer = [=](sf::Vector2f localPos, sf::Vector2f size, IntRect textureRect)
	{
		Renderer::submitQuad(data.textureAtlas.get(), &textureRect, &textColor, &mTextShader,
			localPos + worldPos, size, z, 0.f, {}, projectionType);
	};

	while(1)
	{
		if(*text >= '!' && *text <= '~') 
		{
			auto cq = getCharacterQuad(data.charactersData, *text - 32, &localPos, data.textureAtlas->getWidth());
			localPos.x += cq.advance;
			rowCharacters.emplace_back(cq);
			++lettersInCurrentWord;
		}
		else if(*text == ' ' || localPos.x > textAreaWidth)
		{
			while(*(text + 1) == ' ') {
				++text;
				localPos.x += fontSize;
			}
			localPos.x += fontSize;
			if(localPos.x > textAreaWidth) 
			{
				if(wordsInCurrentRow > 0)
				{
					auto firstNotFittingLetterInTheRow = rowCharacters.begin() + rowCharacters.size() - lettersInCurrentWord;
					const float xOffset = getXOffset(firstNotFittingLetterInTheRow->pos.x);
					for(auto it = rowCharacters.begin(); it != firstNotFittingLetterInTheRow; ++it) {
						it->pos.x += xOffset;
						submitCharacterToQuadRenderer(it->pos, it->size, it->textureRect);
					}
					rowCharacters.clear();
					text -= lettersInCurrentWord + 1;
				}
				else
				{
					const float xOffset = getXOffset(localPos.x);
					for(auto& cq : rowCharacters) {
						cq.pos.x += xOffset;
						submitCharacterToQuadRenderer(cq.pos, cq.size, cq.textureRect);
					}
					rowCharacters.clear();
				}
				localPos.x = 0;
				localPos.y += fontSize;
				wordsInCurrentRow = 0;
			}
			else 
			{
				++wordsInCurrentRow;
			}
			lettersInCurrentWord = 0;
		}

		text++;

		if(*(text) == '\0')
		{
			if(!rowCharacters.empty())
			{
				const float xOffset = getXOffset(localPos.x);
				for(auto& cq : rowCharacters) {
					cq.pos.x += xOffset;
					submitCharacterToQuadRenderer(cq.pos, cq.size, cq.textureRect);
				}
				rowCharacters.clear();
			}
			break;
		}
	}
}

}

