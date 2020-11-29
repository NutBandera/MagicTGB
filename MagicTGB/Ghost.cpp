#include "Ghost.h"

Ghost::Ghost(int x, int y, Game* game)
	: Creature(x, y, game, aIdle, aRunning, aAttackingRight, aAttackingLeft, aDying) {

	aIdle = new Animation("res/Fantasma/idle.png", width, height, 4000, 231, 6, 11, false, game);
	aRunning = new Animation("res/Fantasma/run.png", width, height, 4000, 231, 6, 11, false, game);
	aAttackingRight = new Animation("res/Fantasma/attack.png", width, height,
		4000, 231, 2, 11, false, game);
	aAttackingLeft = new Animation("res/Fantasma/attack.png", width, height,
		4000, 231, 2, 11, false, game);
	aDying = new Animation("res/RedPlayer/die.png", width, height,
		1400, 128, 6, 7, false, game);
	animation = aIdle;
	damage = 2;
	life = 5;
	side = 1;
}