#include "Player.h"

#include <iostream>

Player::Player()
{
    m_PosX = -100;
    m_PosY = -100;

    canspawnbullet=false;

    menu=false;

    m_VelX = 0;
    m_VelY = 0;

    Start=0;
}

void Player::handleEvent( SDL_Event& e,SDL_Renderer* m_Renderer )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LSHIFT: PLAYER_VEL -= 4; m_VelY ==0; m_VelX=0; if (downdown == true){m_VelY += PLAYER_VEL;} if (updown == true){m_VelY -= PLAYER_VEL;} if (rightdown == true) {m_VelX+=PLAYER_VEL;} if (leftdown == true) {m_VelX-=PLAYER_VEL;} break;
            case SDLK_DOWN: m_VelY += PLAYER_VEL; downdown= true; break;
            case SDLK_LEFT: m_VelX -= PLAYER_VEL; leftdown=true; break;
            case SDLK_RIGHT: m_VelX += PLAYER_VEL; rightdown = true; break;
            case SDLK_UP: m_VelY -= PLAYER_VEL; updown= true; break;
            case SDLK_z: canspawnenemy=true; canspawnbullet=true; m_PosX=SCREEN_WIDTH/2 - 150; m_PosY=SCREEN_HEIGHT/1.2; Start=SDL_GetTicks(); break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LSHIFT: PLAYER_VEL += 4; m_VelY ==0; m_VelX=0; if (downdown == true){m_VelY += PLAYER_VEL;} if (updown == true){m_VelY -= PLAYER_VEL;} if (rightdown == true) {m_VelX+=PLAYER_VEL;} if (leftdown == true) {m_VelX-=PLAYER_VEL;} break;
            case SDLK_UP: m_VelY = 0; updown=false; if (downdown == true){m_VelY += PLAYER_VEL;} break;
            case SDLK_DOWN: m_VelY = 0; downdown=false; if (updown == true){m_VelY -= PLAYER_VEL;} break;
            case SDLK_LEFT: m_VelX = 0; leftdown=false; if (rightdown == true) {m_VelX+=PLAYER_VEL;} break;
            case SDLK_RIGHT: m_VelX = 0; rightdown=false; if (leftdown == true) {m_VelX-=PLAYER_VEL;} break;
        }
    }
}

void Player::handleBullet(SDL_Renderer* m_Renderer)
{
    Current_Time=SDL_GetTicks();

    if (canspawnbullet==true && Current_Time>Start+5128 &&  Current_Time > Last_Time+200) {

        Bullet* m_bullet = new Bullet();
        m_bullet->load(BULLET_WIDTH ,BULLET_HEIGHT,"bullet.png");
        m_bullet->loadImg(m_Renderer);
        m_bullet->SetPos(this->m_PosX + m_width/2  - BULLET_WIDTH/2,this->m_PosY);
        m_bullet->set_x_val(8);
        m_bullet->set_is_move(true);
        Last_Time=Current_Time;
        LASER=Mix_LoadWAV("Laser.wav");
        Mix_VolumeChunk(LASER, 0);
        Mix_PlayChannel( -1, LASER, 0 );

        m_bullet_list.push_back(m_bullet);
    }

    for (int i=0;i< m_bullet_list.size();i++)
    {
        Bullet* m_bullet = m_bullet_list.at(i);

        if( m_bullet!=NULL)
        {
            if (m_bullet->get_is_move()==true)
            {
                m_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                m_bullet->render(m_Renderer);
            }
            else
            {
                m_bullet_list.erase(m_bullet_list.begin() + i);
                if(m_bullet!=NULL)
                {
                    m_bullet->free();
                    delete m_bullet;
                    m_bullet=NULL;
                }
            }
        }
    }
}


void Player::move ()
{
    //Move  left or right
    m_PosX += m_VelX;

    //If went too far to the left or right
    if( ( m_PosX < 0 ) || ( m_PosX + m_width > SCREEN_WIDTH -300 ) )
    {
        //Move back
        m_PosX -= m_VelX;
    }

    //Move  up or down
    m_PosY += m_VelY;

    //If  went too far up or down
    if( ( m_PosY < 320 ) || ( m_PosY + m_height > SCREEN_HEIGHT ) )
    {
        //Move back
        m_PosY -= m_VelY;
    }

    if (is_alive==false){
        m_PosY = 2000;
        canspawnbullet=false;
    }
}
