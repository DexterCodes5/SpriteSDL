#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sdl.h>

// handles user input and modifies the game state based on that
class Controller
{
public:
	// last mouse x & y displacements
	int mouseX, mouseY;

	// the up/down position of all keys on the keyboard.
	// check if a key is down by using its SCANCODE:
	// eg keystate[SDL_SCANCODE_UP] will be nonzero if
	// that key is currently down
	const Uint8 *keystate;

	Controller();
	
	// Updates the controller -- call once per frame
	void update();
};

#endif