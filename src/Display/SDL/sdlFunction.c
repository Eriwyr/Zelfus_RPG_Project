#include "sdlFunction.h"

void actionMoveSdl(int * directionMoving, Position * currentPos, int direction){


	*directionMoving = direction;

	switch(direction){
		case DOWN:
			currentPos->y += 2;
		break;

		case UP:
			currentPos->y -= 2;
		break;

		case RIGHT:
			currentPos->x += 2;
		break;

		case LEFT:
			currentPos->x -= 2;
		break;
	}
}


void sdlOpen(){

	SDL_Init(SDL_INIT_VIDEO);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }

    SDL_ShowCursor(SDL_DISABLE);


    if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
   		printf("%s", Mix_GetError());
	}
}

void sdlClose(SDL_Window * screen, SDL_Renderer * renderer){

	SDL_DestroyWindow(screen);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}