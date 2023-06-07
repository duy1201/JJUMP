#include "RenderWindow.h"
using namespace std;

SDL_Window* RenderWindow::window;
SDL_Renderer* RenderWindow::renderer;
int RenderWindow::width, RenderWindow::height;

RenderWindow::RenderWindow()
{
}
RenderWindow::~RenderWindow()
{
}

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
{

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)!=0)
    {
        cout << "SDL Init Error" << SDL_GetError() << '\n';
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG Init Error: " << IMG_GetError() << '\n';
    }

    if (TTF_Init()== -1)
    {
        cout << "TTF Init Error: " << TTF_GetError() << '\n';
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    window = NULL;
    renderer = NULL;

    width = p_w;
    height = p_h;

    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "Create Window failed: " << SDL_GetError() << '\n';
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        cout << "Create Renderer failed: " <<SDL_GetError() << '\n';
    }
}

void RenderWindow::renderClear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanup()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

int Random(int a, int b)
{
    return rand()%(b- a +1) + a;
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


