#ifndef FIGHTTXT_H
#define FIGHTTXT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Fight.h"
#include "AI.h"
#include "txt.h"


/**
 * @brief      Function to get the action from the keyboard.
 *
 * @return     The action to do regarding the key pressed.
 */
int inputKeyboardTxt();

/**
 * @brief      The function to draw the fight in TXT ( all the monsters and the player ect..)
 *
 * @param[in,out]     fight  Pointer to Fight.
 */
void drawFightTxt(Fight* fight);

/**
 * @brief      Draw the hud of the map ( The life and AP/MP)
 *
 * @param[in,out]     fight  Pointer to Fight.
 */
void drawHudTxt(Fight * fight);

/**
 * @brief      Draw the spellBar ( All the spells)
 *
 * @param[in,out]     fight  Pointer to Fight.
 */
void drawSpellBarTxt(Fight * fight);

/**
 * @brief      Create a fight and set the positions from a file
 *
 * @param[in,out]     fightName  The name of the file to open.
 * @warning    The file must exist !
 *
 * @return     return the fight initialised with the positions set.
 */
Fight* fightCreateTxt(char* fightName);

/**
 * @brief      Loop of the game, it continues while the fight isn't finished.
 *
 * @param[in,out]     fight  Pointer to fight.
 */
void launchFightTxt(Fight * fight);

/**
 * @brief      Call hitNRun.
 *
 * @param[in,out]     fight  Pointer to fight.
 * @param[in]  turn   The index of the monster 
 */
void hitNRunTxt(Fight * fight, int turn);

/**
 * @brief      Remove all related to a monster when it dies.
 *
 * @param[in,out]     fight    Pointer to fight
 * @param[in,out]     monster  The monster to kill and remove.
 */
void deleteMonsterTxt(Fight * fight, Monster * monster);

#endif