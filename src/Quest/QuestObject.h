#ifndef QUESTOBJECT_H
#define QUESTOBJECT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#	include <assert.h>
#include "Position.h"

/**
*@struct QuestObject
*@brief define the object of quest ( to be collected)
*/
typedef struct {
	int id; /**< The id of the QuestObject */
	char* name; /**< The name of the QuestObject */
	char* type; /**< The type of the QuestObject */
	Position * pos; /**< The position of the QuestObject (link to Position )*/
	int roomId; /**< The roomId of the QuestObject */
} QuestObject;

/**
*@fn void questObjectInit(QuestObject * object, int idObject, char * name, char * type, int x, int y, int roomId);
*@brief Initialize a questObject.
*@param[in,out]object : the object to initialize.
*@param[in,out]idObject : the id to set.
*@param[in,out]name: the name to set.
*@param[in,out]type: the type to set.
*@return none
*/
void questObjectInit(QuestObject * object, int id, char * name, char * type, int x, int y, int roomId);

/**
*@fn void questObjectFree(QuestObject * object);
*@brief Free memory.
*@param[in,out]object : pointer to object ( Will be freed).
*@return none
*/
void questObjectFree(QuestObject * object);

/**
*@fn QuestObject* questObjectCreate(int id, char * name, char * type, int x, int y, int roomId);
*@brief initalize a QuestObject in the Heap.
*@param[in,out]idObject : the id to set.
*@param[in,out]name: the name to set.
*@param[in,out]type: the type to set
*@return The questObject created.
*/
QuestObject* questObjectCreate(int id, char * name, char * type, int x, int y, int roomId);

/**
*@fn void questObjectDestroy(QuestObject ** object);
*@brief Free memory when questObject alocated with questObjectCreate().
*@param[in,out]object : double pointer to object ( allow to modify the pointer thus to free it).
*@return none
*/
void questObjectDestroy(QuestObject ** object);


/**
*@fn int getIdObject(const QuestObject * object);
*@brief getter of the attributs id of an object.
*@param[in,out]object : pointer to object
*@warning object is a constant.
*@return the id of object.
*/
int getIdObject(const QuestObject * object);

/**
*@fn char* getNameObject(const QuestObject * object);
*@brief getter of the attributs name of an object.
*@param[in,out]object : pointer to object
*@warning object is a constant.
*@return the name of object.
*/
char* getNameObject(const QuestObject * object);

/**
*@fn char* getTypeObject(const QuestObject * object)
*@brief getter of the attributs type of an object.
*@param[in,out]object : pointer to object
*@warning object is a constant.
*@return the type of object.
*/
char* getTypeObject(const QuestObject * object);

/**
 * @brief      Set the id of the object.
 *
 * @param[in,out]     object  pointer to QuestObject.
 * @param[in]  id      the new id to set.
 */
void setIdObject(QuestObject *object, const int id);

/**
*@fn void questObjectTest();
*@brief Unit testing of the functions of QuestObject.
*@return none
*/
void questObjectTest();

/**
 * @brief      get the roomId of an Object
 *
 * @param[in]  obj   Pointer to QuestObject.
 *
 * @return     the roomId of obj.
 */
int getRoomIdObject(const QuestObject* obj);

/**
 * @brief     Set the roomId of an Object.
 *
 * @param[in,out]     obj     Pointer to QuestObject.
 * @param[in]  roomId  The new roomID to set.
 */
void setRoomIdObject(QuestObject* obj, const int roomId);

/**
 * @brief      get the Positions of an object.
 *
 * @param[in]  obj   Pointer to QuestObject.
 *
 * @return    the positions of obj.
 */
Position* getPositionObject(const QuestObject* obj);

/**
 * @brief      Set the position of an object.
 *
 * @param[in,out]     obj   Pointer to Object
 * @param[in]  x     The new x coordonate to set.
 * @param[in]  y     The new y coordonate to set.
 */
void setPositionObject(QuestObject* obj, int x, int y);

#endif