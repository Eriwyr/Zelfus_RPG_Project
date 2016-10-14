#include "characSdl.h"

void initPlayerSprites(CharacSdl * characSdl, SDL_Renderer * renderer){
	characSdl->playerSpriteSheet = loadImage("data/Image/perso.png", renderer);
	characSdl->attack2= loadImage("data/Image/attack2.png", renderer);
}
 
 

void characSdlFree(CharacSdl * characSdl){
	int i;
	if (characSdl->playerSpriteSheet != NULL){
		SDL_DestroyTexture(characSdl->playerSpriteSheet);
		characSdl->playerSpriteSheet = NULL;
	}
	if (characSdl->attack2 != NULL){
		SDL_DestroyTexture(characSdl->attack2);
		characSdl->attack2 = NULL;
	}
	
	for(i=0;i<characSdl->nbSpell;i++){
		spellSdlDestroy(&characSdl->spellSdl[i]);
	}
	
	free(characSdl->spellSdl);
	characSdl->spellSdl =NULL;
	free(characSdl->currentPos);
	characSdl->currentPos=NULL;
}

void characSdlInit(CharacSdl *characSdl, Character * player, SDL_Renderer *renderer){

	int i;
	char idS[10];
	char spellFile[CHAR_SIZE_MAX];
	characSdl->currentPos = malloc(sizeof(Position));
	characSdl->playerSpriteSheet = NULL;
	characSdl->attack2 = NULL;
 	initPlayerSprites(characSdl, renderer);

 	characSdl->id = getIdCharacter(player);
	characSdl->direction = RIGHT;
	characSdl->actualAttack=1;
	characSdl->frameNumber = characSdl->id*3;
	characSdl->isIdle = 1;

	setPosX(characSdl->currentPos, 0);
	setPosY(characSdl->currentPos, 0);
	 
	characSdl->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
	 
	characSdl->frameMax = (characSdl->id*3)+3;
	 
	characSdl->widthSprite = PLAYER_WIDTH;
	characSdl->heightSprite = PLAYER_HEIGTH;
	setPosX(characSdl->currentPos, getPosX(getPositionCharacter(player))*64);
	setPosY(characSdl->currentPos, getPosY(getPositionCharacter(player))*64);

	characSdl->nbSpell = getNbSpell(getSpellBarCharacter(player));
	characSdl->spellSdl = malloc(characSdl->nbSpell*sizeof(SpellSdl *));
	for(i=0;i<characSdl->nbSpell;i++){
		sprintf(idS, "%d", i+2);
		strcpy(spellFile, "data/Image/attack");
		strcat(spellFile, idS);
		strcat(spellFile, ".png");
		characSdl->spellSdl[i] = spellSdlCreate(getSpell(getSpellBarCharacter(player), i), renderer, spellFile);
	}
}

CharacSdl* characSdlCreate(Character * player, SDL_Renderer * renderer){
	CharacSdl * characSdl;
	characSdl = malloc(sizeof(CharacSdl));
	characSdlInit(characSdl, player, renderer);

	return characSdl;
}

void characSdlDestroy(CharacSdl ** characSdl){
	characSdlFree(*characSdl);
	free(*characSdl);
	*characSdl = NULL;
}


void drawPlayer(CharacSdl *characSdl, SDL_Renderer * renderer){

	
	if (characSdl->frameTimer <= 0){
	
		characSdl->frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
	 
		if(characSdl->isIdle == 0){
			characSdl->frameNumber++;
		}
		 
		
		if (characSdl->frameNumber >= characSdl->frameMax)
			characSdl->frameNumber = characSdl->id*3;
	 
	} else 
		characSdl->frameTimer--;
	 
	 
	

	SDL_Rect dest;
	

	dest.x = getPosX(characSdl->currentPos);
	dest.y = getPosY(characSdl->currentPos);
	dest.w = 48;
	dest.h = 48;
	 
	
	SDL_Rect src;
	 
	
	
	src.x = characSdl->frameNumber * characSdl->widthSprite; //à changer avec cste
	src.w = characSdl->widthSprite;
	src.h = characSdl->heightSprite;
	 
	
	
	
	src.y = (characSdl->direction * characSdl->heightSprite)+128;

	
	
	if(SDL_RenderCopyEx(renderer, characSdl->playerSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererCharacCopy\n");
	} 
}

int getXpixCharacSdl(const CharacSdl* characSdl){
	return characSdl->xPix;
}

int getYpixCharacSdl(const CharacSdl* characSdl){
	return characSdl->yPix;
}

SDL_Texture* getSpriteAttack1(const CharacSdl* characSdl){
	return characSdl->attack1;
}

SDL_Texture* getSpriteAttack2(const CharacSdl* characSdl){
	return characSdl->attack2;
}

SDL_Texture* getSpriteAttack3(const CharacSdl* characSdl){
	return characSdl->attack3;
}

Position* getCurrentPosCharacSdl(const CharacSdl * characSdl){
	return characSdl->currentPos;
}

void setcurrentPosCharacSdl(const CharacSdl * characSdl, int x, int y){
	setPosX(characSdl->currentPos, x);
	setPosY(characSdl->currentPos, y);
}

SpellSdl* getSpellSdlIFromCharacSdl(CharacSdl* characSdl, int i){
	assert(i>=0);
	assert(i<characSdl->nbSpell);

	return characSdl->spellSdl[i];
}

int getIsIdleCharacSdl(const CharacSdl* characSdl){
	return characSdl->isIdle;
}

void setIsIdleCharacSdl(CharacSdl* characSdl, int value){
	characSdl->isIdle=value;
}

int* getDirectionCharacSdl(CharacSdl* characSdl){
	return &characSdl->direction;
}

void characSdlTest(){
	
	CharacSdl *characSdl;
	Character *player;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	characSdl =malloc(sizeof(CharacSdl));
	player=characterCreate();
	
	characterInit(player);

	printf("==== Tests of CharacSdl ====\n");
	
	printf("Initializing using characSdlInit... ");
	characSdlInit(characSdl, player,renderer);
	assert(characSdl->currentPos != NULL);
	assert(characSdl->playerSpriteSheet != NULL);
	assert(characSdl->attack2 != NULL);
	assert(characSdl->spellSdl !=NULL);
	assert(characSdl->id == getIdCharacter(player));
	printf("Ok.\n");

	
	printf("Test of initPlayerSprites...");
	initPlayerSprites(characSdl,renderer);
	assert(characSdl->playerSpriteSheet != NULL);
	assert(characSdl->attack2 != NULL);
	printf("Ok.\n");

	printf("Test of characSdlFree...");
	characSdlFree(characSdl);
	assert(characSdl->playerSpriteSheet == NULL);
	assert(characSdl->attack2==NULL);
	assert(characSdl->currentPos==NULL);
	assert(characSdl->spellSdl==NULL);
	printf("Ok.\n");

	free(characSdl);
	characSdl =NULL;

	printf("Test of characSdlCreate...");
	characSdl=characSdlCreate(player,renderer);
	assert(characSdl != NULL);
	printf("Ok.\n");

	printf("Test of characSdlDestroy...");
	characSdlDestroy(&characSdl);
	assert(characSdl == NULL);
	printf("Ok.\n");

	characterDestroy(&player);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
	
	printf("====The tests went well ====\n\n");

}