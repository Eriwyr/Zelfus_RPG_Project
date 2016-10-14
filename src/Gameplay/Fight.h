#ifndef FIGHT_H
#define FIGHT_H

// #include "Rpg.h"
#include "Map.h"
#include <time.h>
#include "OS.h"
#include "str.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX


enum actions {ATTACK_1, ATTACK_2, ATTACK_3, ATTACK_4, MOVE_UPWARD, MOVE_DOWNWARD, MOVE_LEFT,
	MOVE_RIGHT, NOTHING, PICK,  YES, NO, TALK, DIARY, QUIT};

/**
 * @struct Fight
 * @brief Contain a map, a player and a group of ennemies.
 */
typedef struct {
	int id;
	Map * map; /**< The map of the fight.*/
	Character * player; /**< The character of the fight. ( link to Character) */
	Horde * horde; /**< The horde of the fight ( link to Horde). */
	int mpPlayer; /**< The number of movement the player can do in one turn */
	int apPlayer; /**< The number of actions the player can do in one turn */
	int apEnnemy; /**< The number of actions the ennemy can do in one turn */
	int mpEnnemy; /**< The amount of movement the ennemy can do in one turn */
	Monster* actualMonsterAttacked; /**< The monster we are going to attack */
	int toKill; /**< a boolean to check if we need to kill a monster */
	int nbMstrKilled; /**< A counter of how many monsters we have killed */
}Fight;




enum actual_player {PLAYER, ENNEMY};


/*Enum with type of monster ( archer, brutal, runner, healer .... ) TO DEFINE !!!*/


/**
 * @brief       start a fight and continue while the fight isn't over.
 *
 * @param[in,out]    fight           pointer to fight.
 * @param[in]  		actionFunction  Pointer to function to get the action to do.
 * @param[in]  		mapDisplay      Pointer to function to display the map.
 */
void beginFight(Fight * fight, int (*actionFunction)(void), Monster* (*whoToAttack)(Fight * fight), void (*displayFight)(Fight*));

/**
 * @brief      Boolean function returning true if the life of one of the participants is = 0
 *
 * @param[in,out]      fight  Pointer to fight.
 *
 * @return     0 or 1 depending on the result.
 */
int isFinished(Fight * fight);

/**
 * @brief      Create the map, set the position of the characters and monsters
 *
 * @param[in,out]      fight       Pointer to fight.
 * @param[in]  mapDisplay  Pointer to function to display the map.
 */
void loadFight(Fight * fight);


/**
 * @brief      Getter of the map of a fight.
 *
 * @param[in]  fight  Pointer to fight
 * 
 * @return     The map of the fight.
 */
Map* getMapFight(const Fight* fight);

/**
 * @brief      Setter of the map.
 *
 * @param[in,out]     fight  Pointer to fight.
 * @param[in,out]     map    the new map to set.
 */
void setMapFight(Fight* fight, Map* map);

/**
 * @brief      Getter of the character of a Fight.
 *
 * @param[in]  fight  Pointer to fight.
 *
 * @return     The character of the fight.
 */
Character* getCharacterFight(const Fight* fight);

/**
 * @brief      Getter of the monster of a Fight.
 *
 * @param[in]  fight  Pointer to fight.
 *
 * @return     The monster of the fight.
 */
Horde* getHordeFight(const Fight* fight);

/**
 * @fn 		   void moveOnFight(Fight * fight, int entity, int direction);
 *
 * @brief      Allow to move an entity ( player or monster) on the map during a fight.
 *
 * @param[in,out]     map        The current map.
 * @param[in]  entity     The entity that will move
 * @param[in]  direction  the direction the entity will aim to.
 * 
 * @return a value to see if the movement was succesful.s
*/

/**
 * @brief      { function_description }
 *
 * @param[in,out]      fight      Pointer to fight.
 * @param[in]  i          the index of the monster to move.
 * @param[in]  direction  the direction in which the monster will move.
 *
 * @return     1 if the movement succeed, 0 otherwise.
 */
int moveMonsterOnFight(Fight * fight, int i, int direction);

/**
 * @brief      delete a monster from the horde.
 *
 * @param[in,out]      fight    The fight contaning the horde.
 * @param[in,out]      monster  the monster to delete.
 */
void killMonster(Fight * fight, Monster * monster);

/**
 * @brief      Return the closest monster to the player.
 *
 * @param[in,out]     fight  Pointer to fight.
 *
 * @return     the monster which is the closest to the player.
 */
Monster* getClosestMonster(Fight * fight);


