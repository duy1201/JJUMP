#include"Coin.h"

Coin::Coin()
{
    texture = NULL /*TextureManage::load("coins.png")*/;
    x_pos = 0; y_pos = 0;
    src = {0, 0, 768, 756};
    dst = {0, 0, COIN_WIDTH, COIN_HEIGHT };
    isExist = false;
}

Coin::~Coin()
{

}

void Coin::load(const char* filePath)
{
    texture = TextureManage::load(filePath);
}

void Coin::Move(float y_vel_, bool &scroll)
{
    y_vel = y_vel_;
    if (scroll == true)
        y_pos -= y_vel;
    if (y_pos > WINDOW_HEIGHT)
        isExist = false;

    x_pos += x_vel;
}

void Coin::Render()
{
    dst.x = x_pos;
    dst.y = y_pos;
    TextureManage::draw(texture, src, dst);
}

SDL_Rect Coin::getDst()
{
    return dst;
}

void Coin::setPos(float x_, float y_)
{
    x_pos = x_;
    y_pos = y_;
}

float Coin::getY_pos()
{
    return y_pos;
}

void Coin::setIsExist(bool exist)
{
    isExist = exist;
}

bool Coin::getIsExist()
{
    return isExist;
}

void Coin::setX_vel(float x_vel_)
{
    x_vel = x_vel_;
}

void Coin::setIdPlatform(int idx)
{
    idPlatform = idx;
}

int Coin::getIdPlatform()
{
    return idPlatform;
}


