#ifndef GAME_H
#define GAME_H
#include "Texture.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <math.h>
#include <fstream>


using namespace std;

class Game
{
public:
    Game();

    // simply set the running variable to true
    void init() ;
    void loadmedia();
    void draw();
    void handleEvents();
    void close ();
    void enemy ();
    void IsCollisionPlayerToEnemy();
    void IsCollisionEnemyToPlayer();
    void FindPlayer();
    void HandleScore();
    void HandleHighScore();
    void HandleEnding();
    bool running()
        {
            return m_Running;
        }

    SDL_Event e;
    private:

    bool ending;
    bool ending_once;
    int FinalScore;
    int CurrentTime;
    int LastTime;
    bool isenemy;
    bool PlayerBullet_to_Enemy;
    bool EnemyBullet_to_Player;
    float angle;
    int enemy_health;
    int Current_enemy_health;
    bool menu ;
    int score ;
    int StartTime;
    int Currentscore;
    string strCurrentscore;


    bool m_Running;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

};

#endif // GAME_H
