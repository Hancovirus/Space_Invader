#include "Bullet.h"

Bullet::Bullet()
{
    x_val=0;
    y_val=0;
    is_move= false;

    Last_Time=0;


}


void Bullet::HandleMove(const int& x_border, const int& y_border)
{
    m_PosY -= x_val;
    if (m_PosY <214)
    {
      is_move = false;
    }
}

void Bullet::HandleMoveEnemyPattern0(const int& x_border, const int& y_border)
{
    m_PosW=BLUEBULLET_WIDTH;
    m_PosH=BLUEBULLET_HEIGHT;
    m_PosX += x_val*sin(angle*3.14/180);
    m_PosY += x_val*cos(angle*3.14/180);
    if (m_PosY >y_border || m_PosY <-10 || m_PosX > x_border - 300 || m_PosX<-10)
    {
        m_PosX=-200;
        m_PosY=-200;
        is_move = false;
    }
}

void Bullet::HandleMoveEnemyPattern1(const int& x_border, const int& y_border)
{
    m_PosW=EBULLET_WIDTH;
    m_PosH=EBULLET_HEIGHT;
    m_PosX += x_val*sin(angle*3.14/180);
    m_PosY += x_val*cos(angle*3.14/180);
    if (m_PosY >y_border || m_PosY <-100 || m_PosX > x_border - 300 || m_PosX<-100)
    {
        m_PosX=-200;
        m_PosY=-200;
        is_move = false;
    }
}

void Bullet::HandleMoveEnemyPattern2(const int& x_border, const int& y_border)
{
    if (turret)
    {
        m_PosW=SPHERE_WIDTH;
        m_PosH=SPHERE_HEIGHT;
        Current_Time=SDL_GetTicks();
        angle =  (Current_Time/10)%360;
        m_PosX = ENEMY_WIDTH/2 - SPHERE_WIDTH/2 +  x_val*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*cos(angle*3.14/180);
        m_PosY = SCREEN_HEIGHT/2 - SPHERE_WIDTH/2 + 100 + x_val*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*sin(angle*3.14/180);
        if (Time_appear<=Current_Time-200)
        {
            m_PosX=-200;
            m_PosY=-200;
            is_move = false;
        }
    }else {
        m_PosW=EBULLET_WIDTH;
        m_PosH=EBULLET_HEIGHT;
        m_PosX += x_val*sin(angle*3.14/180);
        m_PosY += x_val*cos(angle*3.14/180);
        if (m_PosY >y_border || m_PosY <-100 || m_PosX > x_border - 300 || m_PosX<-100)
        {
            m_PosX=-200;
            m_PosY=-200;
            is_move = false;
        }
    }
}

void Bullet::HandleMoveEnemyPattern3(const int& x_border, const int& y_border)
{
    m_PosW=EBULLET_WIDTH;
    m_PosH=EBULLET_HEIGHT;
    m_PosX -= x_val*cos(angle*3.14/180);
    m_PosY += x_val*sin(angle*3.14/180);
    if (m_PosY >y_border + 500|| m_PosY <-100 || m_PosX > x_border - 300 || m_PosX<-100)
    {
        m_PosX=-200;
        m_PosY=-200;
        is_move = false;
    }
}

void Bullet::HandleMoveEnemyPatternFinal(const int& x_border, const int& y_border)
{
    if (turret)
    {
        m_PosW=SPHERE_WIDTH;
        m_PosH=SPHERE_HEIGHT;
        Current_Time=SDL_GetTicks();
        angle =  (Current_Time/10)%360;
        m_PosX = ENEMY_WIDTH/2 - SPHERE_WIDTH/2 +  x_val*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*cos(angle*3.14/180);
        m_PosY = SCREEN_HEIGHT/2 - SPHERE_WIDTH/2 + 100 + x_val*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*sin(angle*3.14/180);
        if (Time_appear<=Current_Time-200)
        {
            m_PosX=-200;
            m_PosY=-200;
            is_move = false;
        }
    }else {
        m_PosW=EBULLET_WIDTH;
        m_PosH=EBULLET_HEIGHT;
        m_PosX += x_val*sin(angle*3.14/180);
        m_PosY += x_val*cos(angle*3.14/180);
        if (m_PosY >y_border || m_PosY <-100 || m_PosX > x_border - 300 || m_PosX<-100)
        {
            m_PosX=-200;
            m_PosY=-200;
            is_move = false;
        }
    }
}

void Bullet::DestroyPrevious()
{
    m_PosX=-200;
    m_PosY=-200;
    is_move = false;
}

 void Bullet::loadImg(SDL_Renderer* m_Renderer)
 {
     bullet_img.loadFromFile(m_textureID, m_Renderer);
 }

 void Bullet::render (SDL_Renderer* m_Renderer)
 {
     bullet_img.render(m_PosX, m_PosY, m_Renderer);

 }

 void Bullet::free()
 {
     bullet_img.free();
 }
