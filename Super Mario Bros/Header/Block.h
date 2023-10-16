#pragma once

#include "Global.h"

class Block
{
	sf::FloatRect m_AABB;

public:
	Block();

	std::shared_ptr<CCollision> cCollision;

	sf::FloatRect getAABB() const;
	sf::Vector2f getOverlap(const sf::FloatRect& obj) const;
	void setAABB(const sf::FloatRect& block, const sf::Vector2f gBound);

};