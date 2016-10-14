#ifndef QUESTDIARY_H
#define QUESTDIARY_H

#include "Quest.h"
#include "OS.h"
#include "str.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX
	
/**
*@file QuestDiary.h
*@brief A quest diary contain an array of quests.
 Contains some functions (add/remove quest from diary) as well.
*@author Mathieu Regnard

*/


/**
*@struct QuestDiary
*@brief 	Declaration of the atributs of a quest diary
*/
typedef struct {
		Quest ** quests; /**< Array of link to Quest.*/
		int nbQuests; /**< The number of quests currently stored */
		int size; /**< The size of the QuestDiary. */
} QuestDiary;

/*prototypes of functions relative do the quest diary*/

/**
*@fn void diaryInit(QuestDiary * diary);
*@brief Initialize dynamically the array of quests
*@param[in,out]diary : pointer to QuestDiary.
*@return none
*/
void diaryInit(QuestDiary * diary);


/**
*@fn void diaryFree(QuestDiary * diary);
*@brief Free memory
*@param[in,out]diary : pointer to QuestDiary ( will be freed)
*@return none
*/
void diaryFree(QuestDiary * diary);

/**
*@fn QuestDiary *diaryCreate();
*@brief Initialize dynamycally a QuestDiary.
*@param[in,out]none
*@return QuestDiary* link to a QuestDiary
*/
QuestDiary *diaryCreate();

/**
*@fn void diaryDestroy(QuestDiary ** diary);
*@brief Free memory when DiaryQuest was initialized by diaryCreate().
*@param[in,out]diary : double pointer (allow to change the first pointer ( IN-OUT)).
*@return none
*/
void diaryDestroy(QuestDiary ** diary);


/**
*@fn void addQuest(QuestDiary * diary, Quest * newQuest);
*@brief Add a quest to the diary.
*@param[in,out]diary : pointer to QuestDiary ( will be affected).
*@param[in,out]newQuest : the Quest that will be added.
*@warning newQuest : Is a constant !
*@return none
*/
void addQuest(QuestDiary * diary, Quest * newQuest);

/**
*@fn void deleteQuest(QuestDiary * diary, int i);
*@brief delete the quest of index i. 
*@param[in,out]diary : pointer to QuestDiary ( will be affected).
*@param[in,out]index : index of the quest to delete. 
*@warning : First element is index 1.
*/
void deleteQuest(QuestDiary * diary, int index);


/**
*@fn int getNbQuestDiary(const QuestDiary * diary);
*@brief Getter of nbQuests;
*@param[in,out]diary : pointer to QuestDiary.
*@warning diary : Is a constant ! 
*@return nbQuest ( int )
*/
int getNbQuestDiary(const QuestDiary * diary);

/**
*@fn void diaryTest();
*@brief unit testing of QuestDiary
*@param[in,out]none
*@return none
*/
void diaryTest();

/**
 * @fn Quest* getQuestDiary(const QuestDiary* diary);
 *
 * @brief      Return the array of quests
 *
 * @param[in]  diary  pointer to QuestDiary.
 *
 * @return     the array of quests.
 */
Quest** getQuestDiary(const QuestDiary* diary);

/**
 * @fn Quest* getQuestIDiary(const QuestDiary* diary, int i);
 *
 * @brief      return only one quest.
 *
 * @param[in]  diary  : pointer to QuestDiary.
 * @param[in,out]  i   : the index.
 *
 * @return     the ieme minus 1 value ( getQuestIDiary(diary, 1) will return the quest 0 in the array).
 */
Quest* getQuestIDiary(const QuestDiary* diary, int i);

/**
 * @brief      Return the index of the element haveing id for an id.
 *
 * @param[in]  diary  pointer to QuestDiary.
 * @param[in]  id     the id to search
 *
 * @return     the index of the element having the id passed in parameter for an id.
 */
int getIndexById(const QuestDiary * diary, int id);

/**
 * @brief      Load the atributs of a QuestDiary from a file
 *
 * @param[in,out]     fileName  The name of the file to open
 * @warning    The file must exist.
 *
 * @return   a QuestDiary initialized with the values in the file.
 */
QuestDiary* loadQuestDiaryFromFile(char* fileName);


/**
 * @brief      Get the position of a given quest in the diary.
 *
 * @param[in]  diary  Pointer to QuestDiary.
 * @param[in,out]     quest  The quest from which we'll return the index
 *
 * @return     the index of the quest.
 */
int getIdFromQuest(const QuestDiary * diary, Quest * quest);

/**
 * @brief      Save the atributs of a QuestDiary in a file.
 *
 * @param[in,out]     diary     The diary to save.
 * @param[in,out]     fileName  The name of the file to open.
 */
void saveQuestDiaryOnFile(QuestDiary* diary, char* fileName);
#endif