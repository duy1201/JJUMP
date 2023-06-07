#include "GameBase.h"

bool MenuState()
{
    const int MENU_BUTTON_COUNT = 2;
    SDL_Texture* backGroundTexture = TextureManage::load("img/Menu.png");

    vector<Button*> MenuButton;
    for (int i = 0; i < MENU_BUTTON_COUNT; i++)
    {
        Button* button_ = new Button;
        button_->load("img/Button.png");
        button_->setPos(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 200 + (i*(BUTTON_HEIGHT+PIXEL)));
        MenuButton.push_back(button_);
    }

    MenuButton[0]->setSrc(0, 0, 120, 60);
    MenuButton[0]->setBrightSrc(0, 60, 120, 60);

    MenuButton[1]->setSrc(480, 0, 120, 60);
    MenuButton[1]->setBrightSrc(480, 60, 120, 60);

    SDL_Event Event;

    while (true)
    {
        while(SDL_PollEvent(&Event)!=0)
        {
            if (Event.type == SDL_QUIT)
            {
                return true;
            }
            for (int i = 0; i < MENU_BUTTON_COUNT; i++)
                MenuButton[i]->HandleEvent(&Event);
        }

        RenderWindow::renderClear();
        SDL_RenderCopy(RenderWindow::renderer, backGroundTexture, NULL, NULL);
        for (int i = 0; i < MENU_BUTTON_COUNT; i++)
            MenuButton[i]->Render();
        RenderWindow::display();

        if (MenuButton[0]->getSelected())
            return false;
        if (MenuButton[1]->getSelected())
            return true;

    }
    return true;
}

bool ChooseCharState(MainObject &Player)
{
    const int CHOOSE_CHAR_BUTTON_COUNT = 2;
    SDL_Texture* backGroundTexture = TextureManage::load("img/ChooseChar.png");

    vector<Button*> CCButton;
    for (int i = 0; i < CHOOSE_CHAR_BUTTON_COUNT; i++)
    {
        Button* button_ = new Button;
        button_->setHeight(180);
        button_->setWidth(180);
        button_->setPos(WINDOW_WIDTH/2 - 90, 180 + (i*(180+3*PIXEL)));
        CCButton.push_back(button_);
    }

    CCButton[0]->load("img/Char1-Button.png");
    CCButton[0]->setSrc(0, 0, 150, 150);
    CCButton[0]->setBrightSrc(0, 150, 150, 150);

    CCButton[1]->load("img/Char2-Button.png");
    CCButton[1]->setSrc(0, 0, 150, 150);
    CCButton[1]->setBrightSrc(0, 150, 150, 150);

    SDL_Event Event;

    while (true)
    {
        while(SDL_PollEvent(&Event)!=0)
        {
            if (Event.type == SDL_QUIT)
                return true;
            for (unsigned int i = 0; i < CHOOSE_CHAR_BUTTON_COUNT; i++)
                CCButton[i]->HandleEvent(&Event);
        }

        RenderWindow::renderClear();

        SDL_RenderCopy(RenderWindow::renderer, backGroundTexture, NULL, NULL);

        for (int i = 0; i < CHOOSE_CHAR_BUTTON_COUNT; i++)
            CCButton[i]->Render();

        RenderWindow::display();

        if (CCButton[0]->getSelected())
        {
            Player.load("img/Bruno (2).png");
            return false;
        }

        if (CCButton[1]->getSelected())
        {
            Player.load("img/Jorginho (2).png");
            return false;
        }
    }
}

bool GameOverState(int &Score)
{
    const int GAME_OVER_BUTTON_COUNT = 2;
    SDL_Texture* backGroundTexture = TextureManage::load("img/GameOver.png");

    TTF_Font* Font = TTF_OpenFont("font/Welbut__.ttf", 50 );
    TextObject ScoreText;
    ScoreText.setColor(TextObject::WHITE);
    string score_val = to_string(Score);
    ScoreText.setText(score_val);
    ScoreText.CreateText(Font);

    vector<Button*> GOButton;
    for (int i = 0; i < GAME_OVER_BUTTON_COUNT; i++)
    {
        Button* button_ = new Button;
        button_->load("img/Button.png");
        button_->setPos(WINDOW_WIDTH/2 - BUTTON_WIDTH/2, 320 + (i*(BUTTON_HEIGHT+PIXEL)));
        GOButton.push_back(button_);
    }

    GOButton[0]->setSrc(240, 0, 120, 60);
    GOButton[0]->setBrightSrc(240, 60, 120, 60);

    GOButton[1]->setSrc(480, 0, 120, 60);
    GOButton[1]->setBrightSrc(480, 60, 120, 60);

    SDL_Event Event;

    while (true)
    {
        while(SDL_PollEvent(&Event)!=0)
        {
            if (Event.type == SDL_QUIT)
            {
                return true;
            }
            for (unsigned int i = 0; i < GAME_OVER_BUTTON_COUNT; i++)
                GOButton[i]->HandleEvent(&Event);
        }
        RenderWindow::renderClear();
        SDL_RenderCopy(RenderWindow::renderer, backGroundTexture, NULL, NULL);

        ScoreText.Render(WINDOW_WIDTH/2 - ScoreText.getWidth()/2, 230);
        for (int i = 0; i < GAME_OVER_BUTTON_COUNT; i++)
            GOButton[i]->Render();
        RenderWindow::display();

        if (GOButton[0]->getSelected())
            return false;
        if (GOButton[1]->getSelected())
            return true;
    }
    return true;
}

