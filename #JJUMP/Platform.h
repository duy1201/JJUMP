#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "RenderWindow.h"

const int PLATFORM_HEIGHT = 24;
const int PLATFORM_WIDTH = 72;
const float PLATFORM_VEL = 2;

class Platform
{
public:
    Platform();
    ~Platform();
    void load(const char* filePath);
    void Move(float y_vel_, bool &scroll);
    void Render();
    void setPos(float x, float y);
    float get_x_pos();
    float get_y_pos();
    float get_x_vel();
    SDL_Rect getDst();
    void setType(int type);

private:
    float x_pos, y_pos;
    float x_vel, y_vel;
    SDL_Texture* texture;
    SDL_Rect src, dst;
    int type;
    int dirX;
    bool haveCoin;
};
#endif // PLATFORM_H_
