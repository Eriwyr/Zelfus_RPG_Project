#ifndef SPELLSDL_H
#define SPELLSDL_H


#define TIME_BETWEEN_2_FRAMES_SPELL 5
 
#define SPELL_WIDTH 80
#define SPELL_HEIGTH 80
 
#define SPELL_SPEED 1000

#include "Spell.h"
#include "Position.h"
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * @struct SpellSdl
 * @brief contain everything to dislay spells
 */
typedef struct {
	int heightSprite, widthSprite;
	int frameNumber, frameTimer, frameMax;
	int direction;
	int id;
	int display;
	SDL_Texture* attack1Sprite;
	Position *currentPos;

}SpellSdl;


SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

void initSpellSprites(SpellSdl * spellSdl, SDL_Renderer * renderer, char* fileName);

void spellSdlInit(SpellSdl *spellSdl, Spell * spell, SDL_Renderer *renderer, char* fileName);

void spellSdlFree(SpellSdl * spellSdl);

SpellSdl* spellSdlCreate(Spell *spell, SDL_Renderer * renderer, char* fileName);

void spellSdlDestroy(SpellSdl ** spellSdl);

void drawSpell(SpellSdl *spellSdl, SDL_Renderer * renderer);

Position* getCurrentPosSpellSdl(SpellSdl * spellSdl);

void setCurrentPosSpellSdl(SpellSdl * spellSdl, int x, int y);

void setDisplaySpellSdl(SpellSdl* spellSdl, int value);

int getDisplaySpellSdl(const SpellSdl* spellSdl);

int* getDirectionSpellSdl(SpellSdl* spellSdl);

void spellSdlTest();

#endif