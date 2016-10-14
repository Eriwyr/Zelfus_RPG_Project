#include "npcSdl.h"

void initNpcSprites(NpcSdl * npcSdl, SDL_Renderer * renderer){
	npcSdl->npcSpriteSheet = loadImage("data/Image/perso.png", renderer);
}

void npcSdlFree(NpcSdl * npcSdl){
	int i;
	if (npcSdl->npcSpriteSheet != NULL){
		SDL_DestroyTexture(npcSdl->npcSpriteSheet);
		npcSdl->npcSpriteSheet = NULL;
	}
	dialogSdlDestroy(&npcSdl->dialogSdl);
	for(i=0;i<npcSdl->nbObj;i++){
		if(npcSdl->objectSdl[i]!=NULL){
			objectSdlDestroy(&npcSdl->objectSdl[i]);
		}
	}
	free(npcSdl->objectSdl);
	free(npcSdl->currentPos);
	npcSdl->currentPos=NULL;
}

void npcSdlInit(NpcSdl *npcSdl, NPC * npc, SDL_Renderer *renderer){

	int i;

	npcSdl->npcSpriteSheet=NULL;
 	initNpcSprites(npcSdl, renderer);
 	ObjectSet* set;
 	npcSdl->currentPos=NULL;
 	npcSdl->dialogSdl=NULL;
 	npcSdl->id = getIdNpc(npc);
	npcSdl->direction = DOWN;
	npcSdl->dialogSdl = dialogSdlCreate(renderer);
	npcSdl->frameNumber = npcSdl->id*3;
	 
	
	npcSdl->frameTimer = TIME_BETWEEN_2_FRAMES_NPC;
	 
	
	
	npcSdl->frameMax = (npcSdl->id*3)+3;
	 
	npcSdl->widthSprite = NPC_WIDTH;
	npcSdl->heightSprite = NPC_HEIGTH;

	npcSdl->currentPos =malloc(sizeof(Position));
	setPosX(npcSdl->currentPos, getPosX(getPositionNpc(npc))*64);
	setPosY(npcSdl->currentPos, getPosY(getPositionNpc(npc))*64);

	set = getObjectsObjective(getObjectiveQ(getQuestNpc(npc)));
	npcSdl->nbObj = getNbObjSet(set);

	npcSdl->objectSdl = malloc(npcSdl->nbObj * sizeof(ObjectSdl*));
	for(i=0;i<npcSdl->nbObj;i++){
		npcSdl->objectSdl[i] = objectSdlCreate(getObjectIObjset(set, i), renderer);
	}
	npcSdl->size=npcSdl->nbObj;
	npcSdl->displayDialog = 0;
	npcSdl->isIdle = 1; 	
	npcSdl->isTalking = 0;
}

NpcSdl* npcSdlCreate(NPC * npc, SDL_Renderer * renderer){
	NpcSdl * npcSdl;
	npcSdl = malloc(sizeof(NpcSdl));
	npcSdlInit(npcSdl, npc, renderer);

	return npcSdl;
}

Position* getCurrentPosNpcSdl(const NpcSdl* npcSdl){
	return npcSdl->currentPos;
}

void npcSdlDestroy(NpcSdl ** npcSdl){
	npcSdlFree(*npcSdl);
	free(*npcSdl);
	*npcSdl = NULL;
}

DialogSdl* getDialogNpcSdl(const NpcSdl* npcSdl){
	return npcSdl->dialogSdl;
}

