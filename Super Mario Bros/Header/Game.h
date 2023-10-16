#pragma once
#include "Global.h"
#include "Map.h"
#include "Mario.h"

class Game
{
	Map					m_gameMap ;
	sf::RenderWindow	m_window  ;
	sf::Font			m_font    ;
	sf::Text			m_coords  ;
	sf::View			m_view    ;
	bool				m_paused{false} ; 
	bool				m_running{true} ;

	sf::Clock m_clock;
	const float m_frameTime = 1.0f / 60.0f;

	Mario	m_mario;

	void setup();					// setting up window, font, text, and map...for now
	void setPaused(bool pause);		// set the pause value

	void gameRendering();			// and render the game
	void inputEvents();				// handles events like pausing, closing the game etc..

	void playerMovement();
	void gameCollision();
	void gameUpdate();

public:
	Game();

	void run();
};

