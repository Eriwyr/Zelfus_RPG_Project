#include "objectSdl.h"

void initObjectSprite(ObjectSdl * objectSdl, SDL_Renderer * renderer){
	objectSdl->objectSprite= loadImage("data/Image/object.png", renderer);
}

void objectSdlInit(ObjectSdl *objectSdl, QuestObject* object, SDL_Renderer * renderer){

	objectSdl->objectSprite=NULL;
	initObjectSprite(objectSdl, renderer);

	objectSdl->id=1;
	objectSdl->heightSprite=32;
	objectSdl->widthSprite=32;
	objectSdl->display = 0;	

	objectSdl->currentPos = malloc(sizeof(Position));
	setPosX(objectSdl->currentPos, getPosX(getPositionObject(object))*64);
	setPosY(objectSdl->currentPos, getPosY(getPositionObject(object))*64);
}

ObjectSdl* objectSdlCreate(QuestObject* object, SDL_Renderer * renderer){
	ObjectSdl* objectSdl;
	objectSdl = malloc(sizeof(ObjectSdl));

	objectSdlInit(objectSdl, object, renderer);
	return objectSdl;
}

int getDisplayObjectSdl(const ObjectSdl * objectSdl){
	return objectSdl->display;
}

void setDisplayObjectSdl(ObjectSdl * objectSdl, int value){
	objectSdl->display = value;
}


void objectSdlFree(ObjectSdl * objectSdl){
	if (objectSdl->objectSprite != NULL){
		SDL_DestroyTexture(objectSdl->objectSprite);
		objectSdl->objectSprite = NULL;
	}

	free(objectSdl->currentPos);
}

void objectSdlDestroy(ObjectSdl ** objectSdl){
	objectSdlFree(*objectSdl);
	free(*objectSdl);
	*objectSdl = NULL;
}

void drawObject(ObjectSdl* objectSdl, SDL_Renderer* renderer){

	SDL_Rect objectDest, objectSrc;

	objectDest.x=getPosX(objectSdl->currentPos)+(64 - WIDTH_OBJECT)/2;
	objectDest.y=getPosY(objectSdl->currentPos)+(64 - HEIGHT_OBJECT)/2;
	objectDest.h=HEIGHT_OBJECT;
	objectDest.w=WIDTH_OBJECT;

	objectSrc.x=0;
	objectSrc.y=0;
	objectSrc.h=HEIGHT_OBJECT;
	objectSrc.w=WIDTH_OBJECT;


	if(SDL_RenderCopyEx(renderer, objectSdl->objectSprite, &objectSrc, &objectDest, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererObjectCopy\n");

	}
}

void objectSdlTest(){
	
	ObjectSdl *objectSdl;
	SDL_Window* screen;
	SDL_Renderer *renderer;
	QuestObject * object;

	object = questObjectCreate(0, "Object", "Magic", 2, 5, 2);
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	objectSdl = malloc(sizeof(ObjectSdl));
	
	printf("==== Tests of ObjectSdl ====\n");
	
	printf("Initializing using objectSdlInit... ");
	objectSdlInit(objectSdl, object,renderer);
	assert(objectSdl->objectSprite != NULL);
	printf("Ok.\n");

	
	printf("Test of initObjectSprites...");
	initObjectSprite(objectSdl,renderer);
	assert(objectSdl->objectSprite != NULL);

	printf("Ok.\n");

	printf("Test of objectSdlFree...");
	objectSdlFree(objectSdl);
	assert(objectSdl->objectSprite == NULL);
	printf("Ok.\n");
	free(objectSdl);
	objectSdl =NULL;

	printf("Test of objectSdlCreate...");
	objectSdl=objectSdlCreate(object, renderer);
	assert(objectSdl != NULL);
	printf("Ok.\n");

	printf("Test of objectSdlDestroy...");
	objectSdlDestroy(&objectSdl);
	assert(objectSdl == NULL);
	printf("Ok.\n");


	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
	
	printf("====The tests went well ====\n\n");

}
	