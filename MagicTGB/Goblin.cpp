#include "Goblin.h"

Goblin::Goblin(int x, int y, Game* game)
	: Creature(x, y, game, aIdle, aRunningRight, aRunningLeft, aAttackingRight, aAttackingLeft, aDying) {

	aIdle = new Animation("res/Goblin/idle.png", width, height, 4000, 306, 6, 11, false, game);
	aRunningRight = new Animation("res/Goblin/run.png", width, height, 4000, 304, 6, 11, false, game);
	aRunningLeft = new Animation("res/Goblin/run.png", width, height, 4000, 304, 6, 11, false, game);
	aAttackingLeft = new Animation("res/Goblin/attackleft.png", width, height,
		4000, 288, 2, 11, false, game);
	aAttackingRight = new Animation("res/Goblin/attack-right.png", width, height,
		4000, 288, 2, 11, false, game);
	aDying = new Animation("res/RedPlayer/die.png", width, height,
		1400, 128, 6, 7, false, game);
	animation = aIdle;
	damage = 2;
	life = 5;
	side = 0;
}
