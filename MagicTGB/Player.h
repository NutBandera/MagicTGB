#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Audio.h"
#include "Enemy.h"
#include "Creature.h"
#include <list>

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void draw() override;
	void reduceLife(int damage) override;
	bool die() override;
	void increaseMana(int mana);
	void attack(list<Creature*> creatures);

	int conjuro();
	void encantamiento(list<Creature*> creatures);
	Creature* crearCriatura();

	int life = 20;
	int mana = 20;
	int damage = 2;
	int getMana();
	int getLife() override;

	Animation* aIdle;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aAttacking;
	Animation* aDying;
	Animation* animation;

	Audio* audioAttack;

	int state;
};

enum class State { 
	IDLE,
	RUNNING
};


