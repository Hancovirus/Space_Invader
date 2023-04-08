#ifndef BULLET_H
#define BULLET_H


#include "Object.h"

#define ALERT_WIDTH 72
#define ALERT_HEIGHT 72
#define SPHERE_WIDTH 32
#define SPHERE_HEIGHT 32
#define BULLET_WIDTH 2
#define BULLET_HEIGHT 20
#define BLUEBULLET_WIDTH 2
#define BLUEBULLET_HEIGHT 20
#define BEAM_WIDTH 72
#define BEAM_HEIGHT 405
#define EBULLET_HEIGHT 10
#define EBULLET_WIDTH 6
#define EXPLOSION_HEIGHT 72
#define EXPLOSION_WIDTH 72
#define ENEMY_WIDTH 432
#define ENEMY_HEIGHT 264

class Bullet:public Object
{

    public:


        Bullet();

        //void handleEvent( SDL_Event& e );
        void HandleMove(const int& x_border, const int& y_border);
        void HandleMoveEnemyPattern0(const int& x_border, const int& y_border);
        void HandleMoveEnemyPattern1(const int& x_border, const int& y_border);
        void HandleMoveEnemyPattern2(const int& x_border, const int& y_border);
        void HandleMoveEnemyPattern3(const int& x_border, const int& y_border);
        void HandleMoveEnemyPatternFinal(const int& x_border, const int& y_border);

        void DestroyPrevious();

        void loadImg(SDL_Renderer* m_Renderer);
        void render (SDL_Renderer* m_Renderer);
        void SetPos(float PosX,float PosY) {m_PosX=PosX, m_PosY=PosY;}

        void set_x_val(const float& Xval) {x_val=Xval;};
        void set_y_val(const float& Yval) {y_val=Yval;};

        float get_x_val() const {return x_val;};
        float get_y_val() const {return y_val;};

        float GetPosX() const {return m_PosX;};
        float GetPosY() const {return m_PosY;};

        float GetPosW() const {return m_PosW;};
        float GetPosH() const {return m_PosH;};

        bool get_is_move () const {return is_move;}
        void set_is_move (bool fire) {is_move=fire;}

        void set_angle(float b_angle) {angle=b_angle;};
        void set_Time_appear(int time) {Time_appear=time;};
        void set_num (int b_num) {Num=b_num;};
        void set_alert(bool b_alert) {alert=b_alert;};
        void set_random (bool b_random) {random=b_random;};
        void set_numrandom (int b_random) {num_random=b_random;};
        void set_turret (bool b_turret) {turret=b_turret;};

        void free();

        float angle;
        int num_random;
        int Time_appear;
        bool alert;
        bool random;
        float m_PosW;
        float m_PosH;
        bool turret;
    private:
        int Current_Time;
        int Last_Time;
        int left_right;
        int Num;
        float angle_time;

        float x_val;
        float y_val;
        bool is_move;
        Texture bullet_img;

};

#endif // BULLET_H
