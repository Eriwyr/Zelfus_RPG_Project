#include "rewardSdl.h"

void initRewardSprite(RewardSdl * rewardSdl, SDL_Renderer * renderer){
	rewardSdl->rewardWinSprite= loadImage("data/Image/win.png", renderer);
	rewardSdl->rewardLooseSprite= loadImage("data/Image/loose.png", renderer);
}

void rewardSdlFree(RewardSdl * rewardSdl){
	if (rewardSdl->rewardWinSprite != NULL){
		SDL_DestroyTexture(rewardSdl->rewardWinSprite);
		rewardSdl->rewardWinSprite = NULL;
	}

	if (rewardSdl->rewardLooseSprite != NULL){
		SDL_DestroyTexture(rewardSdl->rewardLooseSprite);
		rewardSdl->rewardLooseSprite = NULL;
	}

	TTF_CloseFont(rewardSdl->font);

	free(rewardSdl->xp);
	free(rewardSdl->money);

	rewardSdl->font=NULL;
	rewardSdl->xp=NULL;
	rewardSdl->money=NULL;
}

void rewardSdlInit(RewardSdl *rewardSdl, SDL_Renderer * renderer){

	rewardSdl->rewardWinSprite=NULL;
	rewardSdl->rewardLooseSprite=NULL;

	initRewardSprite(rewardSdl, renderer);
	
	rewardSdl->font = NULL;

	rewardSdl->font=TTF_OpenFont("data/ttf/rpg.ttf",70);
	if (rewardSdl->font == NULL){

		printf("error opening font\n" );
	}

	rewardSdl->xp=NULL;
	rewardSdl->money=NULL;

	rewardSdl->xpText=NULL;
	rewardSdl->moneyText=NULL;

	rewardSdl->xp = malloc (4*sizeof(char));
	rewardSdl->money = malloc(5*sizeof(char));
}

RewardSdl* rewardSdlCreate(SDL_Renderer * renderer){
	RewardSdl* rewardSdl;
	rewardSdl = malloc(sizeof(RewardSdl));

	rewardSdlInit(rewardSdl, renderer);
	return rewardSdl;
}

void rewardSdlDestroy(RewardSdl ** rewardSdl){
	rewardSdlFree(*rewardSdl);
	free(*rewardSdl);
	*rewardSdl = NULL;
}


void drawReward(RewardSdl* rewardSdl,int issue, SDL_Renderer* renderer){

	//int i;

	//SDL_Color black = {0,0,0};
	SDL_Rect rewardDest, rewardSrc;
	//SDL_Rect xpDest, moneyDest; 

	//SDL_Surface* xpSurface, *moneySurface;

	

	rewardSrc.x=0;
	rewardSrc.y=0;
	rewardSrc.h=HEIGHT_REWARD;
	rewardSrc.w=WIDTH_REWARD;

	rewardDest.x=250;
	rewardDest.y=30;
	rewardDest.h=HEIGHT_REWARD;
	rewardDest.w=WIDTH_REWARD;

	if (issue == 1){
		if(SDL_RenderCopyEx(renderer, rewardSdl->rewardWinSprite, &rewardSrc, &rewardDest, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererRewardCopy\n");
		}
	}
	
	else{
		if(SDL_RenderCopyEx(renderer, rewardSdl->rewardLooseSprite, &rewardSrc, &rewardDest, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererRewardCopy\n");
		}
	
	}

		// //convertIntToChar(rewardSdl->xp, getXpReward(getRewardQ(getQuestIDiary(questDiary, i))));
		// //convertIntToChar(rewardSdl->money, getMoneyReward(getRewardQ(getQuestIDiary(questDiary, i))));

		// xpSurface = TTF_RenderText_Blended(rewardSdl->font, rewardSdl->xp, black);
		// moneySurface = TTF_RenderText_Blended(rewardSdl->font, rewardSdl->money, black);

		// rewardSdl->xpText = SDL_CreateTextureFromSurface(renderer, xpSurface);
		// rewardSdl->moneyText = SDL_CreateTextureFromSurface(renderer, moneySurface);

		// xpDest.x=520;
		// xpDest.y=30;
		// xpDest.h=32;
		// xpDest.w=50;
		
		// moneyDest.x=630+50;
		// moneyDest.y=30;
		// moneyDest.h=32;
		// moneyDest.w=50;
		
		// SDL_RenderCopy(renderer, rewardSdl->xpText, NULL, &xpDest);

		// SDL_RenderCopy(renderer, rewardSdl->moneyText, NULL, &moneyDest);

}

void rewardSdlTest(){
	
	RewardSdl *rewardSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
    
    rewardSdl=NULL;
	rewardSdl = malloc(sizeof(RewardSdl));
	
	
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	printf("==== Tests of RewardSdl ====\n");
	
	printf("Initializing using rewardSdlInit... ");
	rewardSdlInit(rewardSdl, renderer);
	assert(rewardSdl->font!=NULL);

	assert(rewardSdl->xp!=NULL);
	assert(rewardSdl->money!=NULL);
	assert(rewardSdl->moneyText==NULL);
	assert(rewardSdl->xpText==NULL);

	printf("Ok.\n");

	
	printf("Test of initRewardSprites...");
	initRewardSprite(rewardSdl,renderer);
	assert(rewardSdl->rewardWinSprite != NULL);
	assert(rewardSdl->rewardLooseSprite != NULL);
	printf("Ok.\n");

	
	printf("Test of rewardSdlFree...");
	rewardSdlFree(rewardSdl);
	assert(rewardSdl->rewardWinSprite == NULL);
	assert(rewardSdl->rewardLooseSprite==NULL);
	assert(rewardSdl->font==NULL);
	assert(rewardSdl->xp==NULL);
	assert(rewardSdl->money==NULL);
	printf("Ok.\n");
	
	free(rewardSdl);
	rewardSdl=NULL;

	printf("Test of rewardSdlCreate...");
	rewardSdl=rewardSdlCreate(renderer);
	assert(rewardSdl != NULL);
	printf("Ok.\n");

	printf("Test of rewardSdlDestroy...");
	rewardSdlDestroy(&rewardSdl);
	assert(rewardSdl == NULL);
	printf("Ok.\n");
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);

 	IMG_Quit();

 	TTF_Quit();
    
    SDL_Quit();

	printf("====The tests went well ====\n\n");



}