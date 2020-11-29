#pragma once
#include "Actor.h"
#include "Animation.h"

class Creature : public Actor
{
public:
	Creature(int x, int y, Game* game, Animation* aIdle, Animation* aRunning, Animation* aAttacking,
		Animation* aDying);

	int life;
	int getLife() override;
	int damage;
	void attack(Actor* enemy);
	void increaseLife(int points);
	void reduceLife(int damage) override;
	void doubleAttack();
	void update(Actor* enemy);
	void draw();
	void moveToEnemy(Actor* enemy);

	Actor* enemy;

	int state;
	int side; // 0 - left , 1 - right -> 

	Animation* aIdle;
	Animation* aRunning;
	Animation* aAttacking;
	Animation* aDying;
	Animation* animation;
};

