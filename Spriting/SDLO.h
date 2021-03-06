#ifndef SDLO_H
#define SDLO_H

#include <map>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include "Log.h"
#include "Vectorf.h"

// If you link the SDL libraries here, you don't
// have to worry about setting the project settings
#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )
#pragma comment( lib, "SDL2_image.lib" )

// Stores everything to do with SDL, and game assets
class SDL
{
	// asset maps: filename=>SDL_* objects
	map<string, SDL_Texture*> texes;
	Vector2f size;

public:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;

	// ctor requires just window width & height
	SDL(const char *title, int windowWidth, int windowHeight);
	~SDL();
	
	inline Vector2f getSize(){
		return Vector2f( screenSurface->w, screenSurface->h );
	}
	void setColor( SDL_Color color );

	// Draws you a simple line
	void line( int startX, int startY, int endX, int endY, SDL_Color color );
	void rect( int x, int y, int w, int h, SDL_Color color );
	void fillRect( int x, int y, int w, int h, SDL_Color color );
	void drawTexture( SDL_Rect rect, SDL_Texture* tex );
	void playMusic( string musicFile );
	void playSound( string soundFile );
	
	SDL_Surface* loadSurface( string filename );
	SDL_Texture* loadTexture( string filename );
};

#endif