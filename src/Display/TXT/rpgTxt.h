#ifndef RPGTXT_H
#define RPGTXT_H

#include "Rpg.h"
#include "txt.h"
#include "BufferGame.h"
/**
 * @struct RpgTxt
 * @brief contain everything to diplay the rpg in txt
 * 
 */
typedef struct {
	Rpg * rpg;
	BufferGame * buffer;
} RpgTxt;


/**
 * @brief      Function to get the action from the keyboard.
 *
 * @return     The action to do regarding the key pressed.
 */
int inputKeyboardRpgTxt();

/**
 * @brief      Draw the rpg ( all the npc, objects, player ect..)
 *
 * @param[in,out]     rpg  Pointer to Rpg.
 */
void drawRpgTxt(Rpg * rpg);

/**
 * @brief      Determine what to display when talking to the npc and displays it.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 * @param[in,out]     npc   The npc your talking to.
 */
void dialogueTxt(Rpg * rpg, NPC * npc);

/**
 * @brief      Loop of the rpg, continues while we don't quit.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 */
void launchRpgTxt(Rpg * rpg);

/**
 * @brief      Place all the npcs on the map to displays them after.
 *
 * @param[in,out]     rpg   The rpg
 */
void setNpcTxt(Rpg * rpg);

#endif