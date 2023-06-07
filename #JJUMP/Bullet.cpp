#include "Bullet.h"

Bullet::Bullet()
{
    texture = TextureManage::load("img/ball.png");
    src = {0, 0, 205, 204};
    dst = {0, 0, 2*PIXEL, 2*PIXEL};
    x_pos = 0;
    y_pos = 0;
    x_vel = 0;
    y_vel = BULLET_SPEED;
    isMove = false;
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Bullet::Move()
{
    y_pos += y_vel;
    if (y_pos < - BULLET_HEIGHT)
        isMove = false;
}

void Bullet::setPos(float x, float y)
{
    x_pos = x;
    y_pos = y;
}

void Bullet::setIsMove(bool isMove_)
{
    isMove = isMove_;
    if (y_pos < 0)
        isMove = false;
}

bool Bullet::getIsMove()
{
    return isMove;
}

void Bullet::Render()
{
    dst.x = x_pos;
    dst.y = y_pos;
    TextureManage::draw(texture, src, dst);
}

SDL_Rect Bullet::getDst()
{
    return dst;
}
