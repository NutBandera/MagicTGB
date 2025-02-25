#pragma once
#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h"
#include "Audio.h"
#include "ManaCrystal.h"
#include <list>
#include <fstream>
#include <sstream>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;
	list<Tile*> tiles;
	void keysToControls(SDL_Event event);
	int newCrystalTime = 10;
	int newEnemyAttack = 10;
	void mouseToControls(SDL_Event event); 
	
	Actor* messageGuide;
	Actor* messageWin;
	Actor* messageLose;
	Actor* messagePause;

	Audio* audioDie;

	bool pause;
	bool guide;
	bool winGame;
	bool loseGame;

	// Elementos de interfaz
	Actor* buttonJump;
	Actor* buttonShoot;

	Player* player;
	Background* background;
	Space* space;

	Actor* currentEnemyForPlayer;
	Actor* currentEnemyForEnemy;

	Audio* audioBackground;

	Text* textManaPlayer;
	Actor* backgroundManaPlayer;
	Text* textManaEnemy;
	Actor* backgroundManaEnemy;
	Text* textPlayerLife;
	Actor* backgroundPlayerLife;
	Text* textEnemyLife;
	Actor* backgroundEnemyLife;

	bool controlContinue = false;
	bool controlShoot = false;
	bool controlConjuro = false;
	bool controlCriatura = false;
	bool controlEncantamiento = false;
	bool controlReset = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	bool saved = false;

	Enemy* enemy;
	list<ManaCrystal*> manaCrystals;
	list<Creature*> playerCreatures;
	list<Creature*> enemyCreatures;

	Actor* buttonReset;
};