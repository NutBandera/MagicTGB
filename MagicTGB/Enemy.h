#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Creature.h"
#include "ManaCrystal.h"
#include "Player.h"
#include <list>

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void update(list<Creature*>creatures, list<ManaCrystal*> crystals);
	void draw(float scrollX) override;
	bool die() override;
	void reduceLife(int damage) override;
	int state;
	int life = 20;
	int mana = 20;
	int damage = 4;
	int getMana();
	void increaseMana(int mana);
	int getLife() override;
	void attackCreatures(list<Creature*>creatures);
	void attack(Creature* creature);
	void takeMana(list<ManaCrystal*> crystals);
	void goTo(int x);
	Creature* createCreature();
	int conjuro();

	float vxIntelligence; // eliminar

	Animation* aIdle;
	Animation* aRunningFront;
	Animation* aRunningBackwards;
	Animation* aDying;
	Animation* aDead;
	Animation* aAttacking;
	Animation* animation;

	Audio* audioAttack;
};

