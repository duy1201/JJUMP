#include "TextureManage.h"

SDL_Texture* TextureManage::load(const char* filePath)
{
    SDL_Texture* texture = IMG_LoadTexture(RenderWindow::renderer, filePath);

    if (texture == NULL)
    {
        cout << "Load Texture " << filePath << " failed" << '\n';
    }

    return texture;
}

void TextureManage::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(RenderWindow::renderer, texture, &src, &dst);
}



