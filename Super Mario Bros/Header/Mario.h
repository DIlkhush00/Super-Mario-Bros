#pragma once

#include "Global.h" // does global is necessary?

class Mario
{
	sf::Texture		m_marioTexture;
	sf::Vector2f	m_marioStart;
	sf::Sprite		m_mario;

	void marioInit(const std::string& path);
	void setStartPos(sf::Vector2f& startPos);

public:

	void drawMario(sf::RenderWindow& window);
	void moveMario(sf::Vector2f directions);
	const sf::FloatRect getAABB();

	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput>		cInput;
	std::shared_ptr<CTransform> cTransform;

	Mario();

	friend class Map;
};

