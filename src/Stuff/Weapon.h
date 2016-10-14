#ifndef WEAPON_H
#define WEAPON_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "OS.h"
#include "str.h"
#include "file.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
 * @struct Weapon
 * @brief Define the attributs of a Weapon
 */
typedef struct {
    char * name; /**< The name of the Weapon */
    int damage; /**< The damage of the Weapon */
    int strength; /**< The strength of the Weapon. */
    int intelligence; /**< The intelligence of the Weapon. */
    int wisdom; /**< The wisdom of the Weapon. */
    int range; /**< The range of the Weapon. */
    int id; /**< The id of the Weapon. */
} Weapon;

/**
*@fn void weaponInit(Weapon * weapon, const char * name, int damage, int strength, int intelligence, int wisdom, int range, int id);
*@brief Initialize a weapon.
*@param[in,out][IN-OUT] weapon  : pointer to Weapon.
*@param[in,out][IN] name : name that'll be set.
*@param[in,out][IN] strength : strengh that'll be set.
*@param[in,out][IN] intelligence : intelligence that'll be set.
*@param[in,out][IN] wisdom : wisdom that'll be set.
*@return none
*/
void weaponInit(Weapon * weapon, const char * name, int damage, int strength, int intelligence, int wisdom, int range, int id);

/**
*@fn Weapon* weaponCreate(const char * name, int damage, int strength, int intelligence, int wisdom, int range, int id);
*@brief Initialize a weapon dynamically.
*@param[in,out][IN] name : name that'll be set.
*@param[in,out][IN] strength : strengh that'll be set.
*@param[in,out][IN] intelligence : intelligence that'll be set.
*@param[in,out][IN] wisdom : wisdom that'll be set.
*@return pointer to weapon.
*/
Weapon* weaponCreate(const char * name, int damage, int strength, int intelligence, int wisdom, int range, int id);

/**
*@fn void weaponFree(Weapon * weapon);
*@brief Free memory 
*@param[in,out][IN-OUT] weapon : pointer to Weapon ( will be freed)
*@return none
*/
void weaponFree(Weapon * weapon);

/**
*@fn void weaponDestroy(Weapon ** weapon);
*@brief Free memory when Weapon was initialized by weaponCreate().
*@param[in,out][IN] weapon  : double pointer (allow to change the first pointer thus to free it).
*@return none
*/
void weaponDestroy(Weapon ** weapon);


/**
*@fn char* getNameWeapon(const Weapon * weapon);
*@brief getter of the atribut name.
*@param[in,out][IN] weapon: pointer to Weapon.
*@warning weapon : Is a constant !
*@return the name of weapon.
*/
char* getNameWeapon(const Weapon * weapon);


/**
*@fn void setNameWeapon(Weapon * weapon, const char * name);
*@brief setter of the atribut name.
*@param[in,out][IN-OUT] weapon : pointer to weapon.
*@param[in,out][IN] name: the new name to set.
*@return none
*/
void setNameWeapon(Weapon * weapon, const char * name);

/**
*@fn int getDamageWeapon(const Weapon * weapon);
*@brief getter of the atribut damage.
*@param[in,out][IN] weapon: pointer to Weapon.
*@warning weapon : Is a constant !
*@return the damage of weapon.
*/
int getDamageWeapon(const Weapon * weapon);

/**
*@fn void setDamageWeapon(Weapon * weapon, int damage);
*@brief setter of the atribut damage.
*@param[in,out][IN-OUT] weapon : pointer to weapon.
*@param[in,out][IN] damage: the new damage to set.
*@return none
*/
void setDamageWeapon(Weapon * weapon, int damage);

/**
*@fn char* getStrengthWeapon(const Weapon * weapon);
*@brief getter of the atribut strength.
*@param[in,out][IN] weapon: pointer to Weapon.
*@warning weapon : Is a constant !
*@return the strength of weapon.
*/
int getStrengthWeapon(const Weapon * weapon);

/**
*@fn void setStrengthWeapon(Weapon * weapon, int strength);
*@brief setter of the atribut strength.
*@param[in,out][IN-OUT] weapon : pointer to weapon.
*@param[in,out][IN] strength: the new strength to set.
*@return none
*/
void setStrengthWeapon(Weapon * weapon, int strength);

/**
*@fn char* getIntelligenceWeapon(const Weapon * weapon);
*@brief getter of the atribut intelligence.
*@param[in,out][IN] weapon: pointer to Weapon.
*@warning weapon : Is a constant !
*@return the intelligence of weapon.
*/
int getIntelligenceWeapon(const Weapon * weapon);

/**
*@fn void setIntelligenceWeapon(Weapon * weapon, int intelligence);
*@brief setter of the atribut intelligence.
*@param[in,out][IN-OUT] weapon : pointer to weapon.
*@param[in,out][IN] intelligence: the new intelligence to set.
*@return none
*/
void setIntelligenceWeapon(Weapon * weapon, int intelligence);

/**
*@fn char* getWisdomWeapon(const Weapon * weapon);
*@brief getter of the atribut wisdom.
*@param[in,out][IN] weapon: pointer to Weapon.
*@warning weapon : Is a constant !
*@return the wisdom of weapon.
*/
int getWisdomWeapon(const Weapon * weapon);

/**
*@fn void setWisdomWeapon(Weapon * weapon, int wisdom);
*@brief setter of the atribut wisdom.
*@param[in,out][IN-OUT] weapon : pointer to weapon.
*@param[in,out][IN] wisdom: the new wisdom to set.
*@return none
*/
void setWisdomWeapon(Weapon * weapon, int wisdom);

/**
 * @brief      Get the range of the weapon.
 *
 * @param[in]  weapon  Pointer to Weapon.
 *
 * @return     the range of the weapon
 */
int getRangeWeapon(const Weapon* weapon);

/**
 * @brief      Set the range of the weapon.
 *
 * @param[in,out]     weapon  pointer to Weapon.
 * @param[in]  range   the new range to set.
 */
void setRangeWeapon(Weapon* weapon, const int range);

/**
 * @brief      Unit testing of Weapon.
 */
void weaponTest();

/**
 * @brief      Load the atributs of a Weapon from a file.
 *
 * @param[in,out]     fileName  the name of the file to open.
 * @warning    The file must exist !
 *
 * @return     A Weapon initialised with the values in the files.
 */
Weapon* loadWeaponFromFile(char* fileName);

/**
 * @brief      get the id of the weapon
 *
 * @param[in]  weapon  Pointer to Weapon
 *
 * @return     The id of weapon.
 */
int getIdWeapon(const Weapon* weapon);

/**
 * @brief      set the id of a weapon
 *
 * @param[in,out]     weapon  Pointer to Wepaon.
 * @param[in]  id      the new id to set.
 */
void setIdWeapon(Weapon* weapon, const int id);

#endif