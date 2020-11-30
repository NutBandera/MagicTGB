#include "Enemy.h"
#include "Ghost.h"


Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 140, 200, game) {
	aIdle = new Animation("res/Enemy/idle.png", width, height, 672, 92, 3, 8, false, game);
	aRunningFront = new Animation("res/Enemy/run-front.png", width, height, 672, 111, 3, 8, false, game);
	aRunningBackwards = new Animation("res/Enemy/run-backwards.png", width, height, 592, 111, 3, 8, false, game);
	aDying = new Animation("res/Enemy/die.png", width, height, 1747, 172, 6, 7, false, game);
	aAttacking = new Animation("res/Enemy/attack.png", width, height, 2000, 121, 3, 8, false, game);
	aDead = new Animation("res/Enemy/dead.png", width, height, 168, 121, 6, 1, false, game);
	animation = aIdle;
	audioAttack = new Audio("res/audio-attack.wav", false);
	state = game->stateMoving;
}

void Enemy::update(list<Creature*> creatures, list<ManaCrystal*> crystals) {
	bool endAnimation = animation->update();

	if (invulnerableTime > 0) {
		invulnerableTime--;
	}
	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}

	if (state == game->stateMoving) {
		if (vx < 0) {
			animation = aRunningFront;
		}
		else if (vx > 0) {
			animation = aRunningBackwards;
		}
		if (vx == 0) {
			animation = aIdle;
		}
	}

	if (state == game->stateShooting) {
		animation = aAttacking;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	attackCreatures(creatures);
	if (creatures.size() == 0) {
		takeMana(crystals); 
	}

}

void Enemy::draw(float scrollX) {
	if (invulnerableTime == 0) {
		animation->draw(x, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x, y);
		}
	}
}

int Enemy::getLife() {
	return life;
}

void Enemy::reduceLife(int damage) {
	if (invulnerableTime <= 0 && life > 0) {
		invulnerableTime = 70;
		life -= damage;
	}
}

bool Enemy::die() {
	animation = aDying;
	bool endAnimation = animation->update();
	return endAnimation;
}

void Enemy::attackCreatures(list<Creature*>creatures) {
	if (creatures.size() > 0) {
		attack(creatures.front());
	}
}

void Enemy::attack(Creature* creature) {
	if (creature->x > WIDTH / 2 && creature->getLife() > 0 && abs(x-creature->x) <= 30) { 
		state = game->stateShooting;
		creature->reduceLife(damage);
	}
}

void Enemy::takeMana(list<ManaCrystal*> crystals) {
	if (crystals.size() > 0 && crystals.front()->x > WIDTH / 2) {
		goTo(crystals.front()->x);
	}
	else {
		vx = 0;
	}
}

int Enemy::getMana() {
	return mana;
}

void Enemy::increaseMana(int mana) {
	this->mana += mana;
}

void Enemy::goTo(int pos) {
	if (pos > x) {
		vx = 2;
	}
	else if (pos < x) {
		vx = -2;
	}
}

Creature* Enemy::createCreature() {
	if (mana >= 2) {
		state = game->stateShooting;
		mana -= 2;
		audioAttack->play();
		return new Ghost(x - 50, HEIGHT - 55, game);
	}
	return NULL;
}

int Enemy::conjuro() {
	if (mana >= 10) {
		state = game->stateShooting;
		mana -= 10;
		audioAttack->play();
		return 4;
	}
	return 0;
}