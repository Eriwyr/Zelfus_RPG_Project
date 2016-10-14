#ifndef OBJECTSET_H
#define OBJECTSET_H

#include "QuestObject.h"

/**
 * @struct ObjectSet
 * @brief Contain a dynamic array of QuestObject
 */
typedef struct {
	QuestObject ** objects; /**< Array of link to QuestObject*/
	int nbObj; /**< The number of Object currently stored */
	int size; /**< The size of the array */
} ObjectSet;

/**
*@fn void objsetInit(ObjectSet * objset, int nbObj);
*@brief Initialize dynamically the array of quests
*@param[in,out]objset : pointer to ObjectSet.
*@return none
*/
void objsetInit(ObjectSet * objset, int nbObj);


/**
*@fn void objsetFree(ObjectSet * objset);
*@brief Free memory
*@param[in,out]objset : pointer to ObjectSet ( will be freed)
*@return none
*/
void objsetFree(ObjectSet * objset);

/**
*@fn ObjectSet *objsetCreate(int nbObj);
*@brief Initialize dynamycally a ObjectSet.
*@param[in,out]none
*@return ObjectSet* link to a ObjectSet
*/
ObjectSet *objsetCreate(int nbObj);

/**
*@fn void objsetDestroy(ObjectSet ** objset);
*@brief Free memory when ObjectSet was initialized by objsetCreate().
*@param[in,out]objset : double pointer (allow to change the first pointer thus to free it).
*@return none
*/
void objsetDestroy(ObjectSet ** objset);


/**
*@fn void addQuestObject(ObjectSet * objset, QuestObject * newObject);
*@brief Add a quest to the objset.
*@param[in,out]objset : pointer to ObjectSet ( will be affected).
*@param[in,out]newQuestObject : the QuestObject that will be added.
*@warning newQuestObject : Is a constant !
*@return none
*/
void addQuestObject(ObjectSet * objset, QuestObject * newObject);

/**
*@fn void removeQuestObject(ObjectSet * objset, int i);
*@brief delete the quest of index i. 
*@param[in,out]objset : pointer to ObjectSet ( will be affected).
*@param[in,out]index : index of the quest to delete. 
*@warning : First element is of index 1.
*/
void removeQuestObject(ObjectSet * objset, int ind);


/**
*@fn int getNbObjSet(const ObjectSet * objset);
*@brief Getter of nbQuestObjects;
*@param[in,out]objset : pointer to ObjectSet.
*@warning objset : Is a constant ! 
*@return The number of monsters in a objset ( int )
*/
int getNbObjSet(const ObjectSet * objset);

/**
*@fn QuestObject** getObjectObjset(const ObjectSet * objset);
*@brief getter of the array of quest objects.
*@param[in,out]objset : pointer to objset.
*@warning objset : objset is a constant.
*@return the array of quest objects.
*/
QuestObject** getObjectObjset(const ObjectSet * objset);

/**
 * @brief      get the Ith element of the Objset.
 *
 * @param[in]  objset  Pointer to ObjectSet
 * @param[in]  i       the index of the element to get
 *
 * @return     The Ith object of objset
 */
QuestObject* getObjectIObjset(const ObjectSet * objset, int i);

/**
 * @brief      Return the position of an object in the Objset
 *
 * @param[in,out]     objset  Pointer to ObjectSet
 * @param[in,out]     object  The object from which we get the index.
 *
 * @return    The index of the object. 
 */
int getIdFromObject(ObjectSet * objset, QuestObject * object);

/**
*@fn void objsetTest();
*@brief unit testing of ObjectSet
*@param[in,out]none
*@return none
*/
void objsetTest();

#endif