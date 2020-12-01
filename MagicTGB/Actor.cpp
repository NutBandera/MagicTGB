#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game) {
	this->game = game;
	texture = game->getTexture(filename);
	this->x = x;
	this->y = y;
	this->fileWidth = width;
	this->fileHeight = height;
	this->width = width;
	this->height = height;

}

int Actor::getLife() {
	return NULL;
}

int Actor::getVX() {
	return vx;
}


void Actor::draw() {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth;
	source.h = fileHeight;
	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;
	SDL_RenderCopyEx(game->renderer, texture, &source, &destination,
		0, nullptr, SDL_FLIP_NONE);
}

bool Actor::isOverlap(Actor * actor)
{
	bool overlap = false;
	if (actor->x - actor->width / 2 <= x +  width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2) {

		overlap = true;
	}
	return overlap;

}

bool Actor::isOver(Actor * actor)
{
	bool overlap = false;
	if (actor->x - actor->width / 2 <= x 
		&& actor->x + actor->width / 2 >= x 
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2) {

		overlap = true;
	}
	return overlap;

}

Actor::~Actor() {
}

bool Actor::isInRender() {
	if (x - width / 2 <= WIDTH && x + width / 2 >= 0
		&& y - height / 2 <= HEIGHT && y + height / 2 >= 0) {
		return true;
	}
	return false;
}

bool Actor::containsPoint(int pointX, int pointY) {
	if (pointY >= y - height / 2 &&
		pointY <= y + height / 2 &&
		pointX <= x + width / 2 &&
		pointX >= x - width / 2) {
		return true;
	}
	return false;
}

void Actor::reduceLife(int damage) {} 
bool Actor::die() {
	return true;
} 

