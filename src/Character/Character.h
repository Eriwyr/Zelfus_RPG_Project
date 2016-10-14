#ifndef CHARACTER_H
#define CHARACTER_H

#include "QuestDiary.h"
#include "Weapon.h"
#include <math.h>
#include "OS.h"
#include "str.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
 * @struct Character
 * @brief Define the attibuts of a Character
 */
typedef struct{

	int id; /**< The unique id associate to the character.*/
	char* name; /**< The name of the character.*/
	int lifePoints; /**< The life points of the character.*/
	Weapon *weapon; /**< The weapon the character possedes. (link on Weapon)*/
	Stuff **stuffs;  /**< The stuff the character owns. (Array of link on stuffs)*/
	SpellBar* spellBar; /**< The Spell Bar ( to manage Spells ) of the character. (link on SpellBar)*/
	int strength; /**< The strength of the character ( will add damages ).*/
	int intelligence; /**< The intelligence of the chraracter ( to cast spells ).*/
	int wisdom;	/**<The wisdom of the character ( The higher the wisdom, the more you receive exeperience)*/
	QuestDiary* diary; /**< The Quest Diary of the character ( to manage Quests).*/
	int money; /**< the amount of money of the character*/
	int level; /**< The level of the character, the higher the level, the better are the caracteristics*/
	int xp; /**< The amount of exeperience. */
	Position* pos; /**< The position of the Character to see it on the Map.*/

}Character;

enum stuff {HEAD, BODY, PANTS, BOOTS};

/**
 * @fn void characterInit(Character * player);
 * @brief      Initialize a character.
 *
 * @param[in,out]     player : pointer to a character.
 * @return none
 */
void characterInit(Character * player);

/**
 * @fn Character* characterCreate();
 *
 * @brief      Create a character in the heap.
 *
 * @return     the character initalized.
 */
Character* characterCreate();

/**
 * @fn 		   void characterFree(Character * player);
 * 
 * @brief      Free memory.
 *
 * @param[in,out]     player  : pointer to Character ( will be freed).
 */
void characterFree(Character * player);

/**
 * @fn         void characterDestroy(Character ** player);
 *
 * @brief      Free memory when alocated with characterCreate().
 *
 * @param[in,out]     player : double pointer to Character ( allow to modify its value thus to free it).
 */
void characterDestroy(Character ** player);

/**
 * @fn 		   char* getNameCharacter(const Character* player);
 * @brief      Getter of the atribtus name of a Character
 *
 * @param[in]  player  : pointer to Character
 *
 * @return     the name of player
 */
char* getNameCharacter(const Character* player);

/**
 * @fn void setNameCharacter(Character* player, char* name);
 * @brief      Setter of the name of a Character
 *
 * @param[in,out]      player  : pointer to Character
 * @param[in]      name    the new name to set.
 */
void setNameCharacter(Character* player, char* name);

/**
 * @fn  	   int getLifePointsCharacter(const Character* player);
 * @brief      Getter of the life points of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the life points of the character.
 */
int getLifePointsCharacter(const Character* player);



/**
 * @fn void setLifePointsCharacter(Character* player, int lifePoints);
 * @brief      Setter of the attributs lifePoints of a Character
 *
 * @param[in,out]     player      pointer to Character
 * @param[in]  lifePoints  the new lifePoint to set.
 * @return none
 */
void setLifePointsCharacter(Character* player, int lifePoints);

/**
 * @fn  	   Weapon* getWeaponCharacter(const Character* player);
 * @brief      Getter of the weapon of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the weapon of the character.
 */
Weapon* getWeaponCharacter(const Character* player);

/**
 * @fn void setWeaponCharacter(Character* player, Weapon* weapon);
 * @brief      Setter of the attributs weapon of a Character
 *
 * @param[in,out]      player      pointer to Character
 * @param[in]  weapon  the new weapon to set.
 * @return none
 */
void setWeaponCharacter(Character* player, Weapon* weapon);

/**
 * @fn  	   Stuff** getSutffsCharacter(const Character* player);
 * @brief      Getter of the stuff of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the Stuff of the character.
 */
Stuff** getSutffsCharacter(const Character* player);

/**
 * @fn         void setSutffsCharacter(Character* player, Stuff* stuff, int i);
 *
 * @brief      setter of the attributs stuff.
 *
 * @param[in,out]     player  : pointer to Character
 * @param[in,out]     stuff  the new stuff to set.
 */
void setSutffsCharacter(Character* player, Stuff* stuff, int i);

/**
 * @fn  	   SpellBar* getSpellBarCharacter(const Character* player);
 * @brief      Getter of the weapon of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the spell bar of the character.
 */
SpellBar* getSpellBarCharacter(const Character* player);

/**
 * @fn         void setSpellBarCharacter(Character* player, SpellBar* spellBar);
 *
 * @brief      setter of the attributs spellBar.
 *
 * @param[in,out]     player    : pointer to player.
 * @param[in,out]     spellBar  : the new spellBar to set.
 */
void setSpellBarCharacter(Character* player, SpellBar* spellBar);

/**
 * @fn  	   int getStrengthCharacter(const Character* player);
 * @brief      Getter of the strength of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the stregth of the character.
 */
int getStrengthCharacter(const Character* player);

/**
 * @fn         void setStrengthCharacter(Character* player, int strength);
 *
 * @brief      setter of the attributs strength.
 *
 * @param[in,out]     player    : pointer to Character.
 * @param[in]  strength  : the new strength to set.
 */
void setStrengthCharacter(Character* player, int strength);

/**
 * @fn  	   int getIntelligenceCharacter(const Character* player);
 * @brief      Getter of the intelligence of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the intelligence of the character.
 */
