#pragma once

#include "Global.h"



// Set movement of entities
class CTransform
{
public:
	float gravity{ 0 };
	float speed{ 0 };
	sf::Vector2f pos{0.0f, 0.0f};

	CTransform(const float g, const float s, const sf::Vector2f p)
		: gravity(g),
		  speed(s) ,
		  pos(p) {}
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
	float x{ 0 };
	float y{ 0 };
	float width{ 0 };
	float height{ 0 };

	CCollision(float x, float y, float w, float h)
		: x(x), 
		  y(y),
		  width(w),
		  height(h) {}
};