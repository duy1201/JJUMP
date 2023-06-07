#ifndef BUTTON_H_
#define BUTTON_H_

#include "TextureManage.h"

const float BUTTON_WIDTH = 10*PIXEL;
const float BUTTON_HEIGHT = 5*PIXEL;

class Button
{
public:

    Button();
    ~Button();
    void setPos(float x, float y);
    void setWidth(float w);
    void setHeight(float h);
    void load(const char* filePath);
    void HandleEvent(SDL_Event* event);
    void Render();
    void setSrc(float x, float y, float w, float h);
    void setBrightSrc(float x, float y, float w, float h);
    bool getSelected();

private:
    SDL_Texture* texture;
    SDL_Rect SRC, src, bright_src , dst;
    float x_pos, y_pos;
    float width, height;
    bool selected;
};

#endif // BUTTON_H_
