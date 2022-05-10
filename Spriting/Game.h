#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "SDLO.h"
#include "Sprite.h"
#include "Controller.h"

class Game
{
private:
	// The SDL object, which allows us to draw and play sounds
	SDL* sdl;

	// OUR SPRITE/game character
	Sprite* sprite;
	
	SDL_Color bkgColor;	// the current background color

	// An object to represent the game controller
	Controller controller;

public:
	Game( SDL& iSdl );
	~Game();
	void update();
	void draw();
};

#endif