#include "Player.h"
#include "Goblin.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 200, 200, game) {

	aIdle = new Animation("res/Player/idle.png", width, height, 936, 142, 6, 6, false, game);
	aRunningRight = new Animation("res/Player/run-right.png", width, height, 1248, 142, 4, 8, false, game);
	aRunningLeft = new Animation("res/Player/run-left.png", width, height, 1248, 142, 4, 8, false, game);
	aAttacking = new Animation("res/Player/attack.png", width, height,
		1248, 142, 3, 8, false, game);
	aDying = new Animation("res/Player/die.png", width, height,
		1092, 142, 6, 7, false, game);
	animation = aIdle;
	
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

void Player::draw() {
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
			creature->reduceLife(damage);
		}
	}
}


// Inferno - 10 points of mana
int Player::conjuro() {
	if (mana >= 10) {
		state = game->stateShooting;
		mana -= 10;
		audioAttack->play();
		return 4;
	}
	return 0;
}

// Fervor - 10 points of mana 
void Player::encantamiento(list<Creature*> creatures) {
	if (mana >= 10 && creatures.size() > 0) {
		state = game->stateShooting;
		audioAttack->play();
		for (auto const& creature : creatures) {
			creature->doubleAttack();
		}
		mana -= 10;
	}
}

// 5 points of mana
Creature* Player::crearCriatura() {
	if (mana >= 5) {
		state = game->stateShooting;
		mana -= 5;
		audioAttack->play();
		return new Goblin(x + 50, HEIGHT - 55, game);
	}
	return NULL;
}



