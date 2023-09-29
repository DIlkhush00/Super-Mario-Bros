#pragma once
#include "Global.h"
#include "Map.h"

class Game
{
	Map					m_gameMap ;
	sf::RenderWindow	m_window  ;
	sf::Font			m_font    ;
	sf::Text			m_coords  ;
	bool				m_paused{false} ; 
	bool				m_running{true} ;



	void setup();					// setting up window, font, text, and map...for now
	void setPaused(bool pause);		// set the pause value

	void gameRendering();			// and render the game

public:
	Game();

	void run();
};

