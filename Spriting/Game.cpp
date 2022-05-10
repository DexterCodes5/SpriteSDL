#include "Game.h"
#include "Colors.h"

Game::Game( SDL& iSdl )
{
	// Link up the static reference to this Game object inside Sprite:
	Sprite::game = this;
	sdl = &iSdl;

	sprite = new Sprite( "fruits", "fruits.png" );

	// Create game sprites
	bkgColor = SDL_ColorMake( 0, 143, 217, 255 );
}

Game::~Game()
{
	delete sprite;
}

void Game::update()
{
	// Get controller inputs first:
	controller.update();

	// Use the controller state to change gamestate
	if( controller.keystate[SDL_SCANCODE_UP] )
		sprite->rect.y--;
	if( controller.keystate[SDL_SCANCODE_DOWN] )
		sprite->rect.y++;
	if( controller.keystate[SDL_SCANCODE_LEFT] )
		sprite->rect.x--;
	if( controller.keystate[SDL_SCANCODE_RIGHT] )
		sprite->rect.x++;

	// let the game objects update themselves
	sprite->update();
}

void Game::draw()
{
	// Set the background's color,
	sdl->setColor( bkgColor );

	// clears the bkg to bkgColor
	SDL_RenderClear( sdl->renderer );
	
	// ask the sprite to draw itself
	sprite->draw();
	
	SDL_RenderPresent( sdl->renderer );
}