/**
 * @brief      Move the player on the map of the fight
 *
 * @param[in,out]     fight      pointer to Fight.
 * @param[in]  direction  The direction in which you care to move.
 *
 * @return     A boolean to check if the movement was successful.
 */
int movePlayerOnFight(Fight * fight, int direction);

/**
 * @brief      Determine if the cell of coordonate x y is empty.
 *
 * @param[in,out]     fight  pointer to Fight.
 * @param[in]  x      the x coordonate
 * @param[in]  y      the y coordonate
 *
 * @return     1 if the cel is empy, 0 otherwise.
 */
int isEmpty(Fight * fight, int x, int y);

/**
 * @brief      Get the apPlayer of the fight.
 *
 * @param[in]  fight  pointer to Fight.
 *
 * @return     the apPlayer of the fight.
 */
int getApPlayerFight(const Fight* fight);

/**
 * @brief      Set the apPlayer of the fight.
 *
 * @param[in,out]     fight     pointer to Fight.
 * @param[in]  apPlayer  the apPlayer to set.
 */
void setApPlayerFight(Fight* fight, const int apPlayer);

/**
 * @brief      Get the mpPlayer of the fight.
 *
 * @param[in]  fight  pointer to Fight.
 *
 * @return     the mpPlayer of the fight.
 */
int getMpPlayerFight(const Fight* fight);

/**
 * @brief      Set the mpPlayer of the fight.
 *
 * @param[in,out]     fight     pointer to Fight.
 * @param[in]  mpPlayer  the mpPlayer to set.
 */
void setMpPlayerFight(Fight* fight, const int mpPlayer);

/**
 * @brief      Get the apEnnemy of the fight.
 *
 * @param[in]  fight  pointer to Fight.
 *
 * @return     the apEnnemy of the fight.
 */		
int getApEnnemyFight(const Fight* fight);

/**
 * @brief      Set the apEnnemy of the fight.
 *
 * @param[in,out]     fight     pointer to Fight.
 * @param[in]  apEnnemy  the apEnnemy to set.
 */
void setApEnnemyFight(Fight* fight, const int apEnnemy);

/**
 * @brief      Get the mpEnnemy of the fight.
 *
 * @param[in]  fight  pointer to Fight.
 *
 * @return     the mpEnnemy of the fight.	
 */
int getMpEnnemyFight(const Fight* fight);

/**
 * @brief      Set the mpEnnemy of the fight.
 *
 * @param[in,out]     fight     pointer to Fight.
 * @param[in]  mpEnnemy  the mpEnnemy to set.
 */
void setMpEnnemyFight(Fight* fight, const int mpEnnemy);

/**
 * @brief      unit testing of Fight.s
 */
void fightTest();

/**
 * @brief      Generate random positions and set them for all the monsters.
 *
 * @param[in,out]     fight  Pointer to Fight.
 */
void setMonstersOnRandomPosition(Fight * fight);

/**
 * @brief      Load the attributs of the fight from a file
 *
 * @param[in,out]     fileName  The name of the file to open.
 *
 * @return     A fight initialized with the value of the file.
 */
Fight* loadFightFromFile(char* fileName, Character* player);

/**
 * @brief      Initialize a fight
 *
 * @param[in,out]     fight  The fight to initialize
 */
void fightInit(Fight * fight);

/**
 * @brief      Create a Fight in the Heap
 *
 * @return     The fight created and initialised.
 */
Fight* fightCreate();

/**
 * @brief      Free memory of the Fight.
 *
 * @param[in,out]     fight  Pointer to fight.
 */
void fightFree(Fight * fight);

/**
 * @brief      Free memory when allocated with fightCreate()
 *
 * @param[in,out]     fight  Pointer to Fight.
 */
void fightDestroy(Fight ** fight);


/**
 * @brief      Execute an attack passed in parameter
 *
 * @param[in,out]     fight   Pointer to fight
 * @param[in]  attack  The attack to do.
 *
 * @return     A boolean to check if the attack succeed or not.
 */
int actionAttack(Fight * fight, int attack);

/**
 * @brief      Execute a movement in a direction passed in parameter.
 *
 * @param[in,out]     fight      Pointer to Fight.
 * @param[in]  direction  The direction toward which the player will go.
 */
void actionMove(Fight * fight, int direction);

int getToKillFight(const Fight* fight);

void setToKillFight(Fight* fight, int value);

Map* getMapFight(const Fight* fight);

int getIdFight(const Fight* fight);
void setIdFight(Fight* fight, const int id);
int getNbMstrKilledFight(const Fight * fight);

Monster* getActualMonsterAttackedFight(const Fight* fight);
#endif