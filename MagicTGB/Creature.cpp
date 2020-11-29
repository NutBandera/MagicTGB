#include "Creature.h"

Creature::Creature(int x, int y, Game* game, Animation* aIdle, Animation* aRunningRight, Animation* aRunningLeft,
	Animation* aAttackingRight, Animation* aAttackingLeft, Animation* aDying)
	: Actor("res/jugador.png", x, y, 50, 50, game) {

	this->aIdle = aIdle;
	this->aRunningRight = aRunningRight;
	this->aRunningLeft = aRunningLeft;
	this->aAttackingRight = aAttackingRight;
	this->aAttackingLeft = aAttackingLeft;
	this->aDying = aDying;

	state = game->stateMoving;
}

void Creature::doubleAttack() {
	damage *= 2;
}

void Creature::update(Actor* e) {
	bool endAnimation = animation->update();

	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}
	if (state == game->stateShooting) {
		if (orientation > 0) {
			animation = aAttackingRight;
		}
		else {
			animation = aAttackingLeft;
		}
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	if (state == game->stateMoving) {
		if (vx == 0) {
			animation = aIdle;
		}
		else if (vx > 0){
			animation = aRunningRight; 
		}
		else {
			animation = aRunningLeft;
		}
	}
	if (e->getLife() > 0) {
		moveToEnemy(e);
	}
	else {
		vx = 0;
	}
}

void Creature::draw() {
	animation->draw(x, y);
}

void Creature::moveToEnemy(Actor* e) {
	if (side == 0) {
		if (abs(e->x - x) <= 30) { // crete get x()
			vx = 0;
			if (x > e->x) {
			}
			else {
			}
			attack(e);
		}
		else {
			if (e->x > x) { // or equal ??
				vx = 2;
			}
			else {
				vx = -2;
			}
		}

	}
	else {
		if (abs(x - e->x) <= 30) {
			vx = 0;
			if (x > e->x) {
				orientation = -1;
			}
			else {
				orientation = 1;
			}
			attack(e);
		}
		else {
			if (e->x < x) { // or equal ??
				orientation = -1;
				vx = -2;
			}
			else {
				orientation = 1;
				vx = 2;
			}
		}

	}

}

void Creature::attack(Actor* e) {
	if (e->getLife() > 0) {
		state = game->stateShooting;
		e->reduceLife(damage);
	}
}

void Creature::reduceLife(int damage) {
	if (invulnerableTime <= 0 && life > 0) {
		invulnerableTime = 50;
		life -= damage;
	}
}

int Creature::getLife() {
	return life;
}