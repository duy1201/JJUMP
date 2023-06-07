#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include<vector>

#include"RenderWindow.h"
#include"TextureManage.h"
#include"Platform.h"
#include"Bullet.h"

using namespace std;

const int MAIN_OBJECT_FRAME = 5;
const int MAIN_OBJECT_WIDTH = 48;
const int MAIN_OBJECT_HEIGHT = 72;
const float MAIN_OBJECT_VEL = 4.5;
const float JUMP_SPEED = -8.8;
const float FALL_SPEED = 0.2;

class MainObject
{
public:
    MainObject();
    ~MainObject();
    void load(const char* filePath);
    void HandleInputAction(SDL_Event event);
    void Move(vector<Platform*> platforms, bool &scroll);
    void Render();
    bool onGround(SDL_Rect platDst);
    float get_y_vel();
    void setPos(float x, float y);
    float get_y_pos();
    void setBulletList(vector<Bullet*> bullet_list_);
    vector<Bullet*> getBulletList() const;
    void removeBullet(const int& idx);
    void HandleBullet();
    SDL_Rect getDst();
    void setIsDead(bool isDead_);
    bool getIsDead();
    SDL_Rect getCollider();
private:
    float PosX, PosY;
    float x_vel, y_vel;
    SDL_Texture* texture;
    int dirX;
    SDL_Rect clips[MAIN_OBJECT_FRAME];
    SDL_Rect src, dst;
    SDL_Rect Collider;
    vector<Bullet*> bullet_list;
    bool isDead;
    int frame = 0;
};
#endif // MAIN_OBJECT_H_
