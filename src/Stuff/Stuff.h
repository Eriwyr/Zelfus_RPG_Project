#ifndef STUFF_H
#define STUFF_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "OS.h"
#include "str.h"

#ifndef CHAR_SIZE_MAX
#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX


/**
*@struct Stuff
*@brief define the attributs of a stuff.
*/
typedef struct {
    char *name; /**< The name of the Stuff. */
    int resistancestrength; /**< The resistance to strength of the Stuff. */
    int resistanceIntelligence; /**< The resistance to intell of the Stuff. */
    int bonusWisdom; /**< The bonus of wisdom of the Stuff. */
    int id; /**< The id of the Stuff. */
}Stuff;
/**
*@fn void stuffInit(Stuff* newStuff, const char *newName, int newResistancestrength, int newResistanceIntelligence, int newBonusWisdom, int id);
*@param[in,out] newStuff
*@param[in,out]in newName
*@param[in,out]in newResistancestrength
*@param[in,out]in newResistanceIntelligence
*@param[in,out]in newBonusWisdom
*@brief intialisation of a stuff
*@return none;
*/
void stuffInit(Stuff* newStuff, const char *newName, int newResistancestrength, int newResistanceIntelligence, int newBonusWisdom, int id);

/**
*@fn void stuffFree(Stuff* stuff);
*@param[in,out]
*@brief free a stuff
*@return none
*/
void stuffFree(Stuff* stuff);

/**
*@fn Stuff *stuffCreate(const char *newName, int newResistancestrength, int newResistanceIntelligence, int newBonusWisdom, int id);
*@param[in,out]in newName
*@param[in,out]in newResistancestrength
*@param[in,out]in newResistanceIntelligence
*@param[in,out]in newBonusWisdom
*@brief create a stuff
*@return Stuff
*/
Stuff *stuffCreate(const char *newName, int newResistancestrength, int newResistanceIntelligence, int newBonusWisdom, int id);

/**
*@fn void stuffDestroy(Stuff ** stuff);
*@brief free memory when allocated with stuffCreate.
*@param[in,out] stuff : double pointer to stuff.

*/
void stuffDestroy(Stuff ** stuff);


/**
*@fn int getResistancestrengthStuff(const Stuff* stuff);
*@brief getter of the atribut resistanceStrength.
*@param[in,out][in-out] stuff: pointer to stuff.
*@warning stuff : Is a constant !
*@return the resistance to the strength of stuff.
*/
int getResistancestrengthStuff(const Stuff* stuff);

/**
*@fn int getResistanceIntelligenceStuff(const Stuff* stuff);
*@brief getter of the atribut resistanceIntelligence.
*@param[in,out][in-out] stuff: pointer to stuff.
*@warning stuff : Is a constant !
*@return the ressistance to the intelligence of stuff.
*/
int getResistanceIntelligenceStuff(const Stuff* stuff);

/**
*@fn char* getNameStuff(const Stuff* stuff);
*@brief getter of the atribut name.
*@param[in,out][in-out] stuff: pointer to stuff.
*@warning stuff : Is a constant !
*@return the name of stuff.
*/
char* getNameStuff(const Stuff* stuff);

/**
*@fn int getBonusWisdomStuff(const Stuff* stuff);
*@brief getter of the atribut bonusWisdom.
*@param[in,out][in-out] stuff: pointer to stuff.
*@warning stuff : Is a constant !
*@return the stuff's bonus of wisdom.
*/
int getBonusWisdomStuff(const Stuff* stuff);


/**
 * @brief      get the id of the Stuff.
 *
 * @param[in]  stuff  Pointer to Stuff.
 *
 * @return     the id of the stuff.
 */
int getIdStuff(const Stuff* stuff);

/**
 * @brief      Set the id of the stuff.
 *
 * @param[in,out]     stuff  Pointer to Stuff.
 * @param[in]  id     the new id to set.
 */
void setIdStuff(Stuff* stuff, const int id);

/**
 * @brief      Load the atributs of a stuff from a file
 *
 * @param[in,out]     fileName  The name of the file to open
 * @warning     the file must exist.
 *
 * @return    A stuff initialized with the values in the file
 */
Stuff* loadStuffFromFile(char* fileName);

/**
*@fn void stuffTest();
*@bief Unit testing of the module Stuff.
*@param[in,out]none
*@return none
*/
void stuffTest();




#endif