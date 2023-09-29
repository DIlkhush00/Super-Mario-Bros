#include "../Header/Game.h"

int main()
{
    Game* game = new Game();    // setup the game

    game->run();                // run the game

    delete game;                // and free the memory :)

    return 0;
}