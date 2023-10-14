#include "../Header/Mario.h"

Mario::Mario()
{

}

void Mario::marioInit(const std::string& path)
{
	if (!m_marioTexture.loadFromFile(path))
	{
		std::cout << "Mario Texture load - Failed" << std::endl;
	}
	m_mario.setTexture(m_marioTexture);
	m_mario.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Mario::drawMario(sf::RenderWindow& window)
{
	window.draw(m_mario);
}

void Mario::setStartPos(sf::Vector2f& start)
{
	m_mario.setPosition(start.x, start.y);
}