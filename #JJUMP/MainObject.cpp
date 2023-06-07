#include "MainObject.h"
using namespace std;


MainObject:: MainObject()
{
    x_vel = 0;
    y_vel = 0;
    dirX = 1;
    PosX = WINDOW_WIDTH/2;
    PosY = WINDOW_HEIGHT/2;
    texture = NULL;
    dst = {0, WINDOW_HEIGHT/2, MAIN_OBJECT_WIDTH, MAIN_OBJECT_HEIGHT};
    Collider = {WINDOW_WIDTH/2 + 3, WINDOW_HEIGHT/2 + 3, 42, 66};
    clips[0] = {0, 0, 190, 370};
    clips[1] = {190, 0, 190, 370};
    clips[2] = {380, 0, 190, 370};
    clips[3] = {570, 0, 190, 370};
    clips[4] = {760, 0, 190, 370};
    isDead = false;
}

MainObject::~MainObject()
{
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void MainObject::setPos(float x, float y)
{
    PosX = x;
    Collider.x = PosX + 3;
    PosY = y;
    Collider.y = PosY + 3;
}

void MainObject::load(const char* filePath)
{
    texture = TextureManage::load(filePath);
}

void MainObject::HandleInputAction(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_LEFT:
            x_vel -= MAIN_OBJECT_VEL;
            dirX = 0;
            break;

        case SDLK_RIGHT:
            x_vel += MAIN_OBJECT_VEL;
            dirX = 1;
            break;

        case SDLK_SPACE:
        {
            if (!isDead)
            {
                Bullet* Ball = new Bullet;
                Ball -> setPos(PosX + MAIN_OBJECT_WIDTH/2 - BULLET_WIDTH/2, PosY + MAIN_OBJECT_HEIGHT);
                Ball -> setIsMove(true);
                bullet_list.push_back(Ball);
            }
        }
        break;

        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_LEFT:
            x_vel += MAIN_OBJECT_VEL;
            break;

        case SDLK_RIGHT:
            x_vel -= MAIN_OBJECT_VEL;
            break;
        default:
            break;
        }
    }
}

void MainObject::Move(vector<Platform*> platforms, bool &scroll)
{
    if (isDead)
    {
        x_vel = 0;
        PosX += x_vel;
        if (y_vel < 0) y_vel = 0;
        y_vel += FALL_SPEED;
        PosY += y_vel;
        scroll = false;
    }
    else
    {
        PosX += x_vel;
        if (PosX <= - MAIN_OBJECT_WIDTH)
        {
            PosX = RenderWindow::width;
        }
        else if (PosX >= RenderWindow::width)
        {
            PosX = -MAIN_OBJECT_WIDTH;
        }

        y_vel += FALL_SPEED;
        PosY += y_vel;
        scroll = false;

        if (PosY < WINDOW_HEIGHT/2)
        {
            PosY = WINDOW_HEIGHT/2;
            scroll = true;
        }
        bool check = false;

        if (y_vel > 0)
        {
            for (int i = 0; i < platforms.size(); i++)
            {
                if (onGround(platforms[i] -> getDst()))
                {
                    check = true;
                    break;
                }
            }
        }

        if (check)
        {
            y_vel = JUMP_SPEED;
        }
    }

    if (PosY >= WINDOW_HEIGHT)
    {
        y_vel = 0;
        x_vel = 0;
    }

    Collider.x = PosX + 3;
    Collider.y = PosY + 3;
}

void MainObject::Render()
{

    dst.x = PosX;
    dst.y = PosY;

    if (isDead)
    {
        src = clips[0];
    }
    else
    {
        if (y_vel <= 0)
        {
            if (frame < 16)
            {
                src = clips[2];
                frame++;
            }
            else
                src = clips[3];
            if (x_vel != 0)
                src = clips[1];
        }
        else
        {
            src = clips[4];
            frame = 0;
        }
    }

    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    if (dirX == 1) flipType = SDL_FLIP_HORIZONTAL;


    SDL_RenderCopyEx(RenderWindow::renderer, texture, &src, &dst, 0.0, NULL, flipType);
}

bool MainObject::onGround(SDL_Rect platDst)
{
    if(dst.x + 20 < platDst.x + platDst.w
            && dst.x + dst.w - 20 > platDst.x
            && dst.y + dst.h < platDst.y+platDst.h*1.0/2
            && dst.y + dst.h > platDst.y)
        return true;
    return false;
}

float MainObject::get_y_vel()
{
    return y_vel;
}

float MainObject::get_y_pos()
{
    return PosY;
}

void MainObject::setBulletList(vector<Bullet*> bullet_list_)
{
    bullet_list = bullet_list_;
}

vector<Bullet*> MainObject::getBulletList() const
{
    return bullet_list;
}

void MainObject::HandleBullet()
{

    for (int i = 0; i < bullet_list.size(); i++)
    {
        Bullet* ball = bullet_list[i];
        if (ball != NULL)
        {
            if (ball->getIsMove() == true)
            {
                ball->Move();
                ball->Render();
            }
            else
            {
                bullet_list.erase(bullet_list.begin() + i);
                if (ball != NULL)
                {
                    delete ball;
                    ball = NULL;
                }
            }
        }
    }
}

SDL_Rect MainObject::getDst()
{
    return dst;
}

void MainObject::removeBullet(const int& idx)
{
    int size_ =  bullet_list.size();
    if (size_ > 0 && idx < size_)
    {
        Bullet* ball =  bullet_list[idx];
        bullet_list.erase(bullet_list.begin() + idx);
        if (ball != NULL)
        {
            delete ball;
            ball = NULL;
        }
    }
}

void MainObject::setIsDead(bool isDead_)
{
    isDead = isDead_;
}

bool MainObject::getIsDead()
{
    return isDead;
}

SDL_Rect MainObject::getCollider()
{
    return Collider;
}
