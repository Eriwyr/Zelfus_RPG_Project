#ifndef HORDE_H
#define HORDE_H

#include "Monster.h"

/**
@struct Horde
@brief Contain an dynamic array of Monster.
*/
typedef struct {
	Monster ** monsters; /**<array of link to monsters*/
	int nbMstr; /**< the number of Monster actually present in the array*/
	int size; /**< the size of the array*/
} Horde;



/**
@fn void hordeInit(Horde * horde, int nbMstr);
@brief Initialize dynamically the array of quests
@param[in,out]horde : pointer to Horde.
@return none
*/
void hordeInit(Horde * horde, int nbMstr);


/**
@fn void hordeFree(Horde * horde);
@brief Free memory
@param[in,out]horde : pointer to Horde ( will be freed)
@return none
*/
void hordeFree(Horde * horde);

/**
@fn Horde* hordeCreate(int nbMstr);
@brief Initialize dynamycally a Horde.
@param[in,out]none
@return Horde* link to a Horde
*/
Horde* hordeCreate(int nbMstr);

/**
@fn void hordeDestroy(Horde ** horde);
@brief Free memory when Horde was initialized by hordeCreate().
@param[in,out]horde : double pointer (allow to change the first pointer thus to free it).
@return none
*/
void hordeDestroy(Horde ** horde);


/**
@fn void addMonster(Horde * horde, Monster * newMonster);
@brief Add a quest to the horde.
@param[in,out]horde : pointer to Horde ( will be affected).
@param[in,out]newMonster : the Monster that will be added.
@warning newMonster : Is a constant !
@return none
*/
void addMonster(Horde * horde, Monster * newMonster);

/**
@fn void removeMonster(Horde * horde, int ind);
@brief delete the quest of index i. 
@param[in,out]horde : pointer to Horde ( will be affected).
@param[in,out]ind : index of the quest to delete. 
@warning : First element is index 1.
*/
void removeMonster(Horde * horde, int ind);


/**
@fn int getNbMstrHorde(const Horde * horde);
@brief Getter of nbMonsters;
@param[in,out]horde : pointer to Horde.
@warning horde : Is a constant ! 
@return The number of monsters in  horde.
*/
int getNbMstrHorde(const Horde * horde);

/**
@fn Monster* getMonstersHorde(const Horde * horde);
@brief getter of the array of monsters.
@param[in,out]horde : pointer to Horde.
@warning horde is a constant.
@return the array of monsters of horde
*/
Monster** getMonstersHorde(const Horde * horde);

/**
 * @brief      Return the ieme element of the array of monsters
 *
 * @param[in]  horde  pointer to horde.
 * @param[in]  i      index of the element that will be returned.
 *
 * @return     the monster at the position i in the array.
 */
Monster* getElementIHorde(const Horde * horde, int i);

/**
 * @brief      Get the size of the horde.
 *
 * @param[in]  horde  pointer to Horde.
 *
 * @return     the size of the horde.
 */
int getSizeHorde(const Horde* horde);

/**
@fn void hordeTest();
@brief unit testing of Horde
@param[in,out]none
@return none
*/
void hordeTest();

#endif