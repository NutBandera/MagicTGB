#pragma once
#include "Layer.h"
#include "Actor.h"
#include "Background.h"

class MenuLayer :
	public Layer
{
public:
	MenuLayer(Game *game);
	void init() override;
	void draw() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);
	bool controlContinue = false;
	bool controlControls = false;
	bool controlGuide = false;
	Background* background;
	Actor* buttonPlay;

};

