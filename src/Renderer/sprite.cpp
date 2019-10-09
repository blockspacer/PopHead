#include "sprite.hpp"

namespace ph {

Sprite::Sprite(const Texture& texture, const std::string& name)
	:mTexture(texture)
{
	auto vbo = VertexBufferHolder::getGlobalInstance().getRectangleVertexBuffer(name, texture.getWidth(), texture.getHeight(), false);
	auto ibo = IndexBufferHolder::getGlobalInstance().getRectangleIndexBuffer("rectangle");
	mVertexArray.setVertexBuffer(vbo, VertexBufferLayout::position2_texCoords2);
	mVertexArray.setIndexBuffer(ibo);
}

}
