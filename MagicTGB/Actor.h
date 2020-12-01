#pragma once
#include "Game.h"

class Actor {
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw();
	bool isOverlap(Actor* actor);
	bool isInRender();
	bool containsPoint(int pointX, int pointY);
	virtual void reduceLife(int damage);
	virtual bool die();
	bool isOver(Actor* actor);
	bool clicked = false;
	virtual int getLife();
	int invulnerableTime = 0;
	SDL_Texture* texture;
	float x;
	float y;
	float vx; // velocidad eje x
	float vy; // velocidad eje y
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	bool outRight;
	bool outLeft;
	int getVX();
	Game* game;

	bool collisionDown = false;
};
