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
	Player(float x, float y, Game* game, Animation* aIdle, Animation* aRunningRight, Animation* aRunningLeft,
		Animation* aAttacking, Animation* aJumping, Animation* aDying, Animation* aDead);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0) override;
	void reduceLife(int damage) override;
	bool die() override;
	int shootCadence = 20;
	int shootTime = 0;
	void jump(int v = -16);
	bool onAir;
	void increaseMana(int mana);
	void attack(list<Creature*> creatures);

	//virtual void conjuro(Enemy* enemy);
	virtual void encantamiento(list<Creature*> creatures);
	virtual Creature* crearCriatura();

	int life = 20;
	int mana = 20;
	int getMana();
	int getLife() override;

	Animation* aIdle;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aAttacking;
	Animation* aJumping;
	Animation* aDying;
	Animation* aDead;
	Animation* animation;

	Audio* audioAttack;

	int state;
};

enum class State { // se usa ?
	IDLE,
	RUNNING
};


