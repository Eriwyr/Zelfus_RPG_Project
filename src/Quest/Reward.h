#ifndef REWARD_H
#define REWARD_H


#include <stdio.h>
#include <stdlib.h>
#include "Stuff.h"
#include "Weapon.h"


/**
*@struct Reward
*@brief define the atributs of a reward.
*/
typedef struct {
	int money;
	int xp;
} Reward;

/*Functions of reward */

/**
*@fn void rewardInit(Reward * reward, int money, int xp);
*@brief Initialize a reward.
*@param[in,out]reward : pointer to Reward.
*@param[in,out]money : the amount of money set.
*@param[in,out]xp : the amount of xp set.
*@param[in,out]nbStuffs : the number of stuff that the reward will contain.
*@param[in,out]nbWeapons : the number of weapons that the reward will contain.
*@return none
*/
void rewardInit(Reward * reward, int money, int xp);

/**
*@fn rewardFree(Reward * reward);
*@brief Free memory.
*@param[in,out]reward : pointer to reward ( will be freed);
*@return none
*/
void rewardFree(Reward * reward);

/**
 * @brief      Create a Reward in the heap
 *
 * @param[in]  money      the money to set
 * @param[in]  xp         the xp to set.
 * @param[in]  nbStuffs   the number of stuffs that the reward will contain
 * @param[in]  nbWeapons  the number of weapons the reward will contain.
 *
 * @return     a pointer to Reward ( initialised )
 */
Reward* rewardCreate(int money, int xp);

/**
 * @brief      Free memory when initialised whith rewardCreate
 *
 * @param[in,out]     reward  double pointer to Reward ( allow to modify its value, thus to free it).
 */
void rewardDestroy(Reward ** reward);


/**
*@fn void rewardTest();
*@brief Unit testing of Reward.
*@param[in,out]none
*@return none
*/
void rewardTest();


/**
*@fn int getMoneyReward(const Reward * reward);
*@brief getter of the atributs money.
*@param[in,out]reward : pointer to a reward 
*@warning reward is a constant !
*@return the amount of money of the reward.
*/
int getMoneyReward(const Reward * reward);

/**
*@fn int getXpReward(const Reward * reward);
*@brief getter of the atributs xp.
*@param[in,out]reward : pointer to a reward 
*@warning reward is a constant !
*@return the amount of xp of the reward.
*/
int getXpReward(const Reward * reward);


#endif