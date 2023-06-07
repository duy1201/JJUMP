#ifndef GAMEBASE_H_
#define GAMEBASE_H_

#include "RenderWindow.h"
#include "MainObject.h"
#include "Platform.h"
#include "ThreatObject.h"
#include "Coin.h"
#include "Text.h"
#include "Button.h"
#include "Time.h"
#include<sstream>

bool MenuState();
bool ChooseCharState(MainObject &Player);
bool GameOverState(int &Score);
void generatePlatforms(vector<Platform*> &platforms);
void updatePlatforms(vector<Platform*> &platforms,
                     MainObject &Player, int &score, bool &scroll);
void updateMonsters(vector<ThreatObject*> &Monsters, MainObject &Player,
                    vector<Platform*> &platforms, bool &scroll);

#endif // GAMEBASE_H_
