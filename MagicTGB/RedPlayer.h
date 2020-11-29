#pragma once
#include "Player.h"

class RedPlayer :
	public Player
{
public:
	RedPlayer(float x, float y, Game* game);
	int conjuro() override;
	void encantamiento(list<Creature*>creatures) override;
	Creature* crearCriatura() override;
};