void updateMonsters(vector<ThreatObject*> &Monsters, MainObject &Player,
                    vector<Platform*> &platforms, bool &scroll)
{
    for (unsigned int i = 0; i < Monsters.size(); i++)
    {
        ThreatObject* monster_ = Monsters[i];
        if (monster_ != NULL)
        {
            if (monster_->getIsExist() == true)
            {
                monster_->Move(Player.get_y_vel(),scroll);
                monster_->Render();

                //check collision player and monster
                if (checkCollision(Player.getCollider(),monster_->getDst()))
                {
                    Player.setIsDead(true);
                }

                //check collision ball and monster
                vector<Bullet*> balls = Player.getBulletList();
                for (unsigned int j = 0; j < balls.size(); j++)
                {
                    Bullet* ball = balls[j];
                    if (ball!= NULL)
                    {
                        if (checkCollision(ball->getDst(), Monsters[i]->getDst()))
                        {
                            Monsters[i]->setIsExist(false);
                            Player.removeBullet(j);
                        }
                    }
                }
            }
            else
            {
                Monsters.erase(Monsters.begin() + i);
                monster_->~ThreatObject();
                if (monster_!= NULL)
                {
                    delete monster_;
                    monster_ = NULL;
                }
            }
        }
    }

    if (Monsters.size() < MONSTERS_COUNT)
    {
        bool check = false;
        int Exist = rand()%100;

        int x_ = Random(0, WINDOW_WIDTH - THREAT_WIDTH);
        int y_ = -THREAT_HEIGHT;
        for (unsigned int i = 0; i < platforms.size() - 1; i++)
        {
            if (y_ + THREAT_HEIGHT*8/7 < platforms[i]->get_y_pos() && y_ - THREAT_HEIGHT*1/7 > platforms[i + 1]->get_y_pos() + PLATFORM_HEIGHT)
            {
                check = true;
                for (unsigned int j = 0; j < Monsters.size(); j++)
                {
                    if (Monsters[j]->get_y_pos() + THREAT_HEIGHT < platforms[i]->get_y_pos()
                            && Monsters[j]->get_y_pos() > platforms[i + 1]->get_y_pos()+ PLATFORM_HEIGHT)
                    {
                        check = false;
                        break;
                    }
                }
            }
            if (check) break;
        }
        if (check && Exist == 1)
        {
            ThreatObject* monster_ = new ThreatObject;
            monster_->setPos(x_, y_);
            monster_->setIsExist(true);
            monster_->setType();
            int type_;
            if (monster_->getType() == 0)
            {
                type_ = rand()%3;
                switch (type_)
                {
                case 0:
                    monster_->load("img/vandijk.png");
                    break;
                case 1:
                    monster_->load("img/ramos.png");
                    break;
                case 2:
                    monster_->load("img/pique.png");
                    break;
                }
            }
            else
            {
                type_ = rand()%2;
                switch (type_)
                {
                case 0:
                    monster_->load("img/Oblak.png");
                    break;
                case 1:
                    monster_->load("img/Courtois.png");
                    break;
                }
            }
            Monsters.push_back(monster_);
        }
    }
}

void generatePlatforms(vector<Platform*> &platforms)
{
    for (int i = 0; i < PLATFORMS_COUNT; i++)
    {
        Platform* platform_ = new Platform;
        if (i == 0)
            platform_->setPos(WINDOW_WIDTH/2 - PLATFORM_WIDTH/2, WINDOW_HEIGHT - (i+1)*3*PIXEL);
        else
            platform_-> setPos(Random(0, 29*PIXEL), WINDOW_HEIGHT - (i+1)*3*PIXEL);
        platform_ -> load("img/platform.png");
        platform_ -> setType(1);

        platforms.push_back(platform_);
    }
}

void updatePlatforms(vector<Platform*> &platforms, MainObject &Player, int &score, bool &scroll)
{
    for (int i = 0; i < PLATFORMS_COUNT; i++)
    {
        Platform* p = platforms[i];
        if (p->get_y_pos() <= WINDOW_HEIGHT)
        {
            p->Move(Player.get_y_vel(), scroll);
            p->Render();
        }
        else
        {
            platforms.erase(platforms.begin() + i);
            p->~Platform();
            if (p != NULL)
            {
                delete p;
                p = NULL;
            }
            Platform* p_ = new Platform;
            p_->setType(score);
            p_->load("img/platform.png");
            if (score < 3000)
            {
                p_->setPos(Random(0, 29*PIXEL), platforms.back()-> get_y_pos() - Random(3*PIXEL, 8*PIXEL));
                if (rand()%5 == 2)
                    p_->setType(2);
                else
                    p_->setType(1);
            }
            else if (score < 6000)
            {
                p_->setPos(Random(0, 29*PIXEL), platforms.back()-> get_y_pos() - Random(3*PIXEL, 14*PIXEL));
                if (rand()%4 == 1)
                    p_->setType(2);
                else
                    p_->setType(1);
            }
            else
            {
                p_->setPos(Random(0, 29*PIXEL), platforms.back()-> get_y_pos() - Random(8*PIXEL, 16*PIXEL));
                if (rand()%2 == 1)
                    p_->setType(2);
                else
                    p_->setType(1);
            }

            platforms.push_back(p_);
        }
    }
}


