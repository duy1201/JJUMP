#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    texture = NULL;
    dirX = 1;
    PosX = 0;
    PosY = 0;
    dst = {0, 0, THREAT_WIDTH, THREAT_HEIGHT};
    isExist = false;
    Defender_Sprites[0] = {0, 0, 190, 370};
    Defender_Sprites[1] = {190, 0, 190, 370};
    Defender_Sprites[2] = {190*2, 0, 190, 370};
    Defender_Sprites[3] = {190*3, 0, 190, 370};
    Defender_Sprites[4] = {190*4, 0, 190, 370};
    Defender_Sprites[5] = {190*5, 0, 190, 370};
    GK_Sprites[0] = {0, 0, 190, 370};
    GK_Sprites[1] = {190, 0, 190, 370};
    frame = 0;
}

ThreatObject::~ThreatObject()
{
    if (texture != NULL)
        texture = NULL;
}

void ThreatObject::load(const char* filePath)
{
    texture =  TextureManage::load(filePath);
}

void ThreatObject::setPos(float x_, float y_)
{
    PosX = x_;
    PosY = y_;
}

void ThreatObject::Render()
{
    dst.x = PosX;
    dst.y = PosY;
    if (type == 0)
    {
        src = Defender_Sprites[frame/6];
        frame ++;
        if (frame/6 >= 6) frame = 0;
    }
    else
    {
        src = GK_Sprites[frame/12];
        frame ++;
        if (frame/12 >= 2) frame = 0;
    }

    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    if (dirX == 0) flipType = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(RenderWindow::renderer, texture, &src, &dst, 0.0, NULL, flipType);
}

void ThreatObject::Move(float m_yVel, bool scroll)
{
    if (scroll == true)
        PosY += -m_yVel;

    if (type == 1)
        x_vel = 0;
    else
        x_vel = THREAT_VEL;

    if (dirX == 1)
    {
        PosX += x_vel;
        if (PosX + THREAT_WIDTH > WINDOW_WIDTH)
        {
            x_vel = 0;
            dirX = 0;
        }
    }
    else if (dirX == 0)
    {
        PosX -= x_vel;
        if (PosX < 0)
        {
            x_vel = 0;
            dirX = 1;
        }
    }


    if (PosY > WINDOW_HEIGHT)
        isExist = false;
}

void ThreatObject::setIsExist(bool isExist_)
{
    isExist = isExist_;
}

bool ThreatObject::getIsExist()
{
    return isExist;
}

float ThreatObject::get_y_pos()
{
    return PosY;
}


SDL_Rect ThreatObject::getDst()
{
    return dst;
}

void ThreatObject::setType()
{
    int x = rand()%2;
    if (x == 0) type = 0;
    else type = 1;
}

int ThreatObject::getType()
{
    return type;
}
