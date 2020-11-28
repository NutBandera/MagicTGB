#include "Creature.h"

Creature::Creature(int x, int y, Game* game, Animation* aIdle, Animation* aRunning, Animation* aAttacking,
	Animation* aDying)
	: Actor("res/jugador.png", x, y, 50, 50, game) {

	this->aIdle = aIdle;
	this->aRunning = aRunning;
	this->aAttacking = aAttacking;
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
		animation = aAttacking;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	if (state == game->stateMoving) {
		if (vx == 0) {
			animation = aIdle;
		}
		else {
			animation = aRunning;
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
	//Cuando la distancia entre tú y tu enemigo sea menor de 10 -> parar y atacar
	if (side == 0) {
		if (e->x - x <= 30) { // crete get x()
			vx = 0;
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
		if (x - e->x <= 30) {
			vx = 0;
			attack(e);
		}
		else {
			if (e->x < x) { // or equal ??
				vx = -2;
			}
			else {
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
	if (e->getLife() <= 0) {
		e->die();
	}
}

void Creature::reduceLife(int damage) {
	if (invulnerableTime <= 0 && life > 0) {
		invulnerableTime = 50;
		life -= damage;
	}
}

bool Creature::die() {
	life = 0;
	return true;
}

int Creature::getLife() {
	return life;
}