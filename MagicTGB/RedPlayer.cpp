#include "RedPlayer.h"
#include "Goblin.h"

RedPlayer::RedPlayer(float x, float y, Game* game)
	: Player(x, y, game, aIdle, aRunningRight, aRunningLeft, aAttacking, aDying) {

	aIdle = new Animation("res/Player/idle.png", width, height, 936, 142, 6, 6, false, game);
	aRunningRight = new Animation("res/Player/run-right.png", width, height, 1248, 142, 4, 8, false, game);
	aRunningLeft = new Animation("res/Player/run-left.png", width, height, 1248, 142, 4, 8, false, game); 
	aAttacking = new Animation("res/Player/attack.png", width, height,
		1248, 142, 3, 8, false, game);
	aDying = new Animation("res/Player/die.png", width, height,
		1092, 142, 6, 7, false, game);
	animation = aIdle;
}


// Inferno - 10 points of mana
int RedPlayer::conjuro() {
	if (mana >= 10) {
		state = game->stateShooting;
		mana -= 10;
		audioAttack->play();
		return 4;
	}
	return 0;
}

// Fervor - 10 points of mana 
void RedPlayer::encantamiento(list<Creature*> creatures) {
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
Creature* RedPlayer::crearCriatura() {
	if (mana >= 5) {
		state = game->stateShooting;
		mana -= 5;
		audioAttack->play();
		return new Goblin(x + 50, HEIGHT - 55, game);
	}
	return NULL;
}
