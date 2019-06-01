#ifndef __SPRITE_H__
#define __SPRITE_H__

# include <SDL2/SDL.h>

struct sprite {
	std::string color;
	int used;
    SDL_Surface* sprite;
    SDL_Texture* texture;
};

#endif