#include "Goblin.h"

Goblin::Goblin(int x, int y, Game* game)
	: Creature(x, y, game, aIdle, aRunning, aAttacking, aDying) {

	aIdle = new Animation("res/Goblin/idle.png", width, height, 4000, 306, 6, 11, false, game);
	aRunning = new Animation("res/Goblin/run.png", width, height, 4000, 304, 6, 11, false, game);
	aAttacking = new Animation("res/Goblin/attack.png", width, height,
		4000, 288, 2, 11, false, game);
	aDying = new Animation("res/RedPlayer/die.png", width, height,
		1400, 128, 6, 7, false, game);
	animation = aIdle;
	damage = 2;
	life = 5;
	side = 0;
}
