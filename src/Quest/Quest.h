#ifndef QUEST_H
#define QUEST_H


#include "Objective.h"
#include "Reward.h"
#include "QuestObject.h"
#include "str.h"
#include "OS.h"

#ifndef CHAR_SIZE_MAX
#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX


/**
*@struct Quest
*@brief Define the atributs of a quest.
*/
typedef struct {
	
	Objective * objective; /**<link on Objective*/
	Reward * reward; /**<link on Reward*/
	int id; /**< The id of the Quest. */
	int isAccomplished; /**< Boolean to know wether the quest is finished or not*/
	char* name; /**< The name of the quest. */

} Quest;

/*definitions of functions related to Quest*/

/**
*@fn void questInit(Quest * quest, int id, const char* name, int nbMstr, int nbObj);
*@brief create a quest with some parameters.
*@param[in,out]quest : quest to create.
*@param[in,out]id : Index of the Quest.
*@param[in,out]name : name of the Quest.
*@return none.
*/
void questInit(Quest * quest, int id, const char* name, int nbMstr, int nbObj);

/**
*@fn void questFree(Quest * quest);
*@brief free memory.
*@param[in,out]quest : pointer to quest.
*@return none.
*/
void questFree(Quest * quest);

/**
 * @fn  Quest* questCreate(int id, const char* name, int nbMstr, int nbObj);
 * @brief     Create a Quest in the Heap.
 *
 * @param[in,out]     quest : pointer to quest.
 * @param[in]  id : the id of the quest.
 * @param[in]     name : the name of the quest.
 * @param[in]  nbMstr  : the number of monsters in the objective.
 * @param[in]  nbObj  : the number of the objects in the objetive.
 * @return none
 */
Quest* questCreate(int id, const char* name, int nbMstr, int nbObj);


/**
 * @brief      Free memory when initialized with questCreate.
 *
 * @param[in,out]  quest : double pointer to quest ( qllow to modify its value).
 */
void questDestroy(Quest ** quest);

/**
*@fn void setObjectiveQ(Quest * quest, Objective * newObjective);
*@brief Allow to modify/set the objectif of the Quest.
*@param[in,out]quest : pointer to quest ( will be modified).
*@param[in,out]newObjective : the new objective that will be set.
*@warning newObjective : Is a constant !
*@return none
*/
void setObjectiveQ(Quest * quest, Objective * newObjective);

/**
*@fn void setRewardQ(Quest * quest, Reward * newReward);
*@brief Allow to modify/set the reward of the Quest.
*@param[in,out]quest : pointer to quest ( will be modified).
*@param[in,out]newReward : the new objective that will be set.
*@warning newReward : Is a constant !
*@return none
*/
void setRewardQ(Quest * quest, Reward * newReward);

/**
*@fn getObjectiveQ(const Quest * quest);
*@brief return the objective of a quest.
*@param[in,out]quest : pointer to quest.
*@warning quest : Is a constant ! 
*@return The objective of the quest.
*/
Objective * getObjectiveQ(const Quest * quest);

/**
*@fn Reward * getRewardQ(const Quest * quest);
*@brief return the reward of a quest.
*@param[in,out]quest : pointer to quest.
*@warning quest : Is a constant ! 
*@return The objective of the quest.
*/
Reward * getRewardQ(const Quest * quest);

/**
*@fn int getIdQ(const Quest * quest);
*@brief return the idex of the quest.
*@param[in,out]quest : pointer to quest.
*@warning Is a constant !
*@return the id of the quest.
*/
int getIdQ(const Quest * quest);


/**
*@fn int isAccomplished(const Quest * quest);
*@brief tell if the quest is finished or not
*@param[in,out]quest : pointer to Quest.
*@warning quest : Is a constant !
*@return the value of the boolean isAcomplished.
*/
int isAccomplished(const Quest * quest);

/**
*@fn void questFinish(Quest * quest);
*@brief Allow to finish a quest ( set isAcoomplished to 1).
*@param[in,out]quest : pointer to quest
*@warning No turning back !
*@return none
*/
void questFinish(Quest * quest);

/**
*@fn char* getNameQ(const Quest * quest);
*@brief Return the name of the quest.
*@param[in,out]quest : pointer to quest.
*@warning quest : Is a constant !
*@return Name of the quest.
*/
char* getNameQ(const Quest * quest);


/**
*@fn void setNameQ(Quest * quest, const char* newName);
*@brief allow to change the name of a quest.
*@param[in,out]quest : pointer to quest.
*@param[in,out]newName : the new name that will be set.
*@warning newName : Is a constant !
*@return none
*/
void setNameQ(Quest * quest, const char* newName);

/**
*@fn void questTest();
*@brief unit tesing
*@return none
*/
void questTest();

/**
 * @brief      Load the attributs of a Quest from a file.
 *
 * @param[in,out]     fileName  The name of the file to open.
 * @warning    The file must exist.
 *
 * @return     The Quest initialized with the value of the Quest.
 */
Quest* loadQuestFromFile(char* fileName);

/**
 * @brief      check if a quest is finished.
 *
 * @param[in,out]     quest  Pointer to Quest.
 *
 * @return     true if quest is finished, fals otherwise.
 */
int checkIsFinishQuest(Quest * quest);

/**
 * @brief      save the atributs of the Quest on a file
 *
 * @param[in,out]     quest     The Quest to save.
 * @param[in,out]     fileName  The name of the file to open.
 */
void saveQuestOnFile(Quest * quest, char* fileName);

#endif