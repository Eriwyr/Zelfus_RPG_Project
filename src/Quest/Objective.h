#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "ObjectSet.h"
#include "Horde.h"


/**
* @struct Objective
* @brief Define an Objective
*/


typedef struct {
	int nbMstr;
	// Horde * horde; /**< Link to Horde*/
	ObjectSet * objects; /**< Link to ObjectSet */
} Objective;


/*functions collect() and kill() to update objectif*/

/**
*@fn void objectiveInit(Objective * obj, int nbMstr, int nbOjct);
*@brief Initialize an objective ( allocate memory )
*@param[in,out]obj : pointer to objective.
*@return none
*/
void objectiveInit(Objective * obj, int nbMstr, int nbOjct);


/**
*@fn Objective *objectiveCreate(int nbMstr, int nbOjct);
*@brief Create an Objective in the Heap.
*@param[in,out]nbMstr : the number of monster you'll have to kill.
*@param[in,out]nbOjct : the number of objects you'll have to collect.
*@return Objective : The objective created.
*/
Objective *objectiveCreate(int nbMstr, int nbOjct);


/**
*@fn void objectiveFree(Objective * obj);
*@brief Free memory of an objective.
*@param[in,out]obj : the objective to be freed.
*@return none
*/
void objectiveFree(Objective * obj);

/**
*@fn void objectiveDestroy(Objective ** obj);
*@brief Free the memory when an Objective is created by objectiveCreate.
*@param[in,out]obj : double pointer, allow to free obj.
*@return none.
*/
void objectiveDestroy(Objective ** obj);

int getNbMstrObjective(const Objective * obj);
void setNbMstrObjective(Objective * obj, int value);

/** 
@fn ObjectSet*getObjectsObjective(const Objective* obj);
@brief Get objects from an objective
@param[in,out]obj : pointer to objective
@return A set of objects
*/
ObjectSet* getObjectsObjective(const Objective* obj);

/**
@fn objectiveTest();
@brief unit testing of Objective
@param[in,out]none
@return none
void objectiveTest();
*/
void objectiveTest();
#endif