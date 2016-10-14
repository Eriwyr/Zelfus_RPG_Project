#ifndef FIGHTSDLMESCOUILLES_H
#define FIGHTSDLMESCOUILLES_H

#include "BufferGame.h"
#include <stdlib.h>
#include <stdio.h>
 
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "mapSdl.h"
#include "characSdl.h"
#include "npcSdl.h"
#include "monsterSdl.h"
#include "hudSdl.h"
#include "Fight.h"
#include "AI.h"
#include "SpellBar.h"
#include <stdlib.h>
#include <stdio.h>
#include "sdlFunction.h"


/**
 * @struct FightSdl
 * @brief Contains everything needed to display a Fight.
 */
typedef struct {
	Fight * fight; /**< The fight to display (link to Fight) */
	SDL_Window * screen; /**< The window used to display */
	SDL_Renderer * renderer; /**< The renderer used to display everything*/
	CharacSdl* characSdl; /**< The characSdl corresponding to the player of the fight (link to CharacSdl) */
	HudSdl* hudSdl; /**< The hudSdl of the Fight ( link to HudSdl) */
	MapSdl* mapSdl; /**< The mapSdl corresponding to the map of the fight ( link to MapSdl) */
	
	MonsterSdl ** monsterSdl; /**<Array of link to monstersSdl */
	int nbMstrSdl; /**< The number of MonsterSdl */
	int size; /**< The sized used by the array of monsters */
	BufferGame * buffer; /**< A link to BufferGame to handle actions */

}FightSdl;

/**
 * @brief      Initialise the fightSdl
 *
 * @param[in,out]     fightSdl  The fight sdl
 * @param[in,out]     screen    The window
 * @param[in,out]     renderer  The renderer
 * @param[in,out]     fight     The fight
 */
void fightSdlInit(FightSdl * fightSdl, SDL_Window * screen,  SDL_Renderer * renderer, Fight * fight);

/**
 * @brief      Free a fightSdl
 *
 * @param[in,out]     fightSdl  The fight sdl to free
 */
void fightSdlFree(FightSdl * fightSdl);

/**
 * @brief      Function getting the key pressed on the keyboard.
 *
 * @return     The action corresponding to the key.
 */
int inputKeyboard();

/**
 * @brief      Function to time
 *
 * @param[in]  frameLimit  The limit of the frame
 */
void delay(unsigned int frameLimit);



SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Loads the game.
 *
 * @param[in,out]     mapSdl      The map sdl
 * @param[in,out]     renderer    The renderer
 * @param[in,out]     characSdl   The charac sdl
 * @param[in,out]     monsterSdl  The monster sdl
 */
void loadGame(MapSdl* mapSdl, SDL_Renderer* renderer, CharacSdl* characSdl, MonsterSdl * monsterSdl);

/**
 * @brief      The function to draw the fight
 *
 * @param[in,out]     fightSdl  The fightSdl to draw.
 */
void drawGame(FightSdl * fightSdl);

/**
 * @brief      Main loop of the fight
 *
 * @param[in,out]     fightSdl  The fightSdl
 *
 * @return     A boolean to see whether the player won or not
 */
int launchFight(FightSdl * fightSdl);

/**
 * @brief      Remove a MonsterSdl from the fight
 *
 * @param[in,out]     fightSdl  The fightSdl.
 */
void deleteMonster(FightSdl * fightSdl);

/**
 * @brief      Update the HudSdl of the FightSdl
 *
 * @param[in,out]     fightSdl  The fightSdl
 */
void updateHud(FightSdl * fightSdl);

/**
 * @brief      Update the player ( when it moved)
 *
 * @param[in,out]     fightSdl  The fight sdl
 */
void updatePlayerDisplay(FightSdl * fightSdl);

/**
 * @brief      Execute an attack 
 *
 * @param[in,out]     fightSdl  FightSdl
 * @param[in]  attack    To see which attack is moving
 */
void actionAttackSdl(FightSdl * fightSdl, int attack);

/**
 * @brief      Call the HitNRun function and add the action to the buffer
 *
 * @param[in,out]     fightSdl  The fightSdl
 * @param[in]  turn      The index of the monster actually playing
 */
void hitNRunSdl(FightSdl * fightSdl, int turn);

/**
 * @brief      Update the monster ( when it moved)
 *The fight sdl
 * @param[in,out]     fightSdl  The fight sdl
 */
void updateMonsterDisplay(FightSdl * fightSdl);

/**
 * @brief      Get the monsterSdl at the index I of the fightSdl
 *
 * @param[in,out]     fightSdl  The fight sdl
 * @param[in]  i         The position in the array
 *
 * @return     The ith monstersdl of the fightSdl
 */
MonsterSdl* getMonsterSdlIFromFightSdl(FightSdl * fightSdl, int i);

/**
 * @brief      Update either the player or the monstes
 *
 * @param[in,out]     fightSdl  The fightSDl
 */
void updateDisplay(FightSdl * fightSdl);

/**
 * @brief      Update the actions of the player	
 *
 * @param[in,out]     fightSdl  The fight sdl
 */
void updatePlayerActionFight(FightSdl * fightSdl);

/**
 * @brief      Get the ith spell from the fightSdl
 *
 * @param[in,out]     fightSdl  The FightSdl
 * @param[in]  i         the index of the spell 
 *
 * @return     The ith spell from the fightSdl
 */
SpellSdl* getSpellSdlIFromFightSdl(FightSdl * fightSdl, int i);

/**
 * @brief      Update the spells ( when moving)
 *
 * @param[in,out]     fightSdl  The fight sdl
 */
void updateSpellDisplay(FightSdl * fightSdl);
#endif