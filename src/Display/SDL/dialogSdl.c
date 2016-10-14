#include "dialogSdl.h"

void initDialogSprite(DialogSdl * dialogSdl, SDL_Renderer * renderer){
	dialogSdl->dialogSprite= loadImage("data/Image/Dialog.png", renderer);
}

void dialogSdlInit(DialogSdl *dialogSdl, SDL_Renderer * renderer){

	dialogSdl->dialogSprite = NULL;
	dialogSdl->dialogText = NULL;
	initDialogSprite(dialogSdl, renderer);
	dialogSdl->font=TTF_OpenFont("data/ttf/rpg.ttf",30);
	if (dialogSdl->font == NULL){

		printf("error opening font\n" );
		printf("%s \n ",TTF_GetError());
	}
}

void dialogSdlFree(DialogSdl * dialogSdl){
	if (dialogSdl->dialogSprite != NULL){
		SDL_DestroyTexture(dialogSdl->dialogSprite);
		dialogSdl->dialogSprite = NULL;
	}

	if (dialogSdl->dialogText != NULL){
		SDL_DestroyTexture(dialogSdl->dialogText);
		dialogSdl->dialogText = NULL;
	}	
	TTF_CloseFont(dialogSdl->font);
	dialogSdl->font=NULL;
}


DialogSdl* dialogSdlCreate(SDL_Renderer * renderer){
	DialogSdl* dialogSdl;
	dialogSdl = malloc(sizeof(DialogSdl));

	dialogSdlInit(dialogSdl, renderer);
	return dialogSdl;
}

void dialogSdlDestroy(DialogSdl ** dialogSdl){
	dialogSdlFree(*dialogSdl);
	free(*dialogSdl);
	*dialogSdl = NULL;
}

void drawDialog(DialogSdl* dialogSdl, char* dialog, Position* position,SDL_Renderer* renderer){

	SDL_Rect dialogDest, dialogSrc;
	SDL_Surface* dialogSurface;

	SDL_Color black={0,0,0};

	dialogDest.x=getPosX(position)+15;
	dialogDest.y=getPosY(position)-150;
	dialogDest.h=HEIGHT_DIALOG;
	dialogDest.w=WIDTH_DIALOG;

	dialogSrc.x=0;
	dialogSrc.y=0;
	dialogSrc.h=150;
	dialogSrc.w=500;

	dialogSurface = TTF_RenderText_Blended(dialogSdl->font, dialog, black);
	dialogSdl->dialogText =  SDL_CreateTextureFromSurface(renderer, dialogSurface);

	if(SDL_RenderCopyEx(renderer, dialogSdl->dialogSprite, &dialogSrc, &dialogDest, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererDialogCopy\n");
	}

	dialogDest.x += 10;
	dialogDest.y += 10;
	dialogDest.h=32;
	dialogDest.w=300;


	SDL_FreeSurface(dialogSurface);
	SDL_RenderCopy(renderer, dialogSdl->dialogText, NULL, &dialogDest);


}

void dialogSdlTest(){
	
	DialogSdl *dialogSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	
	if (TTF_Init() < 0) {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
    dialogSdl=NULL;
	dialogSdl = malloc(sizeof(DialogSdl));
	
	
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	printf("==== Tests of DialogSdl ====\n");
	
	printf("Initializing using dialogSdlInit... ");
	dialogSdlInit(dialogSdl, renderer);
	assert(dialogSdl->font!=NULL);
	assert(dialogSdl->dialogSprite != NULL);
	assert(dialogSdl->dialogText == NULL);
	assert(dialogSdl !=NULL);
	printf("Ok.\n");

	
	printf("Test of initDialogSprites...");
	initDialogSprite(dialogSdl,renderer);
	assert(dialogSdl->dialogSprite != NULL);
	printf("Ok.\n");

	printf("Test of dialogSdlFree...");
	dialogSdlFree(dialogSdl);
	assert(dialogSdl->dialogSprite == NULL);
	assert(dialogSdl->dialogText==NULL);
	assert(dialogSdl->font==NULL);

	printf("Ok.\n");

	free(dialogSdl);
	dialogSdl =NULL;

	printf("Test of dialogSdlCreate...");
	dialogSdl=dialogSdlCreate(renderer);
	assert(dialogSdl != NULL);
	printf("Ok.\n");

	printf("Test of dialogSdlDestroy...");
	dialogSdlDestroy(&dialogSdl);
	assert(dialogSdl == NULL);
	printf("Ok.\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();

    TTF_Quit();
    
    SDL_Quit();
    
	printf("====The tests went well ====\n\n");

}