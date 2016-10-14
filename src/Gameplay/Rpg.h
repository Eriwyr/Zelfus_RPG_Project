#ifndef RPG_H
#define RPG_H

#include "Character.h"
#include "NPC.h"
#include "Horde.h"
#include "Map.h"
#include "str.h"
#include "OS.h"
#include "monsterRpg.h"
#include "Doors.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
 * @strcut Rpg
 * @brief Structure of the rpg, contains everything to play
 */
typedef struct{
	Character* player; /**< The player of the RPG ( link to Character) */
	Map * map; /**< The map of the rpg (link to Map) */
	Map * map1;/**< A map to put everything and to check when moving ( facilize movements	) */
	NPC ** npc;/**< An array of link to NPC.  */
	MonsterRpg ** monsters; /**< An array of monsterRpg. */
	int nbNpc; /**< The number of NPC in the rpg. */
	int nbMstr; /**< The number of monstersRpg in the rpg*/ 
	int size; /**< The size of the array of monstersRpg */
	Door** doors; /**The doors allowing to pass on another map ( array of link to Door )*/
	int nbDoors; /**The number of doors*/

}Rpg;


/**
 * @brief      Reward the player.
 *
 * @param[in,out]     player  Pointer to Character.
 * @param[in,out]     npc     Pointer to NPC.
 */
void reward(Character * player, NPC* npc);


/**
 * @brief      Test of talking to an NPC
 *
 * @param[in,out]     rpg   Pointer to RPG.
 * @param[in]  i     the index of the npc we are talking to.
 */
void test(Rpg * rpg, int i);

/**
 * @brief      Accept the quests of the Ith NPC and add it in the player's diary.
 *
 * @param[in,out]     player   Pointer to Character.
 * @param[in]  i     the index of the NPC.
 */
void acceptQuest(Rpg * rpg, NPC* npc);

/**
 * @brief      Talk to an NPC
 *
 * @param[in,out]     player  Pointer to Character.
 * @param[in,out]     npc     The NPC we're talking to.
 *
 * @return     a boolean to see if we already spoke to it or not.
 */
int talkToNpc(Rpg * rpg, NPC * npc);

/**
 * @brief      Check if the tile of coordonates x and y is empty and available
 *
 * @param[in,out]     rpg   Pointer to RPG.
 * @param[in]  x     the x coordonate to check.
 * @param[in]  y     the y coordonate to check.
 *
 * @return     True if empty , False otherwise.
 */
int isEmptyRpg(Rpg * rpg, int x, int y);

/**
 * @brief      Function to move the player during the Rpg.
 *
 * @param[in,out]     rpg        Pointer to RPG.
 * @param[in]  direction  The direction toward which we're moving.
 *
 * @return     A boolean to see if the movement was successful.
 */
int movePlayerOnRpg(Rpg * rpg, int direction);

/**
 * @brief      Initialise the second map of the Rpg.
 *
 * @param[in,out]     rpg   Pointer to RPG.
 */
void rpgInitSecondMap(Rpg * rpg);

/**
 * @brief      Get the id of an NPC.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 * @param[in,out]     npc   The npc on whom we get the id.
 *
 * @return     The id of npc.
 */
int getIdFromNpc(Rpg * rpg, NPC * npc);

/**
 * @brief      Load the attributs of an Rpg from a file
 *
 * @param[in,out]     fileName  the name of the file to open.
 * @warning    The file must exist !
 *
 * @return     A Rpg initialized with the values of the file.
 */
Rpg* loadRpgFromFile(char* fileName);

/**
 * @brief      Free memory when allocated with rpgCreate
 *
 * @param[in,out]     rpg   Double pointer to rpg ( allow to free the pointer )
 */
void rpgDestroy(Rpg** rpg);

/**
 * @brief      Get the closest object to the player.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 *
 * @return     The closest object.
 */
QuestObject* getClosestObject(Rpg * rpg);

/**
 * @brief      Unit testing of Rpg.
 */
void rpgTest();


/**
 * @brief      Get the number of Npc from the Rpg.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 *
 * @return     The number of Npc.
 */
int getNbNpcRpg(Rpg * rpg);

/**
 * @brief      get the Ith Npc from the Rpg.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 * @param[in]  i     the index of the npc
 *
 * @return     The Ith Npc.
 */
NPC* getNpcIRpg(const Rpg * rpg, int i);

int getNbMstrRpg(const Rpg * rpg);
MonsterRpg* getMonsterRpgIRpg(const Rpg * rpg, int i);
int moveNpcRandom(Rpg * rpg);
void removeMonsterRpgI(Rpg * rpg, int ind);
void changeLevelRpg(Rpg * rpg, Map * map);
int checkDoors(Rpg * rpg);

/**
 * @brief      Pick an object on the map, remove it from the objective of the corresponding quest.
 *
 * @param[in,out]     rpg     Pointer to Rpg.
 * 
 * @return     Int to check if the pickup was succesful.
 */
int pickUpObject(Rpg * rpg, int * i, int *j);

/**
 * @brief      Check if any of the quest is finished.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 */
void checkQuests(Rpg * rpg);

/**
 * @brief      Update the second map of the Rpg
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 */
void updateSecondMap(Rpg* rpg);

/**
 * @brief      get the player of the Rpg
 *
 * @param[in]  rpg   Pointer to Rpg.
 *
 * @return     The character of  rpg.
 */
Character* getCharacterRpg(const Rpg* rpg);

/**
 * @brief      set the character of the Rpg
 *
 * @param[in,out]     rpg     Pointer to Rpg.
 * @param[in,out]     player  The new character to set.
 */
void setCharacterRpg(Rpg* rpg, Character* player);

/**
 * @brief      Return the map of the Rpg.
 *
 * @param[in]  rpg   Pointer to Rpg.
 *
 * @return     The map of the rpg.
 */
Map* getMapRpg(const Rpg* rpg);

/**
 * @brief      set the map of the Rpg.
 *
 * @param[in,out]     rpg   Pointer to Rpg.
 * @param[in,out]     map   The new map to set.
 */
void setMapRpg(Rpg* rpg, Map* map);

/**
 * @brief      Save the attributs of the Rpg on a file
 *
 * @param[in,out]     rpg       The Rpg to save.
 * @param[in,out]     fileName  the name of the file to open.
 */
void saveRpgOnFile(Rpg * rpg, char* fileName);

/**
 * @brief      Check if we have to launch a fight or not
 *
 * @param[in,out]     rpg   The rpg actually playing
 *
 * @return     A fight if need be, NULL otherwise.
 */
Fight * checkForFight(Rpg * rpg, int * id);

#endif //RPG_H