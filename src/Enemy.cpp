#include "Enemy.h"

Texture m_Alert1;

Enemy::Enemy(){
    m_PosX = 0;
    m_PosY = -ENEMY_HEIGHT;

    health=1000;
    angle0=0;
    angle1=0;
    angle2=180;
    angle3=0;
    angle4=-10;
    angle5=0;
    angle6=10;
    acc1=true;
    acc2=true;
    acc3=true;
    acc4=true;

    spawn_once=true;
    can_spawn_bullet=false;

    Last_Time1=0;
    Last_Time=0;

    x_val_=0;
    y_val_=0;
}

void Enemy::HandleMove(const int& x_border, const int& y_border) {
    m_PosY+=y_val_;
    if (m_PosY == -ENEMY_HEIGHT && SDL_GetTicks()>=starttime)
    {
        y_val_ = 1;
    }
    if (m_PosY == 51)
    {
      y_val_ = 0;
      can_spawn_bullet=true;
    }

    if (health<=0){
        is_alive=false;
    }else {is_alive=true;}

    if (is_alive==false){
        m_PosY = -264;
    }
}


void Enemy::handleBullet(SDL_Renderer* m_Renderer)
{
    Current_Time=SDL_GetTicks();
    pattern=((Current_Time-starttime-5128)/15000)%4;

    if (pattern ==0 && is_alive==true && Current_Time>=Last_Time+100 && (Current_Time-starttime-5128)%15000>= 100 && can_spawn_bullet==true && health>100)
    {
        if (angle0 >= 10) {
            acc1=false;
        } else if (angle0 <= -10){
            acc1=true;
        }
        if (acc1==true){
            angle0+=1;
        } else {
            angle0-=1;
        }

        if (angle6 >= 20) {
            acc2=false;
        } else if (angle6 <= 0){
            acc2=true;
        }
        if (acc2==true){
            angle6+=1;
        } else {
            angle6-=1;
        }

        if (angle4 >= 0) {
            acc3=false;
        } else if (angle4 <= -20){
            acc3=true;
        }
        if (acc3==true){
            angle4+=1;
        } else {
            angle4-=1;
        }

        Bullet* m_bullet1 = new Bullet();
        m_bullet1->load(BULLET_WIDTH ,BULLET_HEIGHT,"bluebullet.png");
        m_bullet1->loadImg(m_Renderer);
        m_bullet1->SetPos(this->m_PosX + ENEMY_WIDTH/2  - BULLET_WIDTH/2 +100 ,this->m_PosY + ENEMY_HEIGHT/3);
        m_bullet1->set_x_val(8);
        m_bullet1->set_is_move(true);
        m_bullet1->set_angle(angle0);

        m_bullet_list.push_back(m_bullet1);

        Bullet* m_bullet2 = new Bullet();
        m_bullet2->load(BULLET_WIDTH ,BULLET_HEIGHT,"bluebullet.png");
        m_bullet2->loadImg(m_Renderer);
        m_bullet2->SetPos(this->m_PosX + ENEMY_WIDTH/2  - BULLET_WIDTH/2 +100,this->m_PosY + ENEMY_HEIGHT/3);
        m_bullet2->set_x_val(8);
        m_bullet2->set_is_move(true);
        m_bullet2->set_angle(angle6);

        m_bullet_list.push_back(m_bullet2);

        Bullet* m_bullet3 = new Bullet();
        m_bullet3->load(BULLET_WIDTH ,BULLET_HEIGHT,"bluebullet.png");
        m_bullet3->loadImg(m_Renderer);
        m_bullet3->SetPos(this->m_PosX + ENEMY_WIDTH/2  - BULLET_WIDTH/2 +100,this->m_PosY + ENEMY_HEIGHT/3);
        m_bullet3->set_x_val(8);
        m_bullet3->set_is_move(true);
        m_bullet3->set_angle(angle4);

        m_bullet_list.push_back(m_bullet3);

        Bullet* m_bullet6 = new Bullet();
        m_bullet6->load(BULLET_WIDTH ,BULLET_HEIGHT,"bluebullet.png");
        m_bullet6->loadImg(m_Renderer);
        m_bullet6->SetPos(this->m_PosX + ENEMY_WIDTH/2  - BULLET_WIDTH/2 -100 ,this->m_PosY + ENEMY_HEIGHT/3);
        m_bullet6->set_x_val(8);
        m_bullet6->set_is_move(true);
        m_bullet6->set_angle(angle0);

        m_bullet_list.push_back(m_bullet6);

        Bullet* m_bullet5 = new Bullet();
        m_bullet5->load(BULLET_WIDTH ,BULLET_HEIGHT,"bluebullet.png");
        m_bullet5->loadImg(m_Renderer);
        m_bullet5->SetPos(this->m_PosX + ENEMY_WIDTH/2  - BULLET_WIDTH/2 -100,this->m_PosY + ENEMY_HEIGHT/3);
        m_bullet5->set_x_val(8);
        m_bullet5->set_is_move(true);
        m_bullet5->set_angle(angle6);

        m_bullet_list.push_back(m_bullet5);

        Bullet* m_bullet4 = new Bullet();
        m_bullet4->load(BULLET_WIDTH ,BULLET_HEIGHT,"bluebullet.png");
        m_bullet4->loadImg(m_Renderer);
        m_bullet4->SetPos(this->m_PosX + ENEMY_WIDTH/2  - BLUEBULLET_WIDTH/2 -100,this->m_PosY + ENEMY_HEIGHT/3);
        m_bullet4->set_x_val(8);
        m_bullet4->set_is_move(true);
        m_bullet4->set_angle(angle4);

        m_bullet_list.push_back(m_bullet4);

        Last_Time=Current_Time;

    }
    else if (is_alive==true && Current_Time>=Last_Time+100 && can_spawn_bullet==true && health<=100 )
    {
        Bullet* m_bullet0 = new Bullet();
        angle5+=187;
        m_bullet0->load(EBULLET_WIDTH ,EBULLET_HEIGHT,"ebullet.png");
        m_bullet0->loadImg(m_Renderer);
        m_bullet0->SetPos(this->m_PosX + ENEMY_WIDTH/2  - EBULLET_WIDTH/2,this->m_PosY + ENEMY_HEIGHT);
        m_bullet0->set_x_val(4);
        m_bullet0->set_is_move(true);
        m_bullet0->set_angle(angle5);
        m_bullet0->set_turret(false);

        m_bullet_list.push_back(m_bullet0);

        Bullet* m_bullet1 = new Bullet();
        angle1+=37;
        m_bullet1->load(EBULLET_WIDTH ,EBULLET_HEIGHT,"ebullet.png");
        m_bullet1->loadImg(m_Renderer);
        m_bullet1->SetPos(this->m_PosX + ENEMY_WIDTH/2  - EBULLET_WIDTH/2,this->m_PosY + ENEMY_HEIGHT);
        m_bullet1->set_x_val(4);
        m_bullet1->set_is_move(true);
        m_bullet1->set_angle(angle1);
        m_bullet1->set_turret(false);

        m_bullet_list.push_back(m_bullet1);

        Bullet* m_bullet2 = new Bullet();
        angle2+=37;
        m_bullet2->load(EBULLET_WIDTH ,EBULLET_HEIGHT,"ebullet.png");
        m_bullet2->loadImg(m_Renderer);
        m_bullet2->SetPos(this->m_PosX + ENEMY_WIDTH/2  - EBULLET_WIDTH/2,this->m_PosY + ENEMY_HEIGHT);
        m_bullet2->set_x_val(4);
        m_bullet2->set_is_move(true);
        m_bullet2->set_angle(angle2);
        m_bullet2->set_turret(false);


        m_bullet_list.push_back(m_bullet2);

        Bullet* m_bullet3 = new Bullet();
        m_bullet3->load(BULLET_WIDTH ,BULLET_HEIGHT,"sphere.png");
        m_bullet3->loadImg(m_Renderer);
        m_bullet3->set_is_move(true);
        m_bullet3->set_x_val(1);
        m_bullet3->set_turret(true);
        m_bullet3->set_Time_appear(Current_Time);

        m_bullet_list.push_back(m_bullet3);

        Bullet* m_bullet4 = new Bullet();
        m_bullet4->load(BULLET_WIDTH ,BULLET_HEIGHT,"sphere.png");
        m_bullet4->loadImg(m_Renderer);
        m_bullet4->set_is_move(true);
        m_bullet4->set_x_val(-1);
        m_bullet4->set_turret(true);
        m_bullet4->set_Time_appear(Current_Time);

        m_bullet_list.push_back(m_bullet4);

        for (int i=0;i<4;i++)
            {
            angle = (Current_Time/10)%360;
            Bullet* m_bullet5 = new Bullet();
            m_bullet5->load(BULLET_WIDTH ,BULLET_HEIGHT,"ebullet.png");
            m_bullet5->loadImg(m_Renderer);
            m_bullet5->SetPos(this->m_PosX + ENEMY_WIDTH/2 +   1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*cos(angle*3.14/180) ,this->m_PosY + SCREEN_HEIGHT/2 - SPHERE_WIDTH/2 + 60 + 1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*sin(angle*3.14/180));
            m_bullet5->set_x_val(3);
            m_bullet5->set_is_move(true);
            m_bullet5->set_angle(90*i);
            m_bullet5->set_turret(false);


            m_bullet_list.push_back(m_bullet5);

            Bullet* m_bullet6 = new Bullet();
            m_bullet6->load(BULLET_WIDTH ,BULLET_HEIGHT,"ebullet.png");
            m_bullet6->loadImg(m_Renderer);
            m_bullet6->SetPos(this->m_PosX + ENEMY_WIDTH/2 -  1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*cos(angle*3.14/180) ,this->m_PosY + SCREEN_HEIGHT/2 - SPHERE_WIDTH/2 + 60 - 1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*sin(angle*3.14/180));
            m_bullet6->set_x_val(3);
            m_bullet6->set_is_move(true);
            m_bullet6->set_angle(90*i);
            m_bullet6->set_turret(false);


            m_bullet_list.push_back(m_bullet6);
            }

        Last_Time=Current_Time;
    }
    else if (pattern ==1 && is_alive==true && Current_Time>=Last_Time+1000 && (Current_Time-starttime-5128)%15000>= 100 && can_spawn_bullet==true && health>100 )
    {
        angle3+=37;
        for (int i=0;i<2;i++)
            {
            Bullet* m_bullet1 = new Bullet();
            m_bullet1->load(BULLET_WIDTH ,BULLET_HEIGHT,"ebullet.png");
            m_bullet1->loadImg(m_Renderer);
            m_bullet1->SetPos(this->m_PosX + ENEMY_WIDTH/2  - EBULLET_WIDTH/2 ,this->m_PosY + ENEMY_HEIGHT);
            m_bullet1->set_x_val(2);
            m_bullet1->set_is_move(true);
            m_bullet1->set_angle(angle3-180*i);

            m_bullet_list.push_back(m_bullet1);
            }
    }
    else if (pattern ==2 && is_alive==true && Current_Time>=Last_Time+150 && (Current_Time-starttime-5128)%15000>= 100 && can_spawn_bullet==true && health>100 )
    {
        Current_Time=SDL_GetTicks();
        Bullet* m_bullet1 = new Bullet();
        m_bullet1->load(BULLET_WIDTH ,BULLET_HEIGHT,"sphere.png");
        m_bullet1->loadImg(m_Renderer);
        m_bullet1->set_is_move(true);
        m_bullet1->set_x_val(1);
        m_bullet1->set_turret(true);
        m_bullet1->set_Time_appear(Current_Time);

        m_bullet_list.push_back(m_bullet1);

        Bullet* m_bullet2 = new Bullet();
        m_bullet2->load(BULLET_WIDTH ,BULLET_HEIGHT,"sphere.png");
        m_bullet2->loadImg(m_Renderer);
        m_bullet2->set_is_move(true);
        m_bullet2->set_x_val(-1);
        m_bullet2->set_turret(true);
        m_bullet2->set_Time_appear(Current_Time);

        m_bullet_list.push_back(m_bullet2);

        for (int i=0;i<4;i++)
            {
            angle = (Current_Time/10)%360;
            Bullet* m_bullet3 = new Bullet();
            m_bullet3->load(BULLET_WIDTH ,BULLET_HEIGHT,"ebullet.png");
            m_bullet3->loadImg(m_Renderer);
            m_bullet3->SetPos(this->m_PosX + ENEMY_WIDTH/2 +   1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*cos(angle*3.14/180) ,this->m_PosY + SCREEN_HEIGHT/2 - SPHERE_WIDTH/2 + 60 + 1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*sin(angle*3.14/180));
            m_bullet3->set_x_val(3);
            m_bullet3->set_is_move(true);
            m_bullet3->set_angle(90*i);
            m_bullet3->set_turret(false);


            m_bullet_list.push_back(m_bullet3);

            Bullet* m_bullet4 = new Bullet();
            m_bullet4->load(BULLET_WIDTH ,BULLET_HEIGHT,"ebullet.png");
            m_bullet4->loadImg(m_Renderer);
            m_bullet4->SetPos(this->m_PosX + ENEMY_WIDTH/2 -  1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*cos(angle*3.14/180) ,this->m_PosY + SCREEN_HEIGHT/2 - SPHERE_WIDTH/2 + 60 - 1*((ENEMY_WIDTH/2) - SPHERE_WIDTH/2)*sin(angle*3.14/180));
            m_bullet4->set_x_val(3);
            m_bullet4->set_is_move(true);
            m_bullet4->set_angle(90*i);
            m_bullet4->set_turret(false);


            m_bullet_list.push_back(m_bullet4);
            }
        Last_Time=Current_Time;
    }
    else if (pattern ==3 && is_alive==true && Current_Time>=Last_Time+1000 && (Current_Time-starttime-5128)%15000>= 100 && can_spawn_bullet==true && health>100 )
    {
        for (int i=0;i<8;i++)
            {
            Bullet* m_bullet1 = new Bullet();
            m_bullet1->load(BULLET_WIDTH ,BULLET_HEIGHT,"ebullet.png");
            m_bullet1->loadImg(m_Renderer);
            m_bullet1->SetPos(this->m_PosX + Player_PosX + 14 + 200*cos((45*i*3.14)/180) ,this->m_PosY + Player_PosY - 35 - 200*sin((45*i*3.14)/180));
            m_bullet1->set_x_val(2);
            m_bullet1->set_is_move(true);
            m_bullet1->set_angle(45*i);

            m_bullet_list.push_back(m_bullet1);
            }
        Last_Time=Current_Time;
    }

    for (int i=0;i< m_bullet_list.size();i++)
    {
        Bullet* m_bullet = m_bullet_list.at(i);

        if( m_bullet!=NULL)
        {
            if (m_bullet->get_is_move())
            {
                if (can_spawn_bullet)
                {
                    if (health>100)
                    {
                        if (pattern ==0 && (Current_Time-starttime-5128)%15000 >= 100)
                        {
                            m_bullet->HandleMoveEnemyPattern0(SCREEN_WIDTH, SCREEN_HEIGHT);
                        }
                        else if (pattern==1 && (Current_Time-starttime-5128)%15000 >= 100)
                        {
                            m_bullet->HandleMoveEnemyPattern1(SCREEN_WIDTH, SCREEN_HEIGHT);
                        }
                        else if (pattern==2 && (Current_Time-starttime-5128)%15000 >= 100)
                        {
                            m_bullet->HandleMoveEnemyPattern2(SCREEN_WIDTH, SCREEN_HEIGHT);
                        }
                        else if (pattern==3 && (Current_Time-starttime-5128)%15000 >= 100)
                        {
                            m_bullet->HandleMoveEnemyPattern3(SCREEN_WIDTH, SCREEN_HEIGHT);
                        }
                        else if ((Current_Time-starttime-5128) % 15000 < 100)
                        {
                            m_bullet->DestroyPrevious();
                        }
                    } else {
                        if (health==100) {
                            m_bullet->DestroyPrevious();
                        }
                        m_bullet->HandleMoveEnemyPatternFinal(SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                }
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


void Enemy::loadImg(SDL_Renderer* m_Renderer)
 {
     enemy_img.loadFromFile(m_textureID, m_Renderer);
 }

 void Enemy::render (SDL_Renderer* m_Renderer)
 {
     enemy_img.render(m_PosX, m_PosY, m_Renderer);

 }
