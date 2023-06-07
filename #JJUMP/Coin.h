#ifndef COIN_H_
#define COIN_H_

#include "TextureManage.h"

const int COIN_WIDTH = 2*PIXEL;
const int COIN_HEIGHT = 2*PIXEL;

class Coin{
public:
    Coin();
    ~Coin();
    void load(const char* filePath);
    void Move(float y_vel_,bool &scroll);
    void Render();
    SDL_Rect getDst();
    void setPos(float x_, float y_);
    float getY_pos();
    void setIsExist(bool exist);
    bool getIsExist();
    void setX_vel(float x_vel_);
    void setIdPlatform(int idx);
    int getIdPlatform();

private:
    float x_pos, y_pos;
    float x_vel, y_vel;
    SDL_Texture* texture;
    SDL_Rect src, dst;
    bool isExist;
    int idPlatform;
};
#endif // COIN_H_

