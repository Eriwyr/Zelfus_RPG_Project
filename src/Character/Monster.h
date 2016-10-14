#ifndef MONSTER_H
#define MONSTER_H


#include "Weapon.h"
#include "SpellBar.h"
#include "Position.h"
#include "OS.h"
#include "str.h"


#ifndef CHAR_SIZE_MAX
#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX


/**
*@struct Monster
*@brief Define the atributs of a Monster
*/
typedef struct {
	int id; /**< The id of the monster.*/
	char * name; /**< the name of the monster.*/
	int lifePoints; /**< The life points of the monster*/
	int strength; /**< The strength of the monster.*/
	int intelligence; /**< The intelligence of the monster.*/
	int strengthRes; /**<The resistance of the monster against strength attacks*/
	int intellRes; /**<The resistance of the monster against intelligence attacks ( magical )*/
	SpellBar * spellBar; /**<link on SpellBar*/
	Weapon * weapon; /**<link on Weapon*/
	Position * pos; /**<link on Position*/
} Monster;

/**
*@fn void monsterInit(Monster * monster, const char * name);
*@brief Initialize a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]name : the name that'll be set.
*@return none
*/
void monsterInit(Monster * monster, const char * name);

/**
*@fn void monsterFree(Monster * monster);
*@brief Free memory.
*@param[in,out]monster : pointer to monster( will be freed).
*@return none
*/
void monsterFree(Monster * monster);

/**
*@fn Monster* monsterCreate(const char * name);
*@brief Initialize a monster in the Heap.
*@param[in,out]name : the name that'll be set.
*@return The monster newly initalized.
*/
Monster* monsterCreate(const char * name);

/**
*@fn void monsterDestroy(Monster ** monster);
*@brief Free memory when initialized with monsterCreate().
*@param[in,out]monster : double pointer to monster ( allow to change the pointer thus free it).
*@return none
*/
void monsterDestroy(Monster ** monster);

/**
*@fn char* getNameMonster(const Monster * monster);
*@brief getter of the attributs name of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The name of the monster.
*/
char* getNameMonster(const Monster * monster);

/**
*@fn void setNameMonster(Monster * monster, const char* name);
*@brief The setter of the atributs name of a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]name : the new name to set.
return none
*/
void setNameMonster(Monster * monster, const char* name);

/**
*@fn int getLifePointsMonster(const Monster * monster);
*@brief getter of the attributs life points of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The life points of the monster.
*/
int getLifePointsMonster(const Monster * monster);

/**
*@fn void setLifePointsMonster(Monster * monster, int lifePoints);
*@brief The setter of the atributs life point of a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]lifePoints : the new life points to set.
return none
*/
void setLifePointsMonster(Monster * monster, int lifePoints);

/**
*@fn int getStrengthMonster(const Monster * monster);
*@brief getter of the attributs strength of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The stenght of the monster.
*/
int getStrengthMonster(const Monster * monster);

/**
*@fn void setStrengthMonster(Monster * monster, int strength);
*@brief The setter of the atributs strength of a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]strength : the new life stength to set.
return none
*/
void setStrengthMonster(Monster * monster, int strength);

/**
*@fn int getIntelligenceMonster(const Monster * monster);
*@brief getter of the attributs intelligence of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The intelligence of the monster.
*/
int getIntelligenceMonster(const Monster * monster);


/**
*@fn void setIntelligenceMosnter(Monster * monster, int intelligence);
*@brief The setter of the atributs intelligence of a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]intelligence : the new intelligence to set.
return none
*/
void setIntelligenceMosnter(Monster * monster, int intelligence);

/**
*@fn int getStrengthResMonster(const Monster * monster);
*@brief getter of the attributs strength resistance of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The strength resistance of the monster.
*/
int getStrengthResMonster(const Monster * monster);

/**
*@fn void setStrengthResMonster(Monster * monster, int strengthRes);
*@brief The setter of the atributs strength resistance of a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]strengthRes : the new strength resistance to set.
return none
*/
void setStrengthResMonster(Monster * monster, int strengthRes);

/**
*@fn int getIntellResMonster(const Monster * monster);
*@brief getter of the attributs intelligence resistance of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The intelligence resistance of the monster.
*/
int getIntellResMonster(const Monster * monster);

/**
*@fn void setIntellResMonster(Monster * monster, int intellRes);
*@brief The setter of the atributs intelligence resistance of a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]intellRes : the new intelligence resistance to set.
return none
*/
void setIntellResMonster(Monster * monster, int intellRes);

/**
*@fn SpellBar* getSpellBarMonster(const Monster * monster);
*@brief getter of the attributs spellBar of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The spell bar of the monster.
*/
SpellBar* getSpellBarMonster(const Monster * monster);

/**
*@fn void setSpellBarMonster(Monster * monster, SpellBar* spellBar);
*@brief The setter of the atributs spell bar a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]spellBar : the new spell bar to set.
return none
*/
void setSpellBarMonster(Monster * monster, SpellBar* spellBar);

/**
*@fn Weapon* getWeaponMonster(const Monster * monster);
*@brief getter of the attributs weapon of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The weapon of the monster.
*/
Weapon* getWeaponMonster(const Monster * monster);

/**
*@fn void setWeaponMonster(Monster * monster, Weapon * weapon);
*@brief The setter of the atributs weapon a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]spellBar : the new weapon to set.
return none
*/
void setWeaponMonster(Monster * monster, Weapon * weapon);

/**
*@fn Position* getPositionMonster(const Monster * monster);
*@brief getter of the attributs position of a monster.
*@param[in,out]monster : pointer to monster. (is a const)
*@return : The position of the monster.
*/
Position* getPositionMonster(const Monster * monster);

/**
*@fn void setPositionMonster(Monster * monster, int x, int y);
*@brief The setter of the atributs position a monster.
*@param[in,out]monster : pointer to monster.
*@param[in,out]x : the new coordonate x to set.
*@param[in,out]y : the new coordonate y to set.
return none
*/
void setPositionMonster(Monster * monster, int x, int y);


/**
 * @brief      Get the id of the monster.
 *
 * @param[in]  monster  pointer to Monster
 *
 * @return     the id of the monster.
 */
int getIdMonster(const Monster* monster);

/**
 * @brief      Set the id of the monster.
 *
 * @param[in,out]     monster  pointer to Monster.
 * @param[in]  id       the id to set.
 */
void setIdMonster(Monster* monster, const int id);



/**
*@fn void monsterTest();
*@brief Unit testing of Monster.
*@param[in,out]none
*@return none
*/
void monsterTest();

/**
 * @brief      Load the atributs of a Monster in a file.
 *
 * @param[in,out]     fileName  The name of the file to open.
 *
 * @return     A monster initialized with the values in the file.
 */
Monster* loadMonsterFromFile(char* fileName);

#endif

