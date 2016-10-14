#include "mapSdl.h"
 
 
 
void mapSdlInit(MapSdl* mapSdl, char* mapTileset, SDL_Renderer* renderer){
	
	mapSdl->background=NULL;
	mapSdl->mapTileset=NULL;
	mapSdl->background = loadImage("data/Image/Grass.jpg", renderer);
	mapSdl->mapTileset = loadImage(mapTileset, renderer);

}

	 
MapSdl* mapSdlCreate(char* mapTileset, SDL_Renderer * renderer){
	MapSdl * mapSdl;
	mapSdl = malloc(sizeof(MapSdl));

	mapSdlInit(mapSdl, mapTileset, renderer);
	return mapSdl;	
}
 
SDL_Texture *getBackground(MapSdl* mapSdl){
	return mapSdl->background;
}

 
void mapSdlFree(MapSdl* mapSdl){

	if (mapSdl->background != NULL){ 

		SDL_DestroyTexture(mapSdl->background);
		mapSdl->background = NULL;
	}
	if (mapSdl->mapTileset != NULL)
	{
		SDL_DestroyTexture(mapSdl->mapTileset);
		mapSdl->mapTileset = NULL;
	}
	
}

void mapSdlDestroy(MapSdl ** mapSdl){
	mapSdlFree(*mapSdl);
	free(*mapSdl);
	*mapSdl = NULL;
}

void drawMap(MapSdl* mapSdl, Map* map1, SDL_Renderer *renderer){
	int i;
	int j;
	int line, column;
	SDL_Rect dest;
	SDL_Rect src;
	
	for(i=0;i<getWidthMap(map1);i++){
		for(j=0;j<getHeightMap(map1);j++){
			src.x = i*64;
			src.y = j*64;
			line = floor((getElementXYMap(map1, i, j)/10));
			column = getElementXYMap(map1, i, j)- ( line*10);
			src.y = (ceil(line/2)*32 + floor(line/2)*64) +32;
			if(line % 2 == 0){
				src.x = column*32; 
				src.w = 32;
				src.h = 32;
				dest.h = 32;
				dest.w = 32;
	 
 			} else { 
				src.x = column*64; 
				src.w = 64;
				src.h = 64;
				dest.h = 64;
				dest.w = 64;
	 
 			}
			
			dest.x = i*64;
			dest.y = j*64;
			dest.h = 64;
			dest.w = 64;
			if(SDL_RenderCopyEx(renderer, mapSdl->mapTileset, &src, &dest, 0, 0, SDL_FLIP_NONE) < 0){
				printf("Error rendererCopy\n");
			}

			
		}
	}
}



void mapSdlTest(){
	
	MapSdl *mapSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	
	mapSdl =malloc(sizeof(MapSdl));


	printf("==== Tests of MapSdl ====\n");
	
	printf("Initializing using mapSdlInit... ");
	mapSdlInit(mapSdl, "data/Image/mapTileset1.png",renderer);
	assert(mapSdl->background != NULL);
	assert(mapSdl->mapTileset != NULL);
	printf("Ok.\n");

	printf("Test of mapSdlFree...");
	mapSdlFree(mapSdl);
	assert(mapSdl->background == NULL);
	assert(mapSdl->mapTileset == NULL);
	printf("Ok.\n");

	free(mapSdl);
	mapSdl =NULL;

	printf("Test of mapSdlCreate...");
	mapSdl=mapSdlCreate("data/Image/mapTileset1.png",renderer);
	assert(mapSdl != NULL);
	printf("Ok.\n");

	printf("Test of mapSdlDestroy...");
	mapSdlDestroy(&mapSdl);
	assert(mapSdl == NULL);
	printf("Ok.\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
	
	printf("====The tests went well ====\n\n");

}