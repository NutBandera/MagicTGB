#include "RedPlayer.h"
#include "Goblin.h"

RedPlayer::RedPlayer(float x, float y, Game* game)
	: Player(x, y, game, aIdle, aRunningRight, aRunningLeft, aAttacking, aJumping, aDying, aDead) {

	aIdle = new Animation("res/RedPlayer/idle.png", width, height, 800, 128, 6, 4, false, game);
	aRunningRight = new Animation("res/RedPlayer/run.png", width, height, 1600, 129, 6, 8, false, game);
	aRunningLeft = new Animation("res/runLeft.png", width, height, 2000, 250, 6, 8, false, game); // modify
	aAttacking = new Animation("res/RedPlayer/attack.png", width, height,
		800, 129, 3, 4, false, game);
	aJumping = new Animation("res/jugador_saltando_derecha.png", width, height,
		160, 40, 6, 2, false, game); // add fall
	aDying = new Animation("res/RedPlayer/die.png", width, height,
		1400, 128, 6, 7, false, game);
	aDead = new Animation("res/RedPlayer/dead.png", width, height,
		216, 52, 6, 1, false, game);
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