void drawNpc(NpcSdl *npcSdl, SDL_Renderer * renderer){

	
	if (npcSdl->frameTimer <= 0){
	
		npcSdl->frameTimer = TIME_BETWEEN_2_FRAMES_NPC;
	 
		
		if(npcSdl->isIdle == 0){
			npcSdl->frameNumber++;
		}
		 
		
		if (npcSdl->frameNumber >= npcSdl->frameMax)
			npcSdl->frameNumber = npcSdl->id*3;
	 
	} else 
		npcSdl->frameTimer--;
	 

	SDL_Rect dest;
	

	dest.x = getPosX(npcSdl->currentPos);
	dest.y = getPosY(npcSdl->currentPos);
	dest.w = 48;
	dest.h = 48;
	 
	
	SDL_Rect src;
	 
	
	
	src.x = npcSdl->frameNumber * npcSdl->widthSprite; //à changer avec cste
	src.w = npcSdl->widthSprite;
	src.h = npcSdl->heightSprite;
	 
	
	
	
	src.y = (npcSdl->direction * npcSdl->heightSprite);
	 
	
	
	if(SDL_RenderCopyEx(renderer, npcSdl->npcSpriteSheet, &src, &dest, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererNpcCopy\n");
	} 
}

void setIsTalkingNpcSdl(NpcSdl* npcSdl, int value){
	npcSdl->isTalking = value;
}

void setIsIdleNpcSdl(NpcSdl* npcSdl, int value){
	npcSdl->isIdle = value;
}

void setDisplayDialogNpcSdl(NpcSdl* npcSdl, int value){
	npcSdl->displayDialog = value;
}

ObjectSdl* getObjectSdlINpcSdl(NpcSdl* npcSdl, int i){
	assert(i >= 0);
	assert(i < npcSdl->nbObj);
	return npcSdl->objectSdl[i];
}

int getNbObjNpcSdl(const NpcSdl* npcSdl){
	return npcSdl->nbObj;
}

void removeObjectSdlNpcSdl(NpcSdl * npcSdl, int ind){
	int j;
        /*Making sure that the ind is <= to the number of monsters and > 0 */
        assert(ind <= npcSdl->nbObj);
        assert(ind > 0);
        for(j = ind-1; j<npcSdl->nbObj-1;j++){ /*We start the loop from the ind ( minus one to keep first element at ind 1 )*/
        		objectSdlDestroy(&npcSdl->objectSdl[j]);
            npcSdl->objectSdl[j] = npcSdl->objectSdl[j+1]; /*Each elements is then shifted from 1*/
        }
        npcSdl->nbObj--; // There is now one element less

        // We redifine the size once there is enough free slots
        ObjectSdl ** tmp = npcSdl->objectSdl; //We save the current monsters
        npcSdl->size--;
        npcSdl->objectSdl = malloc(npcSdl->size*sizeof(ObjectSdl*)); //We reallocate memory
        for(j=0;j<npcSdl->nbObj;j++){
            npcSdl->objectSdl[j] = tmp[j]; //Restoration of the saved monsters
        }
        free(tmp);
}

void npcSdlTest(){
	
	NpcSdl *npcSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	NPC* npc;

	npc=npcCreate("npc","hello",1);
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	
	if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }

	npcSdl =malloc(sizeof(NpcSdl));

	printf("==== Tests of NpcSdl ====\n");
	
	printf("Initializing using npcSdlInit... ");
	npcSdlInit(npcSdl,npc,renderer);
	assert(npcSdl->currentPos != NULL);
	assert(npcSdl->dialogSdl != NULL);
	assert(npcSdl->npcSpriteSheet !=NULL);
	printf("Ok.\n");

	
	printf("Test of initNpcSprites...");
	initNpcSprites(npcSdl,renderer);
	assert(npcSdl->npcSpriteSheet != NULL);
	printf("Ok.\n");

	printf("Test of npcSdlFree...");
	npcSdlFree(npcSdl);
	assert(npcSdl->npcSpriteSheet == NULL);

	assert(npcSdl->currentPos==NULL);
	assert(npcSdl->dialogSdl==NULL);

	printf("Ok.\n");
	free(npcSdl);
	npcSdl =NULL;

	printf("Test of npcSdlCreate...");
	npcSdl=npcSdlCreate(npc,renderer);
	assert(npcSdl != NULL);
	printf("Ok.\n");

	printf("Test of npcSdlDestroy...");
	npcSdlDestroy(&npcSdl);
	assert(npcSdl == NULL);
	printf("Ok.\n");
	npcDestroy(&npc);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
	TTF_Quit();
	
	printf("====The tests went well ====\n\n");

}


int* getDirectionNpcSdl(NpcSdl* npcSdl){
	return &npcSdl->direction;
}