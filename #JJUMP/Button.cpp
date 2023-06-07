#include "Button.h"

Button::Button()
{
    texture = NULL;
    x_pos = 0;
    y_pos = 0;
    width = BUTTON_WIDTH;
    height = BUTTON_HEIGHT;
    SRC = {0, 0, 0, 0};
    src = {0, 0, 0, 0};
    dst = {(int)x_pos, (int)y_pos, (int)width, (int)height};
    selected = false;
}

Button::~Button()
{

}

void Button::setPos(float x, float y)
{
    x_pos = x;
    y_pos = y;
}
void Button::setWidth(float w)
{
    width = w;
}

void Button::setHeight(float h)
{
    height = h;
}

void Button::load(const char* filePath)
{
    texture = TextureManage::load(filePath);
}

void Button::Render()
{
    dst = {x_pos, y_pos, width, height};
    TextureManage::draw(texture, SRC, dst);
}

void Button::setSrc(float x, float y, float w, float h)
{
    src = {x, y, w, h};
}

void Button::setBrightSrc(float x, float y, float w, float h)
{
    bright_src = {x, y, w, h};
}

void Button::HandleEvent(SDL_Event* event)
{
    SRC = src;
    int x, y;
    SDL_GetMouseState( &x, &y );
    bool inside = true;

    if( x < x_pos )
    {
        inside = false;
    }
    else if( x > x_pos + width )
    {
        inside = false;
    }
    else if( y < y_pos )
    {
        inside = false;
    }
    else if( y > y_pos + height )
    {
        inside = false;
    }
    if (inside)
    {
        SRC = bright_src;
        switch( event->type )
        {
        case SDL_MOUSEMOTION:
            break;

        case SDL_MOUSEBUTTONDOWN:
        {
            selected = true;
        }
        break;

        case SDL_MOUSEBUTTONUP:
            break;
        }
    }
}

bool Button::getSelected()
{
    return selected;
}
