#ifndef TXT_H
#define TXT_H

#include "OS.h"
#include "Map.h"
#include "Character.h"
#include "Monster.h"
#include "Rpg.h"

#ifndef WINDOWS_OS
	//Unix library for sleep
	#include <unistd.h>
#endif //WINDOWS_OS


/**
 * @brief      The the map to display it after.
 *
 * @param[in,out]     map   Pointer to Map.
 */
void setMapTxt(Map * map);

/**
 * @brief      Set the player on the map.
 *
 * @param[in,out]     player  Pointer to Character.
 * @param[in,out]     map     The map on which it'll be set.
 */
void setPlayerTxt(Character * player, Map* map);

/**
 * @brief      Set the monsters on the map
 *
 * @param[in,out]     horde  Pointer to Horde.
 * @param[in,out]     map    The map on wich they'll be set.
 */
void setMonsterTxt(Horde * horde, Map* map);

/**
 * @brief      draw the map in TXT
 *
 * @param[in,out]     map   The map the display.
 */
void drawMapTxt(Map* map);

/**
 * @brief      Idle the program for a certain time
 *
 * @param[in]  seconds  The time to wait.
 */
void delayTxt(unsigned int seconds);

/**
 * @brief      Clear the console ( Cross Platform)
 */
void clear();

/**
 * @brief      Convert seconds to millisec
 *
 * @param[in]  sec   The amount of seconds to convert.
 *
 * @return     return the same amount but in milliseconds.
 */
int convertSecToMillisec(int sec);

#endif