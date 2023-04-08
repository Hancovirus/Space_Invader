#ifndef PLAYER_H
#define PLAYER_H

#include "SDL_mixer.h"
#include "Object.h"
#include "Bullet.h"
class Player:public Object
{
    public:
        int PLAYER_VEL = 6;
        bool leftdown=false;
        bool downdown=false;
        bool rightdown=false;
        bool updown=false;

        Player();
        void handleEvent( SDL_Event& e,SDL_Renderer* m_Renderer );
        void move();
        void handleBullet(SDL_Renderer* m_Renderer);
        vector <Bullet*> GetBulletList ()const {return  m_bullet_list;};
        int b_PosX;
        int b_PosY;
        void set_is_alive(bool p_is_alive) {is_alive=p_is_alive;};
        void set_reset(bool p_reset) {reset=p_reset;};

        bool get_enemy() {return canspawnenemy;};
        bool get_is_alive() {return is_alive;};
        bool get_reset() {return reset;};

        void set_PosX(float p_PosX) {m_PosX=p_PosX;};
        void set_PosY(float p_PosY) {m_PosY=p_PosY;};

        float GetPosX() const {return m_PosX;};
        float GetPosY() const {return m_PosY;};

        bool get_menu() {return menu;};

        bool is_alive=true;

        bool canspawnenemy=false;

        bool menu;

        bool reset=false;

    private:
        int m_VelX;
        int m_VelY;
        int Start;

        int Current_Time;
        int Last_Time;

        bool canspawnbullet;

        vector <Bullet*> m_bullet_list;

        Mix_Chunk* LASER=NULL;
};

#endif // PLAYER_H
