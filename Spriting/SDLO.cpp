#include "SDLO.h"
#include "Sprite.h"

// ctor requires just window width & height
SDL::SDL(const char* title, int windowWidth, int windowHeight):window(0), screenSurface(0), renderer(0),
size(windowWidth, windowHeight)
{
	Sprite::sdl = this;
	
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		error( "SDL init error: %s\n", SDL_GetError() );
		exit( 1 );
	}

	window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN );
	if( !window )
	{
		error("Window could not be created! error: %s\n", SDL_GetError());
		exit( 1 );
	}
	
	// retrieve the surface (collection of pixels) of the window
	screenSurface = SDL_GetWindowSurface( window );
	
	// create a hardware accelerated renderer
	// that displays only once per refresh interval
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	// Turn on alpha blending
	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );
}

SDL::~SDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void SDL::setColor( SDL_Color color )
{
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
}

// Draws you a simple line
void SDL::line( int startX, int startY, int endX, int endY, SDL_Color color )
{
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
	SDL_RenderDrawLine( renderer, startX, startY, endX, endY );
}

void SDL::rect( int x, int y, int w, int h, SDL_Color color )
{
	SDL_Rect rect = { x, y, w, h };
	setColor( color );
	SDL_RenderDrawRect( renderer, &rect );
}

void SDL::fillRect( int x, int y, int w, int h, SDL_Color color )
{
	SDL_Rect rect = { x, y, w, h };
	setColor( color );
	SDL_RenderFillRect( renderer, &rect );
}

void SDL::drawTexture( SDL_Rect rect, SDL_Texture* tex )
{
	SDL_RenderCopy( renderer, tex, NULL, &rect );
}

SDL_Surface* SDL::loadSurface( string filename )
{
	return IMG_Load( filename.c_str() );  // REQUIRES SDL_IMAGE 2.0!!  https://www.libsdl.org/projects/SDL_image/
}

SDL_Texture* SDL::loadTexture( string filename )
{
	map<string,SDL_Texture*>::iterator iter = texes.find( filename );
	if( iter != texes.end() )
	{
		warning( "%s already loaded", filename.c_str() );
		return iter->second;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface( renderer, loadSurface(filename) );
	SDL_SetTextureBlendMode( tex, SDL_BLENDMODE_BLEND );
	texes[ filename ] = tex;
	return tex;
}
