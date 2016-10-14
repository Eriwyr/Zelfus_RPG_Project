#ifndef RPGSDL_H
#define RPGSDL_H

#include <stdlib.h>
#include <stdio.h>
 
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "mapSdl.h"
#include "Rpg.h"
#include "characSdl.h"
#include "monsterSdl.h"
#include "AI.h"
#include "fightSdl.h"
#include "BufferGame.h"
#include "sdlFunction.h"
#include "questDiarySdl.h"
#include "rewardSdl.h"

/**
 * @struct RpgSdl
 * @brief contain everything to display the RPG
 */
typedef struct{

		SDL_Window * screen;
		SDL_Renderer * renderer;
		CharacSdl* characSdl;
		MonsterSdl** monsterSdl;
		NpcSdl** npcSdl;
		MapSdl* mapSdl;
		QuestDiarySdl* diarySdl;
		Rpg* rpg;
		int nbMstr, size, nbNpc, drawDiary;
		BufferGame * buffer;



}RpgSdl;

void delay(unsigned int frameLimit);
int inputKeyboardRpg(SDL_Event event);
Fight* launchRpg(RpgSdl * rpgSdl, int * id);
void updatePlayerDisplayRpg(RpgSdl * rpgSdl);
void rpgSdlInit(RpgSdl * rpgSdl, Rpg * rpg, SDL_Window * screen, SDL_Renderer * renderer);
void rpgSdlFree(RpgSdl * rpgSdl);
RpgSdl*  rpgSdlCreate(Rpg * rpg, SDL_Window * screen, SDL_Renderer * renderer);
void drawRpg(RpgSdl* rpgSdl);
void updatePlayerAction(RpgSdl * rpgSdl);
void dialogSdl(RpgSdl * rpgSdl, NPC * npc);
void fightFromRpg(SDL_Window * screen, SDL_Renderer * renderer, RpgSdl* rpgSdl, Fight * fight, int id);
void removeMonsterSdlIRpg(RpgSdl * rpgSdl, int ind);
void movingAuto(RpgSdl * rpgSdl);
void updateNpcDisplay(RpgSdl * rpgSdl);
void checkObjectSdl(RpgSdl * rpgSdl);
void removeObjectSdlRpg(RpgSdl * rpgSdl, int i, int j);
#endif
