#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

// Valores generales
#define WIDTH 480
#define HEIGHT 320

#include "Layer.h"
class Layer;

enum class GameInputType {
	KEYBOARD, MOUSE
};

class Game
{
public:
	Game();
	void loop();
	void scale();
	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures; // map - cache
	bool scaledToMax = false;
	float scaleLower = 1;
	TTF_Font* font;
	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* gameLayer;
	Layer* menuLayer;
	Layer* layer;

	int const stateMoving = 1;
	int const stateJumping = 2;
	int const stateDying = 3;
	int const stateShooting = 4;

	int const orientationRight = 1;
	int const orientationLeft = 2;

	GameInputType input = GameInputType::KEYBOARD;

};
