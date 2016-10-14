#include "monsterSdl.h"

void initMonsterSprites(MonsterSdl * monsterSdl, SDL_Renderer * renderer){
	monsterSdl->monsterSpriteSheet = loadImage("data/Image/monster.png", renderer);
}
 
 

void monsterSdlFree(MonsterSdl * monsterSdl){
	if (monsterSdl->monsterSpriteSheet != NULL){
		SDL_DestroyTexture(monsterSdl->monsterSpriteSheet);
		monsterSdl->monsterSpriteSheet = NULL;
	}
	free(monsterSdl->currentPos);
	monsterSdl->currentPos=NULL;
}

void monsterSdlInit(MonsterSdl *monsterSdl, Position * pos, SDL_Renderer * renderer){
 	
 	monsterSdl->monsterSpriteSheet=NULL;
	initMonsterSprites(monsterSdl, renderer);
	monsterSdl->currentPos=NULL;

	monsterSdl->direction = RIGHT;
	
	monsterSdl->frameNumber = 0;
	
	monsterSdl->id = 1;
	
	monsterSdl->frameTimer = TIME_BETWEEN_2_FRAMES_MONSTER;
	
	monsterSdl->currentPos = malloc(sizeof(Position));
	
	monsterSdl->isIdle=1;

	
	monsterSdl->frameMax = 3;
	 
	monsterSdl->widthSprite = MONSTER_WIDTH;
	monsterSdl->heightSprite = MONSTER_HEIGTH;
	setPosX(monsterSdl->currentPos, getPosX(pos)*64);
	setPosY(monsterSdl->currentPos, getPosY(pos)*64);
	// monsterSdl->yPix = getPosX(getPositionMonster(monster))*MONSTER_HEIGTH;
}

MonsterSdl* monsterSdlCreate(Position * pos, SDL_Renderer * renderer){
	MonsterSdl* monsterSdl;
	monsterSdl = malloc(sizeof(MonsterSdl));
	monsterSdlInit(monsterSdl, pos, renderer);
	return monsterSdl;
}

void monsterSdlDestroy(MonsterSdl ** monsterSdl){
	monsterSdlFree(*monsterSdl);
	free(*monsterSdl);
	*monsterSdl = NULL;
}


void drawMonster(MonsterSdl *monsterSdl, SDL_Renderer * renderer){

	if (monsterSdl->frameTimer <= 0){
	
		monsterSdl->frameTimer = TIME_BETWEEN_2_FRAMES_MONSTER;
	 
		if(monsterSdl->isIdle == 0){
			monsterSdl->frameNumber++;
		}
		 
		
		if (monsterSdl->frameNumber >= monsterSdl->frameMax)
			monsterSdl->frameNumber = 0;
	 
	} else 
		monsterSdl->frameTimer--;
	 
	 
	

	SDL_Rect dest;
	

	dest.x = getPosX(monsterSdl->currentPos);
	dest.y = getPosY(monsterSdl->currentPos);
	dest.w = 48;
	dest.h = 48;
	 
	
	SDL_Rect src;
	 
	
	
	src.x = monsterSdl->frameNumber * monsterSdl->widthSprite;
	src.w = monsterSdl->widthSprite;
	src.h = monsterSdl->heightSprite;
	 
	
	
	
	src.y = monsterSdl->direction * monsterSdl->heightSprite;
	 
	
	
	if(SDL_RenderCopyEx(renderer, monsterSdl->monsterSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererMonsterCopy\n");
	}
 
}	 


int getIdMonsterSdl(const MonsterSdl* monsterSdl){
	return monsterSdl->id;
}

void setIdMonsterSdl(MonsterSdl* monsterSdl, const int id){
	monsterSdl->id = id;
}

Position* getCurrentPosMonsterSdl(const MonsterSdl* monsterSdl){

	return monsterSdl->currentPos;
}

int* getDirectionMonsterSdl(MonsterSdl* monsterSdl){	
	return &monsterSdl->direction;
}

void setIsIdleMonsterSdl(MonsterSdl * monsterSdl, int idle){
	monsterSdl->isIdle = idle;
}

void monsterSdlTest(){
	
	MonsterSdl *monsterSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	Position* position;
	
	position=malloc(sizeof(position));
	
	setPosX(position,0);
	setPosY(position,0);
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	
	monsterSdl =malloc(sizeof(MonsterSdl));

	printf("==== Tests of MonsterSdl ====\n");
	
	printf("Initializing using monsterSdlInit... ");
	monsterSdlInit(monsterSdl, position,renderer);
	assert(monsterSdl->currentPos != NULL);
	printf("Ok.\n");

	
	printf("Test of initMonsterSprites...");
	initMonsterSprites(monsterSdl,renderer);
	assert(monsterSdl->monsterSpriteSheet != NULL);
	printf("Ok.\n");

	printf("Test of monsterSdlFree...");
	monsterSdlFree(monsterSdl);
	assert(monsterSdl->monsterSpriteSheet == NULL);

	assert(monsterSdl->currentPos==NULL);

	printf("Ok.\n");

	free(monsterSdl);
	monsterSdl =NULL;

	printf("Test of monsterSdlCreate...");
	monsterSdl=monsterSdlCreate(position,renderer);
	assert(monsterSdl != NULL);
	printf("Ok.\n");

	printf("Test of monsterSdlDestroy...");
	monsterSdlDestroy(&monsterSdl);
	assert(monsterSdl == NULL);
	printf("Ok.\n");

	free(position);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
	
	printf("====The tests went well ====\n\n");

}

