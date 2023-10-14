#pragma once

#include "Global.h"



// Set movement of entities
class CTransform
{
public:
	sf::Vector2f pos{ 0.0,0.0 };
	sf::Vector2f velocity{ 0.0,0.0 };

	CTransform(const sf::Vector2f& p, const sf::Vector2f& v)
		: pos(p),
		velocity(v) {}
};



// Set scores or points
class CScore
{
public:
	int score;
	CScore(int score)
		:score(score) {}
};



// Set Inputs
class CInput
{
public:
	bool up{ false };
	bool down{ false };
	bool left{ false };
	bool right{ false };
	bool space{ false };

	CInput() {}
};



// Set Collision radius for entities
class CCollision
{
public:
	float radius{ 0 };

	CCollision(float r)
		: radius(r) {}
};