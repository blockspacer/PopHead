#include "bilbord.hpp"

namespace ph { 
 
Bilbord::Bilbord(const sf::Texture& stayingBilbordTexture, const sf::Texture& lyingBilbordTexture)
	:GameObject("bilbord")
	,mSprite(stayingBilbordTexture)
	,mStayingBilbordTexture(stayingBilbordTexture)
	,mLyingBilbordTexture(lyingBilbordTexture)
{
}

void Bilbord::drawCurrent(sf::RenderTarget& renderTarget, const sf::RenderStates states) const
{
	renderTarget.draw(mSprite, states);
}

}  
