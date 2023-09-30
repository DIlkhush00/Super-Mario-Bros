#include "../Header/Game.h"
#include "../Header/Map.h"



Game::Game()
{
	setup();
}


void Game::run()
{
	// running the game

	while (m_running)
	{
		inputEvents();
		gameRendering();
	}
}


void Game::setup()
{
	// Setting up Game Window
	m_window.create(sf::VideoMode(1000, 640), "Super Mario Bros");

	// Setting up Font - should wrap this in a function
	const std::string font_path = "Assets/Fonts/ShortBaby.ttf";
	if (m_font.loadFromFile(font_path))
	{
		std::cout << "Font Loading - success" << std::endl;
	}
	else
	{
		std::cout << "Font loading - Fail" << std::endl;
	}

	// Setting up coordinations
	m_coords.setFont(m_font);
	m_coords.setString("0 , 0");

	// Setting up Game Map
	const std::string path = "Assets/Maps/level-1.tmx"; // will change
	m_gameMap.loadMap(path);
	
}



void Game::setPaused(bool pause)
{
	m_paused = !pause;
}



void Game::gameRendering()
{
	m_window.clear();

	m_gameMap.drawMap(m_window);
	m_window.draw(m_coords);

	m_window.display();
}



void Game::inputEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_running = false;
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_running = false;
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				setPaused(m_paused);
			}
			break;

		default:
			break;
		}

	}
}