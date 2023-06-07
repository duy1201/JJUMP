#include"Text.h"

TextObject::TextObject()
{
    texture = NULL;
}

TextObject::~TextObject()
{
}

void TextObject::setText(const string &text)
{
    str_val = text;
}

void TextObject::setColor(const int& type)
{
    if (type == WHITE)
    {
        SDL_Color color =  {255, 255, 255};
        text_color = color;
    }

    else if (type == BLACK)
    {
        SDL_Color color =  {0, 0, 0};
        text_color = color;
    }

    else
    {
        SDL_Color color =  {255, 0, 0};
        text_color = color;
    }
}

void TextObject::CreateText(TTF_Font* font)
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, str_val.c_str(), text_color );
    dst.w = textSurface ->w;
    dst.h = textSurface -> h;
    texture = SDL_CreateTextureFromSurface( RenderWindow::renderer, textSurface );
    SDL_FreeSurface(textSurface);
}

void TextObject::Render(int x, int y)
{
    dst.x = x;
    dst.y = y;
    SDL_RenderCopy(RenderWindow::renderer, texture,NULL, &dst);
}
