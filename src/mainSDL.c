#include "menuSdl.h"
#include "hudSdl.h"
#include "time.h"

int main(int argc, char const *argv[]){
	srand(time(NULL));

	SDL_Window * screen;
	SDL_Renderer * renderer;

	sdlOpen();
	screen = SDL_CreateWindow("Zelfus",	SDL_WINDOWPOS_CENTERED,
                                  		SDL_WINDOWPOS_CENTERED,
                                  		SCREEN_WIDTH, SCREEN_HEIGHT,
                                  		SDL_WINDOW_SHOWN);
	
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	if (screen == NULL || renderer == NULL){
        printf( "%s\n",SDL_GetError());
        exit(1);
    }




	menu(screen, renderer);

	sdlClose(screen, renderer);
	exit(0);
}


