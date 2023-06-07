#ifndef TEXTUREMANAGE_H_
#define TEXTUREMANAGE_H_

#include<SDL.h>
#include<SDL_image.h>

#include "RenderWindow.h"

class TextureManage
{
public:
    static SDL_Texture* load(const char* filePath);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
};
#endif // TEXTUREMANAGE_H_
