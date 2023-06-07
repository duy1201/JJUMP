#ifndef BULLET_H_
#define BULLET_H_

#include "TextureManage.h"
#include<SDL_image.h>
#include<iostream>

const int BULLET_WIDTH = 24;
const int BULLET_HEIGHT = 24;
const float BULLET_SPEED = -10;

class Bullet
{
public:
    Bullet();
    ~Bullet();
    void HandleInputAction(SDL_Event event);
    void Move();
    void Render();
    void setPos(float x, float y);
    void setIsMove(bool isMove_);
    bool getIsMove();
    SDL_Rect getDst();

private:
    bool isMove;
    SDL_Texture* texture;
    SDL_Rect src, dst;
    float x_pos, y_pos;
    float x_vel, y_vel;
};
#endif // BULLET_H_
