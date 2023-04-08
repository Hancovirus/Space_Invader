#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_WIDTH 432
#define ENEMY_HEIGHT 264

#include "Object.h"
#include "Bullet.h"

class Enemy:public Object
{
    public:
        Enemy();

        void HandleMove(const int& x_border, const int& y_border);

        void loadImg(SDL_Renderer* m_Renderer);
        void render (SDL_Renderer* m_Renderer);
        void SetPos(float PosX,float PosY) {m_PosX=PosX, m_PosY=PosY;}

        void set_x_val_(const int& Xval) {x_val_=Xval;};
        void set_y_val_(const int& Yval) {y_val_=Yval;};

        void setstart(int start) {starttime=start;};

        int get_x_val_() const {return x_val_;};
        int get_y_val_() const {return y_val_;};

        float GetPosX() const {return m_PosX;};
        float GetPosY() const {return m_PosY;};

        void PlayerPosX(float b_Player_PosX) {Player_PosX=b_Player_PosX;};
        void PlayerPosY(float b_Player_PosY) {Player_PosY=b_Player_PosY;};

        void handleBullet(SDL_Renderer* m_Renderer);

        vector <Bullet*> GetBulletList ()const {return  m_bullet_list;};

        bool is_alive= true;

        void losehealth() {health--;};

        int get_health() {return health;};

        void set_health(int e_health) {health=e_health;};

        void kill() {health=0;};

        int health;

        float angle;
        float Player_PosX;
        float Player_PosY;

    private:

        bool spawn_once;
        bool spawn_once1;
        bool can_spawn_bullet;
        bool acc1;
        bool acc2;
        bool acc3;
        bool acc4;
        float angle0;
        float angle1;
        float angle2;
        float angle3;
        float angle4;
        float angle5;
        float angle6;

        int pattern;
        int starttime;
        int Current_Time;
        int Last_Time;
        int Last_Time1;
        int Last_Pattern;
        int Last_Pattern_time;
        int left_right;
        int x_val_;
        int y_val_;

        vector <Bullet*> m_bullet_list;

        Texture enemy_img;
};

#endif // ENEMY_H
