#include "spellSdl.h"

void initSpellSprites(SpellSdl * spellSdl, SDL_Renderer * renderer, char* fileName){
	spellSdl->attack1Sprite = loadImage(fileName, renderer);
}


void spellSdlFree(SpellSdl * spellSdl){
	if (spellSdl->attack1Sprite != NULL){
		SDL_DestroyTexture(spellSdl->attack1Sprite);
		spellSdl->attack1Sprite = NULL;
	}

	free(spellSdl->currentPos);
	spellSdl->currentPos=NULL;
}


void spellSdlInit(SpellSdl *spellSdl, Spell * spell, SDL_Renderer *renderer, char* fileName){

	spellSdl->attack1Sprite=NULL;
	initSpellSprites(spellSdl, renderer, fileName);

	spellSdl->currentPos=NULL;
	spellSdl->id = getIdSpell(spell);
	spellSdl->direction = RIGHT;
	spellSdl->frameNumber = 0;

	spellSdl->display = 0;
	spellSdl->frameTimer = TIME_BETWEEN_2_FRAMES_SPELL;
	
	spellSdl->frameMax = 3;
	
	spellSdl->widthSprite = SPELL_WIDTH;
	spellSdl->heightSprite = SPELL_HEIGTH;
	spellSdl->currentPos = malloc(sizeof(Position));
}


SpellSdl* spellSdlCreate(Spell *spell, SDL_Renderer * renderer, char* fileName){
	SpellSdl * spellSdl;
	spellSdl = malloc(sizeof(SpellSdl));
	spellSdlInit(spellSdl, spell, renderer, fileName);

	return spellSdl;
}

void spellSdlDestroy(SpellSdl ** spellSdl){
	spellSdlFree(*spellSdl);
	free(*spellSdl);
	*spellSdl = NULL;
}

void drawSpell(SpellSdl *spellSdl, SDL_Renderer * renderer){

	
	if (spellSdl->frameTimer <= 0){
		
		spellSdl->frameTimer = TIME_BETWEEN_2_FRAMES_SPELL;
		spellSdl->frameNumber++;
		
		if (spellSdl->frameNumber >= spellSdl->frameMax)
			spellSdl->frameNumber = 0;
		
	} else 
	spellSdl->frameTimer--;
	
	
	

	SDL_Rect dest;
	

	dest.x = getPosX(spellSdl->currentPos);
	dest.y = getPosY(spellSdl->currentPos);
	dest.w = 64;
	dest.h = 64;
	
	
	SDL_Rect src;
	
	
	
	src.x = spellSdl->frameNumber * spellSdl->widthSprite; //à changer avec cste
	src.w = spellSdl->widthSprite;
	src.h = spellSdl->heightSprite;
	
	
	
	
	src.y = 0;


	if(spellSdl->direction == UP){
		
		if(SDL_RenderCopyEx(renderer, spellSdl->attack1Sprite, &src, &dest, -90, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererCharacCopy\n");

		}

	} 
	
	if(spellSdl->direction == DOWN){
		
		if(SDL_RenderCopyEx(renderer, spellSdl->attack1Sprite, &src, &dest, 90, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererCharacCopy\n");

		}

	}

	if(spellSdl->direction == LEFT){
		
		if(SDL_RenderCopyEx(renderer, spellSdl->attack1Sprite, &src, &dest, 0, 0, SDL_FLIP_HORIZONTAL) < 0){
			printf("Error rendererCharacCopy\n");

		}

	}
	
	if(spellSdl->direction == RIGHT){
		
		if(SDL_RenderCopyEx(renderer, spellSdl->attack1Sprite, &src, &dest, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererCharacCopy\n");

		}

	} 
}

Position* getCurrentPosSpellSdl(SpellSdl * spellSdl){
	return spellSdl->currentPos;
}

void setCurrentPosSpellSdl(SpellSdl * spellSdl, int x, int y){
	setPosX(spellSdl->currentPos, x);
	setPosY(spellSdl->currentPos, y);
}

void setDisplaySpellSdl(SpellSdl* spellSdl, int value){
	spellSdl->display=value;
}

int* getDirectionSpellSdl(SpellSdl* spellSdl){
	return &spellSdl->direction;
}

int getDisplaySpellSdl(const SpellSdl* spellSdl){
	return spellSdl->display;
}

void spellSdlTest(){
	
	SpellSdl *spellSdl;
	Spell* spell;
	SDL_Window* screen;
	SDL_Renderer *renderer;

	spell = spellCreate(1,"test",20,1);

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	screen = SDL_CreateWindow("test",	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	spellSdl =malloc(sizeof(SpellSdl));
	
	printf("==== Tests of SpellSdl ====\n");
	
	printf("Initializing using spellSdlInit... ");
	spellSdlInit(spellSdl,spell,renderer, "data/Image/attack3.png");
	assert(spellSdl->attack1Sprite != NULL);
	assert(spellSdl->currentPos != NULL);
	printf("Ok.\n");

	
	printf("Test of initSpellSprites...");
	initSpellSprites(spellSdl,renderer, "data/Image/attack3.png");
	assert(spellSdl->attack1Sprite != NULL);

	printf("Ok.\n");

	printf("Test of spellSdlFree...");
	spellSdlFree(spellSdl);
	assert(spellSdl->attack1Sprite == NULL);
	assert(spellSdl->currentPos==NULL);
	printf("Ok.\n");

	free(spellSdl);
	spellSdl =NULL;

	printf("Test of spellSdlCreate...");
	spellSdl=spellSdlCreate(spell,renderer,"data/Image/attack3.png");
	assert(spellSdl != NULL);
	printf("Ok.\n");

	printf("Test of spellSdlDestroy...");
	spellSdlDestroy(&spellSdl);
	assert(spellSdl == NULL);
	printf("Ok.\n");

	spellDestroy(&spell);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	IMG_Quit();   
    SDL_Quit();
	
	printf("====The tests went well ====\n\n");
}
