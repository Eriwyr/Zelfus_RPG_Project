#include "questDiarySdl.h"

void initQuestDiarySprite(QuestDiarySdl * questDiarySdl, SDL_Renderer * renderer){
	questDiarySdl->questDiarySprite= loadImage("data/Image/Diary.png", renderer);
}

void questDiarySdlFree(QuestDiarySdl * questDiarySdl){
	
	if (questDiarySdl->questDiarySprite != NULL){
		SDL_DestroyTexture(questDiarySdl->questDiarySprite);
		questDiarySdl->questDiarySprite = NULL;
	}

	if (questDiarySdl->questText != NULL){
		SDL_DestroyTexture(questDiarySdl->questText);
		questDiarySdl->questText = NULL;
	}

	if (questDiarySdl->xpText != NULL){
		SDL_DestroyTexture(questDiarySdl->xpText);
		questDiarySdl->xpText = NULL;
	}

	if (questDiarySdl->moneyText != NULL){
		SDL_DestroyTexture(questDiarySdl->moneyText);
		questDiarySdl->moneyText = NULL;
	}

	if (questDiarySdl->nbMstrText != NULL){
		SDL_DestroyTexture(questDiarySdl->nbMstrText);
		questDiarySdl->nbMstrText = NULL;
	}

	if (questDiarySdl->nbObjectText != NULL){
		SDL_DestroyTexture(questDiarySdl->nbObjectText);
		questDiarySdl->nbObjectText = NULL;
	}
		
	TTF_CloseFont(questDiarySdl->font);
	if(questDiarySdl->quest !=NULL){
		free(questDiarySdl->quest);
	}

	free(questDiarySdl->xp);
	free(questDiarySdl->money);
	free(questDiarySdl->nbMstr);
	free(questDiarySdl->nbObject);
	questDiarySdl->font=NULL;
	questDiarySdl->quest = NULL;
	questDiarySdl->xp = NULL;
	questDiarySdl->money = NULL;
	questDiarySdl->nbMstr = NULL;
	questDiarySdl->nbObject = NULL;


}

void questDiarySdlInit(QuestDiarySdl *questDiarySdl, SDL_Renderer * renderer){

	questDiarySdl->font = NULL;
	questDiarySdl->questDiarySprite=NULL;
	initQuestDiarySprite(questDiarySdl, renderer);
	questDiarySdl->font=TTF_OpenFont("data/ttf/rpg.ttf",70);
	
	if (questDiarySdl->font == NULL){

		printf("error opening font\n" );
	}
	questDiarySdl->quest = NULL;
	questDiarySdl->xp = NULL;
	questDiarySdl->money = NULL;
	questDiarySdl->nbMstr = NULL;
	questDiarySdl->nbObject = NULL;

	questDiarySdl->questText=NULL;
	questDiarySdl->xpText=NULL;
	questDiarySdl->moneyText=NULL;
	questDiarySdl->nbMstrText=NULL;
	questDiarySdl->nbObjectText=NULL;

	//questDiarySdl->quest = malloc(100*sizeof(char));
	questDiarySdl->xp = malloc (4*sizeof(char));
	questDiarySdl->money = malloc(5*sizeof(char));
	questDiarySdl->nbMstr = malloc(3*sizeof(char));
	questDiarySdl->nbObject = malloc(3*sizeof(char));


}

QuestDiarySdl* questDiarySdlCreate(SDL_Renderer * renderer){
	QuestDiarySdl* questDiarySdl;
	questDiarySdl = malloc(sizeof(QuestDiarySdl));

	questDiarySdlInit(questDiarySdl, renderer);
	return questDiarySdl;
}


void questDiarySdlDestroy(QuestDiarySdl ** questDiarySdl){
	questDiarySdlFree(*questDiarySdl);
	free(*questDiarySdl);
	*questDiarySdl = NULL;
}

