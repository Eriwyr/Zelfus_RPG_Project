#ifndef SDL_FUNCTION_H
#define SDL_FUNCTION_H

#include "Position.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#ifndef SCREEN_WIDTH
	#define SCREEN_WIDTH 1344
#endif //SCREEN_WIDTH
#ifndef SCREEN_HEIGHT
	#define SCREEN_HEIGHT 700
#endif //SCREEN_HEIGHT

void actionMoveSdl(int * directionMoving, Position * currentPos, int direction);
void sdlOpen();
void sdlClose(SDL_Window * screen, SDL_Renderer * renderer);

#endif // SDL_FUNCTION_H
