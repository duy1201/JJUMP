#include "GameBase.h"

using namespace std;

Mix_Music *gMusic = NULL;
Mix_Chunk *jump = NULL;
Mix_Chunk *dead = NULL;
Mix_Chunk *shot = NULL;

int main(int argc, char* argv[])
{
    srand(time(0));

    RenderWindow("#JJUMP", WINDOW_WIDTH, WINDOW_HEIGHT);

    gMusic = Mix_LoadMUS( "sound/04. Mii Plaza.wav" );
    jump = Mix_LoadWAV("sound/jump.mp3");
    shot = Mix_LoadWAV("sound/shot.mp3");

    bool quit = false;

    if (!quit)
    {
        bool showMenu = MenuState();
        if (showMenu)
        {
            quit = true;
        }
    }

    MainObject Player;
    if (!quit)
    {
        bool showChooseChar = ChooseCharState(Player);
        if (showChooseChar)
            quit = true;
    }

    bool scroll;
    int Score;
    SDL_Texture* background = TextureManage::load("img/pitch.png");
    TTF_Font* Font = TTF_OpenFont("font/Welbut__.ttf", 18 );
    TextObject ScoreText;
    ScoreText.setColor(TextObject::BLACK);

    vector<Platform*> platforms;

    vector<ThreatObject*> Monsters;

    SDL_Event event;

    while (!quit)
    {
        bool gameRunning = true;

        //The frames per second timer
        LTimer fpsTimer;
        //The frames per second cap timer
        LTimer capTimer;
        int countedFrames = 0;
        fpsTimer.start();

        Score = 0;
        scroll = false;
        generatePlatforms(platforms);

        Player.setPos(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
        Player.setIsDead(false);

        if( Mix_PlayingMusic() == 0 )
            Mix_PlayMusic( gMusic, -1 );

        while (gameRunning)
        {
            capTimer.start();

            while(SDL_PollEvent(&event)!=0)
            {
                if (event.type == SDL_QUIT)
                {
                    gameRunning = false;
                    quit = true;
                    break;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym ==  SDLK_SPACE)
                    Mix_PlayChannel( -1, shot, 0 );

                Player.HandleInputAction(event);
            }

            float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );

            if( avgFPS > 2000000 )
            {
                avgFPS = 0;
            }

            RenderWindow::renderClear();
            SDL_RenderCopy(RenderWindow::renderer, background, NULL, NULL);
            Player.Move(platforms, scroll);

            if (Player.get_y_vel() == JUMP_SPEED)
                Mix_PlayChannel( -1, jump, 0 );

            if (scroll) Score += -Player.get_y_vel();

            updatePlatforms(platforms, Player, Score, scroll);

            Player.Render();
            Player.HandleBullet();

            updateMonsters(Monsters, Player, platforms, scroll);

            string score_val = "SCORE: " + to_string(Score);
            ScoreText.setText(score_val);
            ScoreText.CreateText(Font);
            ScoreText.Render(0, 0);

            RenderWindow::display();
            ++countedFrames;

            //If frame finished early
            int frameTicks = capTimer.getTicks();
            if( frameTicks < SCREEN_TICKS_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
            }
            if (Player.get_y_pos() >  WINDOW_HEIGHT)
                gameRunning = false;

            if (Player.getIsDead())
                Mix_HaltMusic();

            if (!gameRunning)
            {
                Mix_HaltMusic();
                Player.setIsDead(true);
                while(!platforms.empty())
                {
                    Platform* platform_ = platforms.front();
                    platforms.erase(platforms.begin());
                    platform_->~Platform();
                    if (platform_!=NULL)
                    {
                        delete platform_;
                        platform_ = NULL;
                    }
                }

                while(!Monsters.empty())
                {
                    ThreatObject* monster_ = Monsters.front();
                    Monsters.erase(Monsters.begin());
                    monster_->~ThreatObject();
                    if (monster_!=NULL)
                    {
                        delete monster_;
                        monster_ = NULL;
                    }
                }

                vector<Bullet*> balls = Player.getBulletList();
                for (unsigned int i = 0; i < balls.size(); i++)
                    balls[i]->setIsMove(false);
                Player.HandleBullet();

                gameRunning = false;
            }
        }

        if (!gameRunning && quit)
            break;

        bool ShowGameOver = GameOverState(Score);
        if (ShowGameOver)
        {
            quit = true;
        }
    }
    Mix_FreeMusic( gMusic );
    Mix_FreeChunk(jump);
    Mix_FreeChunk(shot);
    gMusic = NULL;
    jump = NULL;
    Player.~MainObject();
    SDL_DestroyTexture(background);
    RenderWindow::cleanup();
}