void drawQuestDiary(QuestDiarySdl* questDiarySdl,QuestDiary* questDiary, SDL_Renderer* renderer){
	int i;
	SDL_Color black = {0,0,0};
	SDL_Rect diaryDest, diarySrc;
	SDL_Rect questDest, xpDest, moneyDest, nbMstrDest, nbObjectDest; 

	SDL_Surface* questSurface, *xpSurface, *moneySurface, *nbMstrSurface, *nbObjectSurface;

	

	diarySrc.x=0;
	diarySrc.y=0;
	diarySrc.h=771;
	diarySrc.w=1352;

	diaryDest.x=0;
	diaryDest.y=0;
	diaryDest.h=700;
	diaryDest.w=1344;

	if(SDL_RenderCopyEx(renderer, questDiarySdl->questDiarySprite, &diarySrc, &diaryDest, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererHudStatCopy\n");
	}

	if(getNbQuestDiary(questDiary)==0){
		questDest.x=(WIDTH_DIARY/2)-345;
		questDest.y=(HEIGHT_DIARY/2)-35;
		questDest.h=70;
		questDest.w=690;

		questSurface = TTF_RenderText_Blended(questDiarySdl->font, "You don't have any Quests", black);
		questDiarySdl->questText = SDL_CreateTextureFromSurface(renderer, questSurface);
		SDL_RenderCopy(renderer, questDiarySdl->questText, NULL, &questDest);

		SDL_FreeSurface(questSurface);
	}	

	for (i=0;i<getNbQuestDiary(questDiary); i++){
		
		questDiarySdl->quest = strdup(getNameQ(getQuestIDiary(questDiary, i)));
		convertIntToChar(questDiarySdl->xp, getXpReward(getRewardQ(getQuestIDiary(questDiary, i))));
		convertIntToChar(questDiarySdl->money, getMoneyReward(getRewardQ(getQuestIDiary(questDiary, i))));
		convertIntToChar(questDiarySdl->nbMstr, getNbMstrObjective(getObjectiveQ(getQuestIDiary(questDiary, i)))); //we assign nbMstr which must kills in the quest
		convertIntToChar(questDiarySdl->nbObject, getNbObjSet(getObjectsObjective(getObjectiveQ(getQuestIDiary(questDiary, i))))); //we assign nbObj which must found in the quest


		questSurface = TTF_RenderText_Blended(questDiarySdl->font, questDiarySdl->quest, black);
		xpSurface = TTF_RenderText_Blended(questDiarySdl->font, questDiarySdl->xp, black);
		moneySurface = TTF_RenderText_Blended(questDiarySdl->font, questDiarySdl->money, black);
		nbMstrSurface = TTF_RenderText_Blended(questDiarySdl->font, questDiarySdl->nbMstr, black);
		nbObjectSurface = TTF_RenderText_Blended(questDiarySdl->font, questDiarySdl->nbObject, black);

		questDiarySdl->questText = SDL_CreateTextureFromSurface(renderer, questSurface);
		questDiarySdl->xpText = SDL_CreateTextureFromSurface(renderer, xpSurface);
		questDiarySdl->moneyText = SDL_CreateTextureFromSurface(renderer, moneySurface);
		questDiarySdl->nbMstrText = SDL_CreateTextureFromSurface(renderer, nbMstrSurface);
		questDiarySdl->nbObjectText = SDL_CreateTextureFromSurface(renderer, nbObjectSurface);

		questDest.x=80;
		questDest.y=140;
		questDest.h=64;
		questDest.w=400;
		
		xpDest.x=795;
		xpDest.y=165;
		xpDest.h=32;
		xpDest.w=50;
		
		moneyDest.x=595;
		moneyDest.y=165;
		moneyDest.h=32;
		moneyDest.w=50;
		
		nbMstrDest.x=995;
		nbMstrDest.y=165;
		nbMstrDest.h=32;
		nbMstrDest.w=25;
		
		nbObjectDest.x=1195;
		nbObjectDest.y=165;
		nbObjectDest.h=32;
		nbObjectDest.w=25;
		



		SDL_RenderCopy(renderer, questDiarySdl->questText, NULL, &questDest);

		SDL_RenderCopy(renderer, questDiarySdl->xpText, NULL, &xpDest);

		SDL_RenderCopy(renderer, questDiarySdl->moneyText, NULL, &moneyDest);

		SDL_RenderCopy(renderer, questDiarySdl->nbMstrText, NULL, &nbMstrDest);

		SDL_RenderCopy(renderer, questDiarySdl->nbObjectText, NULL, &nbObjectDest);

		free(questDiarySdl->quest);
		SDL_FreeSurface(questSurface);
		SDL_FreeSurface(xpSurface);
		SDL_FreeSurface(moneySurface);
		SDL_FreeSurface(nbMstrSurface);
		SDL_FreeSurface(nbObjectSurface);


		questDiarySdl->quest=NULL;

	}



}

void questDiarySdlTest(){
	
	QuestDiarySdl *questDiarySdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	
	if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }

	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	questDiarySdl =malloc(sizeof(QuestDiarySdl));
	
	printf("==== Tests of QuestDiarySdl ====\n");
	
	printf("Initializing using questDiarySdlInit... ");
	questDiarySdlInit(questDiarySdl,renderer);
	assert(questDiarySdl->font!=NULL);
	assert(questDiarySdl->questDiarySprite!=NULL);
	assert(questDiarySdl->xp != NULL);
	assert(questDiarySdl->money != NULL);
	assert(questDiarySdl->nbMstr != NULL);
	assert(questDiarySdl->nbObject != NULL);

	assert(questDiarySdl->questText==NULL);
	assert(questDiarySdl->xpText==NULL);
	assert(questDiarySdl->moneyText==NULL);
	assert(questDiarySdl->nbMstrText==NULL);
	assert(questDiarySdl->nbObjectText==NULL);

	printf("Ok.\n");

	
	printf("Test of initPlayerSprites...");
	initQuestDiarySprite(questDiarySdl,renderer);
	assert(questDiarySdl->questDiarySprite != NULL);
	printf("Ok.\n");

	printf("Test of questDiarySdlFree...");
	questDiarySdlFree(questDiarySdl);
	assert(questDiarySdl->font==NULL);
	assert(questDiarySdl->questDiarySprite==NULL);
	assert(questDiarySdl->quest==NULL);
	assert(questDiarySdl->xp==NULL);
	assert(questDiarySdl->money==NULL);
	assert(questDiarySdl->nbMstr==NULL);
	assert(questDiarySdl->nbObject==NULL);

	assert(questDiarySdl->questText==NULL);
	assert(questDiarySdl->xpText==NULL);
	assert(questDiarySdl->moneyText==NULL);
	assert(questDiarySdl->nbMstrText==NULL);
	assert(questDiarySdl->nbObjectText==NULL);

	printf("Ok.\n");

	free(questDiarySdl);
	questDiarySdl=NULL;

	printf("Test of questDiarySdlCreate...");
	questDiarySdl=questDiarySdlCreate(renderer);
	assert(questDiarySdl != NULL);
	printf("Ok.\n");

	printf("Test of questDiarySdlDestroy...");
	questDiarySdlDestroy(&questDiarySdl);
	assert(questDiarySdl == NULL);
	printf("Ok.\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
    TTF_Quit();
	
	printf("====The tests went well ====\n\n");

}