int getIntelligenceCharacter(const Character* player);

/**
 * @fn         void setIntelligenceCharacter(Character* player, int intelligence);
 *
 * @brief      setter of the intelligence.
 *
 * @param[in,out]     player      : pointer to intelligence
 * @param[in]  intelligence  : the new intelligence to set.
 */
void setIntelligenceCharacter(Character* player, int intelligence);

/**
 * @fn  	   int getWisdomCharacter(const Character* player);
 * @brief      Getter of the wisdom of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the wisdom of the character.
 */
int getWisdomCharacter(const Character* player);

/**
 * @fn         void setWisdomCharacter(Character* player, int wisdom);
 *
 * @brief      setter of the wisdom.
 *
 * @param[in,out]     player  : pointer to Charater.
 * @param[in]  wisdom  : the new wisdom to set.
 */
void setWisdomCharacter(Character* player, int wisdom);

/**
 * @fn  	   QuestDiary* getDiaryCharacter(const Character* player);
 * @brief      Getter of the diary of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the diary of the character.
 */
QuestDiary* getDiaryCharacter(const Character* player);

/**
 * @fn         void setDiaryCharacter(Character* player, QuestDiary* diary);
 *
 * @brief      setter of the diary.
 *
 * @param[in,out]     player  : pointer to Character.
 * @param[in,out]     diary   : the new diary to set.
 */
void setDiaryCharacter(Character* player, QuestDiary* diary);

/**
 * @fn  	   int getMoneyCharacter(const Character* player);
 * @brief      Getter of the money of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the money of the character.
 */
int getMoneyCharacter(const Character* player);

/**
 * @fn         void setMoneyCharacter(Character* player, int money);
 *
 * @brief      setter of the money of teh character.
 *
 * @param[in,out]     player  : pointer to Character.
 * @param[in]  money   : the new amount of money to set.
 */
void setMoneyCharacter(Character* player, int money);

/**
 * @fn  	   int getLevelCharacter(const Character* player);
 * @brief      Getter of the weapon of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the level of the character.
 */
int getLevelCharacter(const Character* player);

/**
 * @fn         void setLevelCharacter(Character* player, int level);
 *
 * @brief      setter of the attributs level.
 *
 * @param[in,out]     player  : pointer to character
 * @param[in]  level   : the new level to set.
 */
void setLevelCharacter(Character* player, int level);

/**
 * @fn  	   Position* getPositionCharacter(const Character* player);
 * @brief      Getter of the position of a Character.
 *
 * @param[in]  player  : pointer to Character.
 *
 * @return     the position of the character.
 */
Position* getPositionCharacter(const Character* player);

/**
 * @fn         void setPositionCharacter(Character* player, int x, int y);
 *
 * @brief      setter of the position.
 *
 * @param[in,out]     player  : pointer to Character.
 * @param[in,out]     pos     : the new Position to set.
 */
void setPositionCharacter(Character* player, int x, int y);

/**
 * @brief      Get the id of the player	.
 *
 * @param[in]  player  Pointer to Character.
 *
 * @return     The id of the character.
 */
int getIdCharacter(const Character* player);

/**
 * @brief      Set the id of the player
 *
 * @param[in,out]     player  Pointer to Character.
 * @param[in]  id      the new id to set.
 */
void setIdCharacter(Character* player, int id);

/**
 * @brief      Get the Ith stuff of the character.
 *
 * @param[in]  player  Poiner to Character.
 * @param[in]  i       The index of the stuff to get.
 *
 * @return     The Ith stuff of the player.
 */
Stuff* getStuffICharacter(const Character* player, int i);

/**
 * @fn         void characterTest();
 *
 * @brief      Unit testing of the function of a Character.
 */

/**
 * @brief      Allow a character to attack a monster
 *
 * @param[in]      Character  The character that will attack.
 * @param[in,out]      monster    the monster attacked.
 *
 * @return     Return 1 if the attack is successful, 0 otherwise.
 */
int attackMonster(Character * Character, Monster * monster);

/**
 * @fn         void characterTest();
 * @brief      unit testing of Character.
 */
void characterTest();

/**
 * @brief      Get the xp of the character.
 *
 * @param[in]  player  pointer to character.
 *
 * @return     the xp of the character.
 */
int getXpCharacter(const Character* player);

/**
 * @brief      Set the xp of the character.
 *
 * @param[in,out]     player  pointer to Character.
 * @param[in]  xp      the xp to set.
 */		
void setXpCharacter(Character* player, const int xp);

/**
 * @brief      Calculate the amount of xp necessary to level up.
 *
 * @param[in]  level  the current level of the player
 *
 * @return     The amount of xp needed to level up.
 */
int amountToNewLevel(int level);

/**
 * @brief      Update the stats of the player based on it's level
 *
 * @param[in,out]     player  Pointer to Character.
 */
void levelUp(Character * player);

/**
 * @brief      Load all the atributs of a Character in a file.
 *
 * @param[in,out]     fileName  The name of the file to open
 * @warning    The file must exist !
 *
 * @return     A character initialized with the values of the file.
 */
Character* loadCharacterFromFile(char* fileName);

/**
 * @brief      Save the atributs of the player in a file.	
 *
 * @param[in,out]     player    The player to save.
 * @param[in,out]     fileName  the name of the file to open.
 */
void saveCharacterOnFile(Character * player, char* fileName);

/**
 * @brief      The function to attack a monster with a spell
 *
 * @param[in,out]     player   Pointer to player.
 * @param[in,out]     monster  The monster to attack.
 * @param[in,out]     spell    The spell casted.
 *
 * @return     A boolean to check wheter the attack was successful or not.
 */
int attackMonsterSpell(Character* player, Monster* monster, Spell* spell);


#endif	
