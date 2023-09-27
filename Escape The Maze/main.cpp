#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 640), "SFML works!");
    tmx::Map map;
    if (map.load("Assets/shadow_dungeon.tmx")) {
        std::cout << "tmx file  - Success! \n";
    }
    else
    {
        std::cout << "tmx file  - Failure \n";
    }

    const auto& tilesets = map.getTilesets();
    std::vector<sf::Texture> tilesetTextures;
    for (const auto& tileset : tilesets)
    {
        //read out tile set properties, load textures etc...
        sf::Texture texture;
        if (texture.loadFromFile(tileset.getImagePath()))
        {
            texture.setSmooth(false);
            tilesetTextures.push_back(texture);
            std::cout << "Texture loaded successfully \n";
        }
        else
        {
            // Handle the error if the texture fails to load
            std::cout << "Error... in texture loading \n";
        }
    }


    int tile_width = map.getTileSize().x;
    int tile_height = map.getTileSize().y;
    int tilesPerRow = map.getTileCount().x;
    int tilesPerCol = map.getTileCount().y;

    const tmx::Tileset& tileset = tilesets[0];
    const sf::Texture& tilesetTexture = tilesetTextures[0];
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }

        window.clear();

        // handling tilemap logic


        const auto& layers = map.getLayers();
        for (auto& layer : layers)
        {
            if (layer->getType() == tmx::Layer::Type::Tile)
            {
                if (layer->getName() == "bg_bricks")
                {
                    std::cout << "bg_bricks check \n";
                }
                if (layer->getName() == "fg_bricks")
                {
                    std::cout << "fg_bricks check \n";
                }
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

                auto& tiles = tileLayer.getTiles();

                int index = 0;

                for (int i = 0; i < tilesPerCol; i++)
                {
                    for (int j = 0; j < tilesPerRow; j++)
                    {

                        // Calculate the position of the tile
                        sf::Vector2f position(tile_width * j, tile_height * i);

                        // Calculate the texture rectangle for the tile
                        int gid = tileset.getFirstGID();
                        int tileID = tiles[index].ID - gid; // Calculate the relative tile ID
                        
                        std::cout << "Gid & tileID:  " << gid << " " << tileID << " and layer: " << layer->getName() << std::endl;

                        int tilesr = tilesetTexture.getSize().x / tileset.getTileSize().x;
                        int x = (tileID % tilesr) * tileset.getTileSize().x;
                        int y = (tileID / tilesr) * tileset.getTileSize().y;

                        /*sf::IntRect textureRect((tileID % tilesPerRow) * tile_width, (tileID / tilesPerRow) * tile_height, tile_width, tile_height);*/
                        sf::IntRect textureRect(x, y, tileset.getTileSize().x, tileset.getTileSize().y);

                        // Setup the Sprite
                        sf::Sprite tileSprite(tilesetTexture);
                        tileSprite.setTextureRect(textureRect);
                        tileSprite.setPosition(position);
                        // Render the tile sprite to the window
                        window.draw(tileSprite);
                        index++;
                    }
                }
            }

        }
        


        window.display();
    }

    return 0;
}