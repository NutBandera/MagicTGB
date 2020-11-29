#include "Player.h"

Player::Player(float x, float y, Game* game, Animation* aIdle, Animation* aRunningRight, Animation* aRunningLeft,
	Animation* aAttacking, Animation* aJumping, Animation* aDying, Animation* aDead)
	: Actor("res/jugador.png", x, y, 300, 300, game) {

	this->aIdle = aIdle;
	this->aRunningRight = aRunningRight;
	this->aRunningLeft = aRunningLeft;
	this->aAttacking = aAttacking;
	this->aDying = aDying;
	this->aDead = aDead;
	
	audioAttack = new Audio("res/audio-attack.wav", false);
	state = game->stateMoving;
}

void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = animation->update();


	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}


	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
		if (state == game->stateDying) {
			state = game->stateDead;
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

	if (state == game->stateJumping) {
		animation = aJumping;
	}

	if (state == game->stateShooting) {
		animation = aAttacking;
	}

	if (state == game->stateDying) {
		animation = aDying;
	}

	if (state == game->stateDead) {
		animation = aDead;
	}
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
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

void Player::jump(int v) {
	if (!onAir) {
		vy = v;
		onAir = true;
	}
}

void Player::reduceLife(int damage) {
	if (invulnerableTime <= 0 && life > 0) {
		invulnerableTime = 20; 
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
		if (creature->x <= x + 50) {
			creature->reduceLife(1);
		}
	}
}

int Player::conjuro()
{
	return 0;
}

void Player::encantamiento(list<Creature*> creatures) {}

Creature* Player::crearCriatura() // leave empty ????? 
{
	cout << "hola";
	return NULL;
}



