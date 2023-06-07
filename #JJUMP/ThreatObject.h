#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "TextureManage.h"

const int THREAT_HEIGHT = 72;
const int THREAT_WIDTH = 48;
const float THREAT_VEL = 2.8;

class ThreatObject
{
public:
    ThreatObject();
    ~ThreatObject();
    void load(const char* filePath);
    void Render();
    void setPos(float x_, float y_);
    float get_y_pos();
    void Move(float m_yVel, bool scroll);
    void setIsExist(bool isExist_);
    bool getIsExist();
    SDL_Rect getDst();
    void setType();
    int getType();

private:
    float PosX, PosY;
    float x_vel, y_vel;
    int dirX;
    SDL_Texture* texture;
    SDL_Rect src, dst;
    SDL_Rect Defender_Sprites[6], GK_Sprites[2];
    int frame;
    int type;
    bool isExist;
};
#endif // THREAT_OBJECT_H_
