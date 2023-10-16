#include "../Header/Game.h"
#include "../Header/Map.h"
#include "../Header/Block.h"
#include "../Header/Global.h"

Game::Game()
{
	setup();
}


void Game::run()
{	
	// Running the game
	while (m_running)
	{
		gameUpdate();

		inputEvents();
		playerMovement();
		gameCollision();
		gameRendering();
	}
}

void Game::gameUpdate()
{
	// Ensuring 60fps
	sf::Time deltaTime = m_clock.restart();
	if (deltaTime.asSeconds() < m_frameTime)
	{
		sf::sleep(sf::seconds(m_frameTime - deltaTime.asSeconds()));
	}

	// Displaying coordinates
	float top  = m_mario.getAABB().top;
	float left = m_mario.getAABB().left;

	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2) << left <<", "<< top;

	m_coords.setString(stream.str());

	/*m_view.setCenter(sf::Vector2f(250.0f, 125.0f));*/

	m_view.setCenter(m_mario.getAABB().left, m_mario.getAABB().top);
}

void Game::setup()
{
	// Setting up Game Window
	m_window.create(sf::VideoMode(1000, 700), "Super Mario Bros");

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
	m_coords.scale(0.5f, 0.5f);

	// Setting up Game Map
	const std::string path = "Assets/Maps/level-1.0.tmx"; // will change
	m_gameMap.loadMap(path);
	

	// Camera setup 
	m_view.setSize(sf::Vector2f(500.0f, 250.0f));
	

	// Player setup
	const std::string playerTex = "Assets/Player/mario-small.png";
	m_gameMap.playerInit(playerTex, m_mario);
}



void Game::setPaused(bool pause)
{
	m_paused = !pause;
}



void Game::gameRendering()
{
	m_window.clear();
	m_window.setView(m_view);

	m_gameMap.drawMap(m_window);
	m_mario.drawMario(m_window);
	m_window.draw(m_coords); 

	m_window.display();
}


void Game::gameCollision()
{
	for (const Block& block : m_gameMap.solid_blocks)
	{
		
		sf::FloatRect block_gbounds = block.getAABB();
		sf::FloatRect mario_gbounds = m_mario.getAABB();

		if (block_gbounds.intersects(mario_gbounds))
		{
			std::cout << "Collision detected!" << std::endl;

			// Collision is detected between mario and the block
			sf::Vector2f overlap = block.getOverlap(mario_gbounds);
			// Collision - horizontally & vertically
			if (((mario_gbounds.left + mario_gbounds.width > block_gbounds.left)
				&& (mario_gbounds.left < block_gbounds.left + block_gbounds.width))
				|| ((mario_gbounds.top + mario_gbounds.height > block_gbounds.top)
				&& (mario_gbounds.top < block_gbounds.top + block_gbounds.height)))
			{
				// Collision from top
				if ((mario_gbounds.top + mario_gbounds.height >= block_gbounds.top)
					&& (mario_gbounds.top <= block_gbounds.top))
				{
					m_mario.cTransform->pos.y -= overlap.y;
				}

				// Collision from bottom
				else if ((block_gbounds.top + block_gbounds.height >= mario_gbounds.top)
					&& (block_gbounds.top + block_gbounds.height <= mario_gbounds.top + mario_gbounds.height))
				{
					m_mario.cTransform->pos.y += overlap.y;
				}

				// Collision from left
				if ((mario_gbounds.left + mario_gbounds.width >= block_gbounds.left)
					&& (mario_gbounds.left <= block_gbounds.left))
				{
					m_mario.cTransform->pos.x -= overlap.x;
				}

				// Collision from right
				else if ((block_gbounds.left + block_gbounds.width >= mario_gbounds.left)
					&& (block_gbounds.left + block_gbounds.width <= mario_gbounds.left + mario_gbounds.width))
				{
					m_mario.cTransform->pos.x += overlap.x;
				}

				m_mario.moveMario(m_mario.cTransform->pos);
				break;
			}
		}
	}
}


void Game::playerMovement()
{
	sf::Vector2f dir(0.0, 0.0);
	if (m_mario.cInput->up)
	{
		dir.x = 0.0;
		dir.y =  - m_mario.cTransform->speed;
	}
	if (m_mario.cInput->down)
	{
		dir.x = 0.0;
		dir.y = m_mario.cTransform->speed;
	}
	if (m_mario.cInput->left)
	{
		dir.x = - m_mario.cTransform->speed;
		dir.y = 0.0;
	}
	if (m_mario.cInput->right)
	{
		dir.x = m_mario.cTransform->speed;
		dir.y = 0.0;
	}
	m_mario.cTransform->pos += dir;
	m_mario.moveMario(m_mario.cTransform->pos);
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
			else if (event.key.code == sf::Keyboard::W)
			{
				m_mario.cInput->up = true;
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				m_mario.cInput->left = true;
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				m_mario.cInput->right = true;
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				m_mario.cInput->down = true;
			}
			break;

		
		case sf::Event::KeyReleased:
		{
			if (event.key.code == sf::Keyboard::A) { m_mario.cInput->left = false; }
			else if (event.key.code == sf::Keyboard::D) { m_mario.cInput->right = false; }
			else if (event.key.code == sf::Keyboard::W) { m_mario.cInput->up = false; }
			else if (event.key.code == sf::Keyboard::S) { m_mario.cInput->down = false; }

			break;
		}
		default:
			break;
		}

	}
}