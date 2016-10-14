#include "hudSdl.h"

void initHudSprite(HudSdl * hudSdl, SDL_Renderer * renderer){
	hudSdl->hudSprite = loadImage("data/Image/hud.png", renderer);
	hudSdl->spellBarSprite = loadImage("data/Image/SpellBar.png", renderer);
}


void hudSdlFree(HudSdl * hudSdl){
	int i;

	if (hudSdl->hudSprite != NULL){
		SDL_DestroyTexture(hudSdl->hudSprite);
		hudSdl->hudSprite = NULL;
	}

	if (hudSdl->spellBarSprite != NULL){
		SDL_DestroyTexture(hudSdl->spellBarSprite);
		hudSdl->spellBarSprite = NULL;
	}

	if (hudSdl->mpText != NULL){
		SDL_DestroyTexture(hudSdl->mpText);
		hudSdl->mpText = NULL;
	}

	if (hudSdl->apText != NULL){
		SDL_DestroyTexture(hudSdl->apText);
		hudSdl->apText = NULL;
	}
	
	if (hudSdl->lifeText != NULL){
		SDL_DestroyTexture(hudSdl->lifeText);
		hudSdl->lifeText = NULL;
	}
	if (hudSdl->lifeMonsterText != NULL){
		SDL_DestroyTexture(hudSdl->lifeMonsterText);
		hudSdl->lifeMonsterText = NULL;
	}

	TTF_CloseFont(hudSdl->font);
	hudSdl->font=NULL;
	free(hudSdl->mp);
	free(hudSdl->ap);
	free(hudSdl->life);
	hudSdl->mp=NULL;
	hudSdl->ap=NULL;
	hudSdl->life=NULL;
	
	for(i=0; i<10; i++){
		
		free(hudSdl->lifeMonster[i]);
		free(hudSdl->posMonsters[i]);
		hudSdl->lifeMonster[i]=NULL;
		hudSdl->posMonsters[i]=NULL;
	}

	free(hudSdl->lifeMonster);
	free(hudSdl->posMonsters);
	hudSdl->lifeMonster=NULL;
	hudSdl->posMonsters=NULL;

}

void hudSdlInit(HudSdl *hudSdl, SDL_Renderer * renderer){
 	int i;

 	hudSdl->spellBarSprite=NULL;
	initHudSprite(hudSdl, renderer);
	hudSdl->life=0;
	hudSdl->font=NULL;
	hudSdl->font=TTF_OpenFont("data/ttf/rpg.ttf",100);
	if (hudSdl->font == NULL){

		printf("error opening font\n" );
	}

	hudSdl->life=NULL;
	hudSdl->mp=NULL;
	hudSdl->ap=NULL;
	hudSdl->lifeMonster=NULL;
	hudSdl->posMonsters=NULL;
	hudSdl->mpText=NULL;
	hudSdl->apText=NULL;
	hudSdl->lifeText=NULL;
	hudSdl->lifeMonsterText=NULL;

	hudSdl->life=malloc(3*sizeof(char));
	hudSdl->mp=malloc(3*sizeof(char));
	hudSdl->ap=malloc(3*sizeof(char));
	hudSdl->lifeMonster=malloc(10*sizeof(char*));
	hudSdl->posMonsters=malloc(10*sizeof(Position*));

	for(i=0; i<10; i++){
		hudSdl->lifeMonster[i]=malloc(3*sizeof(char));
		hudSdl->posMonsters[i]=malloc(sizeof(Position));
	}

	hudSdl->nbMstr =0;

}

HudSdl* hudSdlCreate(SDL_Renderer * renderer){
	HudSdl* hudSdl;
	hudSdl = malloc(sizeof(HudSdl));

	hudSdlInit(hudSdl, renderer);
	return hudSdl;
}

void hudSdlDestroy(HudSdl ** hudSdl){
	hudSdlFree(*hudSdl);
	free(*hudSdl);
	*hudSdl = NULL;
}


void convertIntToChar(char* CharNumber , int number){

		sprintf(CharNumber, "%d", number);
}

