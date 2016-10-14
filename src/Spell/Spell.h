#ifndef SPELL_H
#define SPELL_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "OS.h"
#include "str.h"
#include "file.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
*@struct Spell
*@brief Define the attributs of a spell
*/
typedef struct {
	int id; /**< The id of the Spell. */
	char * name; /**< The name of the Spell. */
	int damage; /**< The damage of the Spell. */
	int range; /**< The range of the Spell. */

}Spell;

/**
*@fn void spellInit(Spell* pSpell, int spellId, const char * spellName, int spellDamage, int range);
*@brief Create a spell
*@param[in,out] pSpell
*@param[in,out]in spellId
*@param[in,out]in spellName
*@param[in,out]in spellDamage
*@return none
*/
void spellInit(Spell* pSpell, int spellId, const char * spellName, int spellDamage, int range);

/**
*@fn void spellFree(Spell * spell);
*@brief Free memory
*@param[in,out][IN-OUT] spell : the spell that'll be freed
*@return none
*/
void spellFree(Spell * spell);

/**
*@fn Spell* spellCreate(int spellId, const char * spellName, int spellDamage, int range);
*@brief Initialyze a spell in the Heap.
*@param[in,out]spellId : the id set.
*@param[in,out]spellName : the name set.
*@param[in,out]spellDamage : the dammage set.
*@return the spell creater. 
*/
Spell* spellCreate(int spellId, const char * spellName, int spellDamage, int range);

/**
*@fn void spellDestroy(Spell** spell);
*@brief Free memory when a spell is created by spellCreate().
*@param[in,out]spell : double pointer to Spell ( allow to modify a pointer thus to free it).
*@return none
*/
void spellDestroy(Spell** spell);

/**
*@fn int getIdSpell(const Spell* pSpell);
*@brief get id attribut of a spell
*@param[in,out]in pSpell
*@return id of the spell
*/
int getIdSpell(const Spell* pSpell);

/**
*@fn int getNameSpell(const Spell* pSpell);
*@brief get name attribut of a spell
*@param[in,out]in pSpell
*@return name of the spell
*/
char *getNameSpell(const Spell* pSpell);

/**
*@fn int getDamageSpell(const Spell* pSpell);
*@brief get damage attribut of a spell
*@param[in,out]in pSpell
*@return damage of the spell
*/
int getDamageSpell(const Spell* pSpell);

/**
*@fn void spellTest();
*@brief unit testing of functions from spell.c
*@return none
*/
void spellTest();

/**
 * @brief      get the range of a Spell.
 *
 * @param[in]  pSpell  Pointer to Spell.
 *
 * @return     The range of the spell
 */
int getRangeSpell(const Spell* pSpell);

/**
 * @brief      set the range of a Spell.
 *
 * @param[in,out]     pSpell   Pointer to Spell.
 * @param[in]  newRange  The new range to set.
 */
void setRangeSpell(Spell* pSpell, const int newRange);

/**
 * @brief      Load the atributs of a Spell from a file.
 *
 * @param[in,out]     fileName  The name of the file to open.
 *
 * @return     A spell initialised with the values in the file.
 */
Spell* loadSpellFromFile(char* fileName);

#endif