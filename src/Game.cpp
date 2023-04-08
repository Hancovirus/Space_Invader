#include "Game.h"


Player m_player ;
Enemy m_enemy ;

Texture m_Background;
Texture m_Menuscreen;
Texture m_End;
Texture Health;
Texture NumScore;
Texture HighScore;
Texture NumHighScore;
Texture m_StatWall;
Texture e_health;
Texture NumEnemyHealth;
Texture NumFinalScore;
Texture TextFinalScore;

Mix_Chunk* BGM=NULL;
Mix_Chunk* EndingSong=NULL;
Mix_Chunk* MenuMusic=NULL;

TTF_Font* Font=NULL;

Game::Game()
{
    m_Window=NULL;
    m_Renderer=NULL;

    menu = false;

    score = 1000;
    Currentscore=0;

    enemy_health=1000;
    Current_enemy_health=1000;

    LastTime=0;

    ending = false;
    ending_once = false;
}

void Game::init()
{
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
	    m_Window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( m_Window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );

		}
		else
		{
			//Create renderer for window
			m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_PRESENTVSYNC );
			if( m_Renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );

			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( m_Renderer,255,255,255,255);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
				}
                 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				}

			}
		}
	}
    m_Running = true;
}

void Game::draw()
{
    SDL_RenderClear(m_Renderer);

    m_Background.render( 0, 0,m_Renderer );
    m_Menuscreen.render( 0, 0,m_Renderer );
    m_StatWall.render( 432, 0,m_Renderer );
    m_End.render( 0, 0,m_Renderer );

    Health.renderText(m_Renderer, 442, 100, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    NumScore.renderText(m_Renderer, 635, 100, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    HighScore.renderText(m_Renderer, 442, 135, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    NumHighScore.renderText(m_Renderer, 635, 135, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    e_health.renderText(m_Renderer, 442, 10, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    NumEnemyHealth.renderText(m_Renderer, 635, 10, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    NumFinalScore.renderText(m_Renderer, 270, 500, NULL, 0.0 , NULL, SDL_FLIP_NONE );
    TextFinalScore.renderText(m_Renderer, 75, 500, NULL, 0.0 , NULL, SDL_FLIP_NONE );

    m_player.draw(m_Renderer);
    m_enemy.draw(m_Renderer);
}

void Game::loadmedia()
{
    m_Background.loadFromFile( "background.png" ,m_Renderer);
    m_player.load(29,31,"rockettest.png");
    m_enemy.load(432,264,"enemy.png");
    m_Menuscreen.loadFromFile ("MenuTest.png" ,m_Renderer);
    m_StatWall.loadFromFile("StatWall.png", m_Renderer);

    MenuMusic=Mix_LoadWAV("MenuMusic.wav");
    Mix_Volume(-1, 25);
    Mix_PlayChannel( -1, MenuMusic, -1 );
}

void Game::enemy()
{
    if (Current_enemy_health!=enemy_health)
    {
        Current_enemy_health=enemy_health;
        NumEnemyHealth.free();
        string strCurrent_enemy_health=to_string(Current_enemy_health);
        SDL_Color textColor = { 255, 255, 255 };
        NumEnemyHealth.loadFromRenderedText( strCurrent_enemy_health, textColor, Font, m_Renderer );
    }
    isenemy=m_player.get_enemy();
    if (isenemy)
    {
        if (!menu)
        {
            Mix_FreeChunk(MenuMusic);
            MenuMusic=NULL;
            strCurrentscore=to_string(Currentscore);
            Font = TTF_OpenFont( "8Bit.ttf", 25 );
            SDL_Color textColor = { 255, 255, 255 };
            Health.loadFromRenderedText( "Health", textColor, Font, m_Renderer );
            HighScore.loadFromRenderedText( "HighScore", textColor, Font, m_Renderer );
            e_health.loadFromRenderedText( "EnemyHealth", textColor, Font, m_Renderer );
            NumScore.loadFromRenderedText( strCurrentscore, textColor, Font, m_Renderer );
            string strCurrent_enemy_health=to_string(Current_enemy_health);
            NumEnemyHealth.loadFromRenderedText( strCurrent_enemy_health, textColor, Font, m_Renderer );
            BGM=Mix_LoadWAV("BGMTest2.wav");
            Mix_VolumeChunk(BGM, 1000);
            StartTime=SDL_GetTicks();
            m_enemy.setstart(StartTime);
            Mix_PlayChannel( -1, BGM, -1 );
            menu=true;
        }
        m_Menuscreen.free();
        m_enemy.loadImg(m_Renderer);
        m_enemy.SetPos(m_enemy.m_PosX ,m_enemy.m_PosY);
        m_enemy.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        m_enemy.render(m_Renderer);
        m_enemy.handleBullet(m_Renderer);
    }
}

void Game::IsCollisionPlayerToEnemy()
{

    vector<Bullet*> player_bullet_arr=m_player.GetBulletList();
    for(int i=0;i<player_bullet_arr.size();i++)
    {
        Bullet*p_bullet=player_bullet_arr.at(i);
        if(p_bullet!=NULL)
        {
            int EnemyX=m_enemy.GetPosX();
            int EnemyY=m_enemy.GetPosY();
            int BulletX=p_bullet->GetPosX();
            int BulletY=p_bullet->GetPosY();
            if (EnemyX+432>=BulletX && BulletX+2>=EnemyX && EnemyY + 267 >= BulletY && BulletY - 260 >= EnemyY) {
                PlayerBullet_to_Enemy= true;
            } else {PlayerBullet_to_Enemy=false;}
            if (PlayerBullet_to_Enemy==true)
            {
                m_enemy.losehealth();
                enemy_health=m_enemy.health;
                if (m_player.get_is_alive())
                {
                    score+=5;
                }
            }
        }
    }
}

void Game::IsCollisionEnemyToPlayer()
{
    vector<Bullet*> enemy_bullet_arr=m_enemy.GetBulletList();
    CurrentTime=SDL_GetTicks();
    for(int i=0;i<enemy_bullet_arr.size();i++)
    {
        Bullet*p_bullet=enemy_bullet_arr.at(i);
        if(p_bullet!=NULL)
        {
            int PlayerX=m_player.GetPosX();
            int PlayerY=m_player.GetPosY();
            int BulletX=p_bullet->GetPosX();
            int BulletY=p_bullet->GetPosY();
            int BulletW=p_bullet->GetPosW();
            int BulletH=p_bullet->GetPosH();
            if (PlayerX + 16>=BulletX && BulletX+BulletW>=PlayerX + 14 && PlayerY + 16 >= BulletY && BulletY + BulletH >= PlayerY + 14)
            {
                EnemyBullet_to_Player= true;
            }
            else
            {
                EnemyBullet_to_Player=false;
            }
            if (EnemyBullet_to_Player && CurrentTime>=LastTime+500)
            {
                LastTime=CurrentTime;
                score-=100;
            }
            if (score<=0)
            {
                score=0;
                m_player.set_is_alive(false);
            }
        }
    }
}

void Game::HandleScore()
{
    if (Currentscore!=score)
    {
        Currentscore=score;
        NumScore.free();
        strCurrentscore=to_string(Currentscore);
        SDL_Color textColor = { 255, 255, 255 };
        NumScore.loadFromRenderedText( strCurrentscore, textColor, Font, m_Renderer );
    }
}

void Game::HandleHighScore()
{
	fstream HighScoreFromFile;
	string highscore;

	HighScoreFromFile.open("High_Score.txt",ios::in);
	HighScoreFromFile >> highscore;
	SDL_Color textColor = { 255, 255, 255 };
	NumHighScore.loadFromRenderedText( highscore, textColor, Font, m_Renderer );

    if (!m_player.get_is_alive() || enemy_health<=0 )
    {

        int OldHighScore=stoi(highscore);
        FinalScore=(1000-enemy_health)*100 + score;
        if (FinalScore>OldHighScore)
        {
            fstream HighScoreToFile;
            HighScoreToFile.open("High_Score.txt",ios::out);
            HighScoreToFile << FinalScore;
        }
        string FinalScorestr = to_string(FinalScore);
        NumFinalScore.loadFromRenderedText( FinalScorestr, textColor, Font, m_Renderer );
        TextFinalScore.loadFromRenderedText( "Final Score:", textColor, Font, m_Renderer );
        ending=true;
        m_enemy.kill();
    }
}

void Game::FindPlayer()
{
    float PlayerX= (float) m_player.GetPosX();
    float PlayerY= (float) m_player.GetPosY();
    m_enemy.Player_PosX=PlayerX;
    m_enemy.Player_PosY=PlayerY;
}

void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT )
        {
            m_Running = false;
        }
        m_player.handleEvent( e,m_Renderer);
    }
    m_player.handleBullet(m_Renderer);
    m_player.move();
    SDL_RenderPresent(m_Renderer);
}

void Game::HandleEnding()
{
    if(ending)
    {
        if (!ending_once)
        {
            if (!m_player.get_is_alive())
            {
                m_End.loadFromFile("Lose.png", m_Renderer);
                ending_once=true;
                Mix_FreeChunk(BGM);
                BGM=NULL;
                EndingSong=Mix_LoadWAV("Lose.wav");
                Mix_Volume(-1, 30);
                Mix_PlayChannel( -1, EndingSong, -1 );
            }
            else if (enemy_health<=0)
            {
                m_End.loadFromFile("Win.png", m_Renderer);
                ending_once=true;
                Mix_FreeChunk(BGM);
                BGM=NULL;
                EndingSong=Mix_LoadWAV("Victory.wav");
                Mix_Volume(-1, 30);
                Mix_PlayChannel( -1, EndingSong, -1 );
                m_player.set_is_alive(false);
            }
        }
    }
}

void Game::close()
{
    //Destroy window
	SDL_DestroyRenderer( m_Renderer );
	SDL_DestroyWindow( m_Window );
	m_player.clean();
	m_enemy.clean();
	Mix_FreeChunk(EndingSong);
    EndingSong=NULL;

	m_Window = NULL;
	m_Renderer = NULL;

    //Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
