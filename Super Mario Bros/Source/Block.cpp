#include "../Header/Block.h"

Block::Block()
{

}

sf::Vector2f Block::getOverlap(const sf::FloatRect& obj) const
{
	// 1 -> block , 2 -> obj
	float x1, x2, y1, y2;

	x1 = m_AABB.left + (m_AABB.width / 2);
	y1 = m_AABB.top + (m_AABB.height / 2);
	
	x2 = obj.left + (obj.width / 2);
	y2 = obj.top + (obj.height / 2);

	sf::Vector2f delta{ std::abs(x1 - x2), std::abs(y1 - y2)};
	sf::Vector2f overlap;
	overlap.x = (m_AABB.width / 2) + (obj.width / 2) - delta.x;
	overlap.y = (m_AABB.height / 2) + (obj.height / 2) - delta.y;
	
	return overlap;
}

void Block::setAABB(const sf::FloatRect& block, const sf::Vector2f gbounds)
{
	m_AABB = block;
	m_AABB.left = gbounds.x;
	m_AABB.top = gbounds.y;
}

sf::FloatRect Block::getAABB() const
{
	return m_AABB;
}