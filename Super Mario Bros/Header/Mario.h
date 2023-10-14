#pragma once

#include "Global.h" // does global is necessary?

class Mario
{
	sf::Texture		m_marioTexture;
	sf::Vector2f	m_marioStart;
	sf::Sprite m_mario;



public:
	void marioInit(const std::string& path);
	void drawMario(sf::RenderWindow& window);
	void setStartPos(sf::Vector2f& startPos);

	Mario();
};

