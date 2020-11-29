#include "Ghost.h"

Ghost::Ghost(int x, int y, Game* game)
	: Creature(x, y, game, aIdle, aRunningRight, aRunningLeft, aAttackingRight, aAttackingLeft, aDying) {

	aIdle = new Animation("res/Fantasma/idle.png", width, height, 4000, 231, 6, 11, false, game);
	aRunningRight = new Animation("res/Fantasma/run-right.png", width, height, 4000, 231, 6, 11, false, game);
	aRunningLeft = new Animation("res/Fantasma/run-left.png", width, height, 4000, 231, 6, 11, false, game);
	aAttackingRight = new Animation("res/Fantasma/attack-right.png", width, height,
		4000, 231, 2, 11, false, game);
	aAttackingLeft = new Animation("res/Fantasma/attack-left.png", width, height,
		4000, 231, 2, 11, false, game);
	aDying = new Animation("res/RedPlayer/die.png", width, height,
		1400, 128, 6, 7, false, game);
	animation = aIdle;
	damage = 2;
	life = 5;
	side = 1;
}