#include "Platform.h"
#include "TextureManage.h"
#include "RenderWindow.h"

using namespace std;

//constructor
Platform::Platform()
{
    dirX = Random(0, 1);
    texture = NULL;
    x_pos = 0;
    y_pos = 0;
    x_vel = 0;
    y_vel = 0;
    type = 1;
    src = {0, 0, 144, 24};
    dst= {0, 0, PLATFORM_WIDTH, PLATFORM_HEIGHT};
    haveCoin = false;
}

//destructor
Platform::~Platform()
{
    if (texture!=NULL)
        SDL_DestroyTexture(texture);
}

void Platform::load(const char* filePath)
{
    texture = TextureManage::load(filePath);
}

void Platform::Render()
{
    dst.x = x_pos;
    dst.y = y_pos;

    if (type == 1)
    {
        src = {0, 0, 72, 24};
    }

    else if (type == 2)
    {
        src = {72, 0, 72, 24};
    }
    TextureManage::draw(texture, src, dst);
}

void Platform::Move(float y_vel_, bool &scroll)
{
    y_vel = y_vel_;
    if (scroll == true)
        y_pos -= y_vel;

    x_vel = PLATFORM_VEL;
    if (type == 2)
    {
        if (dirX == 1)
        {
            x_pos += x_vel;
            if (x_pos + PLATFORM_WIDTH > WINDOW_WIDTH)
            {
                x_vel = 0;
                dirX = 0;
            }
        }
        else if (dirX == 0)
        {
            x_vel = -x_vel;
            x_pos += x_vel;
            if (x_pos < 0)
            {
                x_vel = 0;
                dirX = 1;
            }
        }
    }
    else
    {
        x_vel = 0;
    }
}

void Platform::setPos(float x, float y)
{
    x_pos = x;
    y_pos = y;
}

float Platform::get_x_pos()
{
    return x_pos;
}

float Platform::get_y_pos()
{
    return y_pos;
}

SDL_Rect Platform::getDst()
{
    return dst;
}

void Platform::setType(int type)
{
    this->type = type;
}


float Platform::get_x_vel()
{
    return x_vel;
}
