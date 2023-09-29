#include "../Header/Map.h"
#include "../Header/Global.h"

using uint  =  unsigned int;
using ull   =  unsigned long long int;
using ll    =  long long int;



Map::Map()
{
}



void Map::loadMap(const std::string& map_path)
{
    load(map_path);
    loadTexture();
    mapInit();
}



void Map::load(const std::string& path)
{
	if (m_map.load(path))
	{
		std::cout << " Map is Successfully loaded! " << std::endl;
	}
	else
	{
		std::cout << "Map loading failed!" << std::endl;
	}
}



void Map::loadTexture()
{
    m_tilesetVec = m_map.getTilesets();

    for (const auto& tileset : m_tilesetVec)
    {
        sf::Texture texture;
        if (texture.loadFromFile(tileset.getImagePath()))
        {
            m_textureVec.push_back(texture);
            std::cout << "Texture loaded successfully \n";
        }
        else
        {
            std::cout << "Error... in texture loading \n";
            break;
        }
    }
}



void Map::mapInit()
{
    m_tile_width = m_map.getTileSize().x;   // tile width
    m_tile_height = m_map.getTileSize().y;  // tile height
    m_tilesPerRow = m_map.getTileCount().x; // tiles per row
    m_tilesPerCol = m_map.getTileCount().y; // tiles per col

    const auto& layerVec = m_map.getLayers();

    for (auto& layer : layerVec)
    {

        // for each layer of objects
        //if (layer->getType() == tmx::Layer::Type::Object)
        //{
        //    if (layer->getName() == "start_end")
        //    {
        //        std::cout << "start_end check!" << std::endl;
        //        const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
        //        const auto& objects = objectLayer.getObjects();
        //        
        //        for (const auto& object : objects)
        //        {
        //            //do stuff with object properties
        //            tmx::FloatRect points = object.getAABB();
        //            start_end.push_back(points);
        //        }
        //    }
        //}

        // for each layer of tiles
        if (layer->getType() == tmx::Layer::Type::Tile)
        {
            const tmx::TileLayer& tileLayer = layer->getLayerAs<tmx::TileLayer>();

            auto& tiles = tileLayer.getTiles();

            uint index = 0; // end result should be m_tilesPerCol * m_tilesPerRow

            for (uint col = 0; col < m_tilesPerCol; col++)
            {
                for (uint row = 0; row < m_tilesPerRow; row++)
                {
                    // if the tile id is 0  -> there is no tile to draw
                    // if there is empty tile then we need to keep it transparent
                    // if we skip this step then that tile will be filled with default color (maybe grey)

                    if (tiles[index].ID == 0) {
                        index++;
                        continue;
                    }

                    // after getting the tile -> what texture it'll take? and from which tileset
                    // to calculate this we have tile id and each tileset's GID
                    // find the difference of both and apply the below formulas
                    // and we get the tile texture position in the tileset texture
                    // so we got what we need to draw a tile on the screen -> Draw the tile

                    for (const auto& tileset : m_tilesetVec)
                    {
                        for (const auto& texture : m_textureVec)
                        {
                            uint first_GID = tileset.getFirstGID();
                            ll rel_tileID = tiles[index].ID - first_GID;

                            uint tileset_width = tileset.getTileSize().x;
                            uint tileset_height = tileset.getTileSize().y;
                            ull tex_tilesPerRow = texture.getSize().x / tileset_width;

                            // Formulas
                            uint tile_x = (rel_tileID % tex_tilesPerRow) * tileset_width;
                            uint tile_y = (rel_tileID / tex_tilesPerRow) * tileset_height;

                            // draw the tile
                            drawTile(texture, tile_x, tile_y, tileset_width, tileset_height, row, col);
                        }
                    }

                    index++;
                }
            }
        }

    }
}



void Map::drawTile(const sf::Texture& tileTexture, uint tile_x, uint tile_y, uint t_width, uint t_height, uint row, uint col)
{

    // Setup the Sprite
    sf::Sprite tileSprite;

    // setting up the texture
    tileSprite.setTexture(tileTexture);

    // Setup texture rectangle
    sf::IntRect textureRect(tile_x, tile_y, t_width, t_height);
    tileSprite.setTextureRect(textureRect);

    // Setting the position of the tile
    sf::Vector2f position(m_tile_width * row, m_tile_height * col);
    tileSprite.setPosition(position);

    // store the tiles into a vector
    m_tileSpriteVec.push_back(tileSprite);
}



void Map::drawMap(sf::RenderWindow& window)
{
    // draw the tile on the screen

    for (const auto& tileSprite : m_tileSpriteVec)
    {
        window.draw(tileSprite);
    }
}