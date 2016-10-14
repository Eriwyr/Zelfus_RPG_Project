#ifndef SPELLBAR_H
#define SPELLBAR_H


#include "Spell.h"
#include "OS.h"

/**
*@struct SpellBar
*@brief dynamic array of Spell
*/ 
typedef struct {
    
    Spell ** spells; /**<Array of link to Spell*/
    int nbSpell; /**<Slots used (5 slots by default)*/
}SpellBar;

/**
*@fn void spellBarInit(SpellBar * spellBar);
*@brief initialisation of spell bar
*@param[in,out] spellBar
*@return none
*/ 
void spellBarInit(SpellBar * spellBar);


/**
*@fn SpellBar * spellBarCreate();
*@brief Create Spell Bar in Heap memory.
*@param[in,out]none
*@return pointer to spellBar
*/
SpellBar * spellBarCreate();


/**
*@fn void addSpell(SpellBar* spellBar, Spell *newSpell);
*@brief add spell into SpellBar
*@param[in,out] spellBar
*@param[in,out]in newSpell
*@return none
*/
void addSpell(SpellBar* spellBar, Spell *newSpell);

/**
*@fn void spellBarFree(SpellBar * spellBar);
*@brief free memory alocated to the spell Bar 
*@param[in,out] spellBar
*@return none

*/
void spellBarFree(SpellBar * spellBar);


/**
*@fn void spellBarDestroy(SpellBar ** spellBar);
*@brief Free memory when initialized with spellCreate()
*@param[in,out]spellBar : pointer to Spell Bar 
*@return none
*/
void spellBarDestroy(SpellBar ** spellBar);


/**
*@fn void spellBarTest();
*@brief Unit testing of SpellBar.
*@param[in,out]none
*@return none
*/
int getNbSpell(SpellBar * spellBar);

void spellBarTest();

Spell* getSpell(const SpellBar* spellBar, int i);

SpellBar* loadSpellBarFromFile(char* fileName);

void saveSpellBarOnFile(SpellBar * spellBar, char* fileName);
#endif