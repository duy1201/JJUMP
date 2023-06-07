#ifndef TEXT_H_
#define TEXT_H_
#include<string>
#include"TextureManage.h"

using namespace std;

class TextObject
{
public:
    enum TextColor
    {
        WHITE = 0,
        BLACK = 1,
        RED = 2,
    };
    TextObject();
    ~TextObject();
    void setText(const string &text);
    void setColor(const int &type);
    void CreateText(TTF_Font* font);
    void Render(int x, int y);
    int getWidth()
    {
        return dst.w;
    }
private:
    SDL_Texture* texture;
    SDL_Rect dst;
    string str_val;
    SDL_Color text_color;

};

#endif // TEXT_H_


