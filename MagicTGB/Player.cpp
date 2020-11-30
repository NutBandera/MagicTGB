#include "Player.h"

Player::Player(float x, float y, Game* game, Animation* aIdle, Animation* aRunningRight, Animation* aRunningLeft,
	Animation* aAttacking, Animation* aDying)
	: Actor("res/jugador.png", x, y, 200, 200, game) {

	this->aIdle = aIdle;
	this->aRunningRight = aRunningRight;
	this->aRunningLeft = aRunningLeft;
	this->aAttacking = aAttacking;
	this->aDying = aDying;
	
	audioAttack = new Audio("res/audio-attack.wav", false);
	state = game->stateMoving;
}

void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}
	bool endAnimation = animation->update();

	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}


	if (state == game->stateMoving) {
		if (vx < 0) {
			animation = aRunningLeft;
		}
		else if (vx > 0) {
			animation = aRunningRight;
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

}

void Player::moveX(float axis) {
	vx = axis * 3;
}

int Player::getLife() {
	return life;
}

void Player::draw(float scrollX) {
	if (invulnerableTime == 0) {
		animation->draw(x, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x, y);
		}
	}
}


void Player::reduceLife(int damage) {
	if (invulnerableTime <= 0 && life > 0) {
		invulnerableTime = 70; 
		life -= damage;
	}
}

bool Player::die() {
	invulnerableTime = 0;
	animation = aDying;
	bool endAnimation = animation->update();
	return endAnimation;
}

int Player::getMana() {
	return mana;
}

void Player::increaseMana(int mana) {
	this->mana += mana;
}

void Player::attack(list<Creature*> creatures) {
	state = game->stateShooting;
	audioAttack->play();
	for (auto &const creature : creatures) {
		if (abs(x - creature->x) <= 30) {
			creature->reduceLife(2);
		}
	}
}

int Player::conjuro()
{
	return 0;
}

void Player::encantamiento(list<Creature*> creatures) {}

Creature* Player::crearCriatura() 
{
	return NULL;
}



