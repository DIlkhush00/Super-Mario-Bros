#pragma once

#include "Global.h"

class Map
{
	tmx::Map m_map;
	unsigned int m_tile_width{ 0 };
	unsigned int m_tile_height{ 0 };
	unsigned int m_tilesPerRow{ 0 };		// total tiles in a row
	unsigned int m_tilesPerCol{ 0 };		// total tiles in a column

	std::vector<tmx::Tileset>	m_tilesetVec;
	std::vector<sf::Texture>	m_textureVec;
	std::vector<sf::Sprite>		m_tileSpriteVec;


	void load(const std::string& path);		// loading the map from the given path
	void loadTexture();						// loading all the textures
	void mapInit();							// setting up the game map

	// drawing tile
	void drawTile(const sf::Texture& tileTexture, unsigned int tile_x, unsigned int tile_y, unsigned int t_width, unsigned int t_height, unsigned int row, unsigned int col);

public:
	Map();

	void loadMap(const std::string& path);	// preparing the map - load(), loadTexture(), mapInit()

	void drawMap(sf::RenderWindow& window); // drawing the map on the screen
};

