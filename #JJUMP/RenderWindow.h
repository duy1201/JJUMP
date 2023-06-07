#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<cstdlib>
#include<string>
#include<ctime>

using namespace std;

const int PIXEL = 12;
const int WINDOW_WIDTH = 420;
const int WINDOW_HEIGHT = 640;
const int MONSTERS_COUNT = 3;
const int PLATFORMS_COUNT = 20;


class RenderWindow
{
public:
    RenderWindow();
    ~RenderWindow();
    RenderWindow(const char* p_title, int p_w, int p_h);

    static void renderClear();
    static void display();
    static void cleanup();

    static int width;
    static int height;
    static SDL_Window* window;
    static SDL_Renderer* renderer;

private:


};

int Random(int a, int b);

bool checkCollision( SDL_Rect a, SDL_Rect b );


#endif // RENDERWINDOW_H_


