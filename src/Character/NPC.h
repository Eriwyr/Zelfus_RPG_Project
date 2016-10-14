#ifndef NPC_H
#define NPC_H

#include "Quest.h"
#include "str.h"
#include "OS.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX


/**
@struct NPC
* @brief Define the atributs of a Non Player Character (NPC)
*/

typedef struct{
	int id; /**< The id of the NPC, necessary to identify a npc */
	char * name; /**< The name of the NPC. */
	char * dialog; /**< The dialogue of the NPC*/
	Quest * quest; /**< Link to quest */
	int isAccepted;/**< Boolean to see wheter the quest is accepted or not*/
	Position *pos;/**<The position of the NPC in order to locate it. */
	int hasRewarded;/**<Boolean to see if the npc has rewarded the player */
	int roomId;
}NPC;

/**
 *@fn void npcInit(NPC * npc, char* name, char* dialog, int id);
 * @brief      Initialisation of a non player character *
 * @param[in,out]     npc      a pointer to non player character
 * @param[in,out]     name    a pointer to the name of the npc
 * @param[in,out]     dialog  a pointer to the dialog's npc
 * @return 		none
 */
void npcInit(NPC * npc, char* name, char* dialog, int id);

/**
 * @fn 			void npcFree(NPC* npc);

 * @brief     	Free a npc
 *
 * @param[in,out]     npc   pointer to npc
 */
void npcFree(NPC* npc);

/**
 * @fn 			void npcCreate(char* name, char* dialog, int id);
 * @brief 		Create a npc
 * @param[in,out]     name     Pointer to the name of npc
 * @param[in,out]     dialog  Pointer to the name of npc
 * @return     a pointer to npc
 */
NPC* npcCreate(char* name, char* dialog, int id);

/**
 * @fn 			void npcDestroy(NPC** npc);
 * @brief      	Delete a npc
 * @param[in,out]      npc double pointer to a npc   
 */
void npcDestroy(NPC** npc);

/**
 * @fn 			char* getNameNpc(const NPC* npc);

 * @brief      get the name of a npc
 *
 * @param[in]  npc   pointer to a npc
 *
 * @return     		pointer to the name of the npc
 */
char* getNameNpc(const NPC* npc);

/**
 * @fn 			char* getDialogNpc(const NPC* npc);
 * @brief      	get the dialog who says the npc
 *
 * @param[in]  npc   pointer to npc
 *
 * @return     	a pointer to the dialogue who says the npc
 */
char* getDialogNpc(const NPC* npc);

/**
 * @brief      Get the quest of the npc.
 *
 * @param[in]  npc   the non player character's quest to get
 *
 * @return     the quest of npc.
 */
Quest* getQuestNpc(const NPC* npc);

/**
 *@ fn npcTest();
 * @brief      unit testing of npc
 */
void npcTest();

/**
 * @brief      Set the boolean isAccepted of a npc.
 *
 * @param[in,out]     npc         pointer to npc
 * @param[in]  isAccepted  int valued 1 or 0 to say if the player accepted the quest or not
 */
void setAcceptedNpc(NPC* npc, const int isAccepted);

/**
 * @brief      Determine if the quest is accepted or not npc.
 *
 * @param[in]  npc   pointer to NPC.
 *
 * @return     boolean to check if the quest is accepted or not.
 */
int isAcceptedNpc(const NPC* npc);

/**
 * @brief      Set the dialog of the npc.
 *
 * @param[in,out]     npc     pointer to NPC.
 * @param[in,out]     dialog  the new dialogue to set.
 */
void setDialogNpc(NPC* npc, char* dialog);

/**
 * @brief      Sets the identifier of the npc.
 *
 * @param[in,out]     npc   Pointer to NPC
 * @param[in]  id    The value to set.
 */
void setIdNpc(NPC* npc, int id);

/**
 * @brief      Gets the identifier f the npc.
 *
 * @param[in]  npc   The npc
 *
 * @return     The identifier of the npc.
 */
int getIdNpc(const NPC* npc); //same



/**
 * @brief      set the quest of the npc
 *
 * @param[in,out]      npc    pointer to npc
 * @param[in,out]      quest  The new quest to set.
 */
void setQuestNpc(NPC * npc, Quest * quest);

/**
 * @brief      get the Position of the Npc.
 *
 * @param[in]  npc   Pointer to NPC.
 *
 * @return     The position of the npc.
 */
Position* getPositionNpc(const NPC* npc);

/**
 * @brief      Set the position of the Npc.
 *
 * @param[in,out]     npc   Pointer to NPC.
 * @param[in]  x     The new x coordonate to set.
 * @param[in]  y     The new y coordonate to set.
 */
Position* getPositionNpc(const NPC* npc);

/**
 * @brief      Sets the position of the npc.
 *
 * @param[in,out]     npc   The npc
 * @param[in]  x     The x coordonate to set.
 * @param[in]  y     The y coordonate to set.
 */
void setPositionNpc(NPC* npc, int x, int y);

/**
 * @brief      Load the atributs of a NPC in a file.
 *
 * @param[in,out]     fileName  The name of the file to open.
 * @warning    The file must exist.
 *
 * @return     A NPC initialized with the values of the file.
 */
NPC* loadNPCFromFile(char* fileName);

/**
 * @brief      Determine if the npc has rewarded the player ( to reward him only once ) .
 *
 * @param[in]  npc   Pointer to NPC.
 *
 * @return     True if npc has rewarded, False otherwise.
 */
int hasRewardedNpc(const NPC* npc);

/**
 * @brief      Set the attributs hasRewarded
 *
 * @param[in,out]     npc          Pointer to NPC.
 * @param[in]  hasRewarded  The new value of hasRewarded.
 */
void setRewardedNpc(NPC* npc, const int hasRewarded);

/**
 * @brief      Save the attributs of a NPC in a file
 *
 * @param[in,out]     npc       The NPC to save.
 * @param[in,out]     fileName  the name of the file to open.
 */
void saveNPCOnFile(NPC * npc, char* fileName);

int getRoomIdNpc(const NPC* npc);

#endif