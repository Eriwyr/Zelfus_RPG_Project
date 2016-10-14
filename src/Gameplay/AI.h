#ifndef AI_H
#define AI_H

#include "Fight.h"
#include <math.h>



/**
 * @brief      Return the direction to go if you want to go toward a position
 *
 * @param[in,out]     fight  Pointer to fight.
 * @param[in]  i      the index of the monster to move
 * @param[in,out]     pos    the position to go toward
 * @param[in,out]     map    the map on which we check
 *
 * @return     the direction in which to go.
 */
int moveToward(Fight * fight,int i, Position * pos, Map * map);

/**
 * @brief      Allow a monster to attack the player
 *
 * @param[in,out]     monster  pointer to Monster.
 * @param[in,out]     player   the player to attack.
 *
 * @return     A boolean to see wheter the attack succeed or not.
 */
int attackPlayer(Monster * monster, Character * player);

/**
 * @brief      Return the direction to go if you want to go away a position
 *
 * @param[in,out]     fight  Pointer to fight.
 * @param[in]  i      the index of the monster to move
 * @param[in,out]     pos    the position to go away from
 * @param[in,out]     map    the map on which we check
 *
 * @return     the direction in which to go.
 */
int moveAway(Fight * fight, int i, Position * pos, Map * map);

/**
 * @brief      The artificial intelligence of the fight
 *
 * @param[in,out]     fight  The fight played
 * @param[in]  turn   The turn of the monster who attack.
 */
void hitNRun(Fight * fight, int turn);

/**
 * @brief      Move the monster of index i closer to the player
 *
 * @param[in,out]     fight  pointer to Fight.
 * @param[in]  i      index of the monster
 *
 * @return     -1 if the monster couldn't get closer.
 */
void getCloser(Fight * fight, int i);

/**
 * @brief      Move the monster of index i away of the player
 *
 * @param[in,out]     fight  pointer to Fight.
 * @param[in]  i      index of the monster
 *
 * @return     -1 if the monster couldn't get away.
 */
void getAway(Fight * fight, int i);

/**
 * @brief      unit testing of the AI.
 */
void IAtest();

#endif



