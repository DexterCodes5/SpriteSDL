#include "Sprite.h"
#include "Game.h"
#include "Colors.h"

SDL* Sprite::sdl;
Game* Sprite::game;

void Sprite::defaults()
{
	color = SDL_ColorMake( 255, 255, 255, 255 );
	hidden = false;
}

Sprite::Sprite(string iname)
{
	defaults();
	name = iname;
	tex = 0;
}

Sprite::Sprite(string iname, SDL_Texture* iTex)
{
	defaults();
	name = iname;
	tex = iTex;
	retrieveTexSize();
}

Sprite::Sprite(string iname, string filename)
{
	defaults();
	name = iname;
	tex = sdl->loadTexture(filename);
	retrieveTexSize();
}

void Sprite::boundTopAndBottom()
{
	// If I leave the top of the screen..
	if( rect.top() < 0 )
	{
		// just set the top of my rect to 0
		rect.y = 0;
	}

	// if I leave the bottom of the screen..
	if( rect.bottom() > sdl->getSize().y )
	{
		// put the _bottom_ of my rect @ bottom of screen
		rect.y = sdl->getSize().y - rect.h;
	}
}

void Sprite::boundLeftAndRight()
{
	// if exit left..
	if( rect.left() < 0 )
	{
		// just put left edge of my rect at left edge of world
		rect.x = 0;
	}
	if( rect.right() > sdl->getSize().x )
	{
		rect.x = sdl->getSize().x - rect.w;
	}
}

void Sprite::show()
{
	hidden = false;
}

void Sprite::hide()
{
	hidden = true;
}

void Sprite::update()
{
	// Ensure the change to my position didn't take me out of bounds
	boundTopAndBottom();
	boundLeftAndRight();
}

void Sprite::draw()
{
	if( hidden )
		return ; // just don't draw
	
	sdl->setColor( color );
	if( !tex )
	{
		// no texture, so draw a solid rect
		sdl->fillRect( rect.x, rect.y, rect.w, rect.h, color );
	}
	else
	{
		// Convert our floating pt rect to an int-based rect
		SDL_Rect r = { rect.x, rect.y, rect.w, rect.h };
		sdl->drawTexture( r, tex );
	}
}

void Sprite::retrieveTexSize()
{
	int w,h;
	SDL_QueryTexture( tex, 0, 0, &w, &h );
	rect.w=w, rect.h=h;
}
