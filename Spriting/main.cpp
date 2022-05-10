#include <stdio.h>
#include <string>
using namespace std;

#include "SDLO.h"
#include "Game.h"
#include "Sprite.h"
#include <time.h>

//      ___           ___           ___                       ___                       ___           ___     
//     /\  \         /\  \         /\  \          ___        /\  \          ___        /\__\         /\  \    
//    /::\  \       /::\  \       /::\  \        /\  \       \:\  \        /\  \      /::|  |       /::\  \   
//   /:/\ \  \     /:/\:\  \     /:/\:\  \       \:\  \       \:\  \       \:\  \    /:|:|  |      /:/\:\  \  
//  _\:\~\ \  \   /::\~\:\  \   /::\~\:\  \      /::\__\      /::\  \      /::\__\  /:/|:|  |__   /:/  \:\  \ 
// /\ \:\ \ \__\ /:/\:\ \:\__\ /:/\:\ \:\__\  __/:/\/__/     /:/\:\__\  __/:/\/__/ /:/ |:| /\__\ /:/__/_\:\__\
// \:\ \:\ \/__/ \/__\:\/:/  / \/_|::\/:/  / /\/:/  /       /:/  \/__/ /\/:/  /    \/__|:|/:/  / \:\  /\ \/__/
//  \:\ \:\__\        \::/  /     |:|::/  /  \::/__/       /:/  /      \::/__/         |:/:/  /   \:\ \:\__\  
//   \:\/:/  /         \/__/      |:|\/__/    \:\__\       \/__/        \:\__\         |::/  /     \:\/:/  /  
//    \::/  /                     |:|  |       \/__/                     \/__/         /:/  /       \::/  /   
//     \/__/                       \|__|                                               \/__/         \/__/    

int main(int argc, char* args[])
{
	srand(time(0));
	SDL sdl( "Spriting", 1800, 1000 );
	Game game( sdl );
	
	bool gameRunning=true;
	while( gameRunning )
	{
		SDL_Event e;
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
			{
				gameRunning = false;
			}
		}
		
		// Update the game, update() the sprites, etc
		game.update();

		// Draw out the new state
		game.draw();
	}
	
	return 0;
}





