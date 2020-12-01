#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
}

void MenuLayer::init() {
	background = new Background("res/menu.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	buttonPlay = new Actor("res/boton-jugar.png", WIDTH * 0.5, HEIGHT * 0.4, 150, 53, game);
}

void MenuLayer::draw() {
	background->draw();
	buttonPlay->draw();
	SDL_RenderPresent(game->renderer); 
}


void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			game->input = GameInputType::KEYBOARD;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = GameInputType::MOUSE;
		}
		if (game->input == GameInputType::KEYBOARD) {
			keysToControls(event);
		}
		if (game->input == GameInputType::MOUSE) {
			mouseToControls(event);
		}
	}

	if (controlContinue) {
		game->layer = game->gameLayer;
		controlContinue = false;
	}
}

void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_SPACE: 
			controlContinue = true;
			break;
		}
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (buttonPlay->containsPoint(motionX, motionY)) {
			controlContinue = true;
		}

	}
}