void drawHud(HudSdl* hudSdl, SDL_Renderer* renderer){
	int i;
	SDL_Color black = {0,0,0};
	SDL_Color red = {200,0,0};

	SDL_Rect destStats;
	SDL_Rect srcStats;

	SDL_Rect mpRect, apRect, lifeRect,srcSpellBar,destSpellBar, destLifeMonster;
	
	SDL_Surface* lifeMonsterSurface;
	SDL_Surface* mpSurface;
	SDL_Surface* apSurface;
	SDL_Surface* lifeSurface;

	mpSurface = TTF_RenderText_Blended(hudSdl->font, hudSdl->mp, black);
	apSurface = TTF_RenderText_Blended(hudSdl->font, hudSdl->ap, black);
	lifeSurface = TTF_RenderText_Blended(hudSdl->font, hudSdl->life, black);

	hudSdl->mpText = SDL_CreateTextureFromSurface(renderer, mpSurface);
	hudSdl->apText = SDL_CreateTextureFromSurface(renderer, apSurface);
	hudSdl->lifeText = SDL_CreateTextureFromSurface(renderer, lifeSurface);

	SDL_FreeSurface(mpSurface);
	SDL_FreeSurface(apSurface);
	SDL_FreeSurface(lifeSurface);

	mpRect.x =360;
	mpRect.y =37;
	mpRect.w =30;
	mpRect.h =30;

	apRect.x =235;
	apRect.y =37;
	apRect.w =30;
	apRect.h =30;

	lifeRect.x =120;
	lifeRect.y =37;
	lifeRect.w =30;
	lifeRect.h =30;

	destStats.x = 0;
	destStats.y = 0;
	destStats.w = 428;
	destStats.h = 117;
	 
	srcStats.x = 0;
	srcStats.y = 0;
	srcStats.w = 428;
	srcStats.h = 117;

	srcSpellBar.x=0;
	srcSpellBar.y=0;
	srcSpellBar.h=64;
	srcSpellBar.w=1344;

	destSpellBar.x=0;
	destSpellBar.y=636;
	destSpellBar.h=64;
	destSpellBar.w=1344;

	destLifeMonster.h=30;
	destLifeMonster.w=30;
	

	for (i=0; i<hudSdl->nbMstr; i++){ // we make and a copy into the rendere the texture which correspond to the life monsters
		lifeMonsterSurface = TTF_RenderText_Blended(hudSdl->font, hudSdl->lifeMonster[i],red);
		hudSdl->lifeMonsterText = SDL_CreateTextureFromSurface(renderer, lifeMonsterSurface);
		SDL_FreeSurface(lifeMonsterSurface);
		destLifeMonster.x=(getPosX(hudSdl->posMonsters[i]))+15;
		destLifeMonster.y=(getPosY(hudSdl->posMonsters[i]))-32;
		SDL_RenderCopy(renderer, hudSdl->lifeMonsterText, NULL, &destLifeMonster);
		SDL_DestroyTexture(hudSdl->lifeMonsterText);
		hudSdl->lifeMonsterText=NULL;


	}
	 	
	if(SDL_RenderCopyEx(renderer, hudSdl->hudSprite, &srcStats, &destStats, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererHudStatCopy\n");
	}

	if(SDL_RenderCopyEx(renderer, hudSdl->spellBarSprite, &srcSpellBar, &destSpellBar, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererHudSellCopy\n");
	}
	SDL_RenderCopy(renderer, hudSdl->mpText, NULL, &mpRect);
 	SDL_RenderCopy(renderer, hudSdl->apText, NULL, &apRect);
 	SDL_RenderCopy(renderer, hudSdl->lifeText, NULL, &lifeRect);
}

void hudSdlTest(){
	int i;
	HudSdl *hudSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
    
    hudSdl=NULL;
	hudSdl = malloc(sizeof(HudSdl));
	
	
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	printf("==== Tests of HudSdl ====\n");
	
	printf("Initializing using hudSdlInit... ");
	hudSdlInit(hudSdl, renderer);
	assert(hudSdl->font!=NULL);

	assert(hudSdl->life!=NULL);
	assert(hudSdl->mp!=NULL);
	assert(hudSdl->ap!=NULL);
	assert(hudSdl->lifeMonster!=NULL);
	assert(hudSdl->posMonsters!=NULL);
	assert(hudSdl->spellBarSprite!=NULL);
	assert(hudSdl->mpText==NULL);
	assert(hudSdl->apText==NULL);
	assert(hudSdl->lifeText==NULL);
	assert(hudSdl->lifeMonsterText==NULL);

	for(i=0; i<10; i++){
		assert(hudSdl->lifeMonster[i]!=NULL);
		assert(hudSdl->posMonsters[i]!=NULL);
	}
	printf("Ok.\n");

	
	printf("Test of initHudSprites...");
	initHudSprite(hudSdl,renderer);
	assert(hudSdl->hudSprite != NULL);
	assert(hudSdl->spellBarSprite != NULL);
	printf("Ok.\n");

	
	printf("Test of hudSdlFree...");
	hudSdlFree(hudSdl);
	assert(hudSdl->hudSprite == NULL);
	assert(hudSdl->spellBarSprite==NULL);
	assert(hudSdl->font==NULL);
	
	assert(hudSdl->lifeMonster==NULL);
	assert(hudSdl->posMonsters==NULL);
	assert(hudSdl->spellBarSprite==NULL);
	assert(hudSdl->mpText==NULL);
	assert(hudSdl->apText==NULL);
	assert(hudSdl->lifeText==NULL);
	assert(hudSdl->lifeMonsterText==NULL);

	printf("Ok.\n");

	free(hudSdl);
	hudSdl=NULL;

	printf("Test of hudSdlCreate...");
	hudSdl=hudSdlCreate(renderer);
	assert(hudSdl != NULL);
	printf("Ok.\n");

	printf("Test of hudSdlDestroy...");
	hudSdlDestroy(&hudSdl);
	assert(hudSdl == NULL);
	printf("Ok.\n");
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();

    TTF_Quit();
    
    SDL_Quit();

	printf("====The tests went well ====\n\n");



}