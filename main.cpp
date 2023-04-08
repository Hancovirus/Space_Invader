#include "Game.h"



Game* g_game = NULL;

int main(int argc, char* argv[])
{
    g_game = new Game();
    g_game->init();
    g_game->loadmedia();



    while(g_game->running())
    {
        g_game->draw();
        g_game->enemy();
        g_game->handleEvents();
        g_game->IsCollisionPlayerToEnemy();
        g_game->IsCollisionEnemyToPlayer();
        g_game->FindPlayer();
        g_game->HandleScore();
        g_game->HandleHighScore();
        g_game->HandleEnding();
    }
    g_game->close();
    return 0;
}
