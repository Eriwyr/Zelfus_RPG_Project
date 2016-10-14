#ifndef BUFFERGAME_H
#define BUFFERGAME_H

#include "Buffer.h"
#include <stdarg.h>

typedef enum MovingElement {CHARACTER, MONSTER, SPELL, _NPC} MovingElement;

/**
 * @struct BufferGame
 * @brief Define the element of the BufferGame.
 */
typedef struct {
	Buffer *elmt; /**< link to Buffer to store the moving elements */
	Buffer *toGoX; /**< Link to Buffer to store the x coordonate of the position to go. */
	Buffer *toGoY; /**< Link to Buffer to store the y coordonate of the postition to go. */
	Buffer *index; /**< Link to Buffer to store the index of the moving element. */
	Buffer *action; /**< Link to Buffer to store the action that will be executed. */
	Buffer *hasBeenExecuted; /**< Link to Buffer to tell if a peculiar action has been executed or not. */
} BufferGame;

/**
 * @brief      Initialize a BufferGame
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 */
void bufferGameInit(BufferGame * buffer);

/**
 * @brief      Free memory
 *
 * @param[in,out]     buffer  The BufferGame to free.
 */
void bufferGameFree(BufferGame * buffer);

/**
 * @brief      Create a BufferGame in the Heap.
 *
 * @return     Return a BufferGame initialized.
 */
BufferGame* bufferGameCreate();

/**
 * @brief      Free memory when initialized with bufferGameCreate()
 *
 * @param[in,out]     buffer  Double pointer of BufferGame (allow to free the pointer of BufferGame).
 */
void bufferGameDestroy(BufferGame ** buffer);

/**
 * @brief      Wrapper of addEventToBuffer
 *
 * @param[in,out]     buffer     Pointer to BufferGame
 * @param[in]  elmt       The element that is moving
 * @param[in]  x          the x coordonate to go.
 * @param[in]  y          the y coordonate to go.
 * @param[in]  <...>  	  Optional parameters ( not every element need an index)
 */
void addEventToBufferGame(BufferGame* buffer, MovingElement elmt, int x, int y, ...);

/**
 * @brief      Wrapper of removeEventToBuffer
 *
 * @param[in,out]     buffer  Pointer to BufferGame
 * @param[in]  i       the index of the elements to remove.
 */
void removeEventFromBufferGame(BufferGame * buffer, int i);

/**
 * @brief      Wrapper of getNbEventBuffer.
 *
 * @param[in,out]     buffer  Pointer to BufferGame
 *
 * @return     The number of events in the buffer game.
 */
int getNbEventBufferGame(BufferGame * buffer);

/**
 * @brief      Wrapper of setCurrentIndexBuffer
 *
 * @param[in,out]     buffer        Pointer to BufferGame.
 * @param[in]  currentIndex  The new current index to set.
 */
void setCurrentIndexBufferGame(BufferGame* buffer, const int currentIndex);

/**
 * @brief      Wrapper of getCurrentIndexBuffer.
 *
 * @param[in,out]     buffer  Pointer to BufferGame
 *
 * @return     The current index of the buffer elmt.
 */
int getCurrentIndexBufferElmt(BufferGame* buffer);

/**
 * @brief      Wrapper of getCurrentIndexBuffer
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 *
 * @return     The current index of the buffer toGoX.
 */
int getCurrentIndexBufferX(BufferGame* buffer);

/**
 * @brief      Wrapper of getCurrentIndexBuffer
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 *
 * @return     The current index of the buffer toGoY.
 */
int getCurrentIndexBufferY(BufferGame* buffer);

/**
 * @brief      Get the position in the buffer of an element.
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 * @param[in]  elmt    The element to search the index.
 *
 * @return     The index of the element ( its position in the buffer).
 */
int getIFromElmtBufferGame(BufferGame * buffer, int elmt);

/**
 * @brief      Wrapper of getEventIBuffer
 *
 * @param[in]  buffer  Pointer to BufferGame
 * @param[in]  i       The index of the element to get.
 *
 * @return     The value in the buffer toGoX at the Ith position.
 */
int getXBufferGame(const BufferGame * buffer, int i);

/**
 * @brief      Wrapper of getEventIBuffer
 *
 * @param[in]  buffer  Pointer to BufferGame.
 * @param[in]  i       The index of the element to get.
 *
 * @return     The value in the buffer toGoY at the Ith position.
 */
int getYBufferGame(const BufferGame * buffer, int i);

/**
 * @brief      Wrapper of isEmptyBuffer.
 *
 * @param[in]  buffer  Pointer to BufferGame.
 *
 * @return     True if the buffer elmt is empty, False otherwise.
 */
int isEmptyBufferElmt(const BufferGame * buffer);

/**
 * @brief      Wrapper of getEventIBuffer
 *
 * @param[in]  buffer  Pointer to BufferGame.
 * @param[in]  i       The index of the element to get.
 *
 * @return     The value in the buffer elmt at the Ith position.
 */
int getEventIBufferGame(const BufferGame * buffer, int i);

/**
 * @brief      Wrapper of getEventIBuffer
 *
 * @param[in]  buffer  Pointer to BufferGame.
 * @param[in]  i       The index of the element to get.
 *
 * @return     The value in the buffer index at the Ith position.
 */
int getIndexIBufferGame(const BufferGame * buffer, int i);

/**
 * @brief      Remove all elements corresponding to elmt of the buffer.
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 * @param[in]  elmt    The type of elmt to remove in the buffer.
 */
void clearBufferGame(BufferGame * buffer, int elmt);

/**
 * @brief      Add a action to BufferGame.
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 * @param[in]  action  The action to add.
 */
void addActionToBufferGame(BufferGame * buffer, int action);

/**
 * @brief      Wrapper of getEventIBuffer
 *
 * @param[in]  buffer  Pointer to BufferGame.
 * @param[in]  i       the index of the event to get
 *
 * @return     Return the Ith element of the buffer action.
 */
int getActionIBufferGame(const BufferGame * buffer, int i);

/**
 * @brief      Remove all the events of the buffer action
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 */
void clearActionBufferGame(BufferGame * buffer);

/**
 * @brief      Clear the buffer of the spell
 *
 * @param[in,out]     buffer  pointer to BufferGame.
 */
void clearSpellBuffer(BufferGame * buffer);

/**
 * @brief      Counts the number of elements buffer.
 *
 * @param[in]  buffer  Pointer to Buffer.
 * @param[in]  elmt    The elmt to count for
 *
 * @return     Number of element buffer.
 */
int countElementBuffer(const BufferGame * buffer, int elmt);

/**
 * @brief      Wrapper of removeEventFromBuffer
 *
 * @param[in,out]     buffer  Pointer to BufferGame.
 * @param[in]  i       The index of the action to remove
 */
void removeActionFromBufferGame(BufferGame * buffer, int i);

/**
 * @brief      Determine if action has been executed.
 *
 * @param[in]  buffer  Pointer to BufferGame.
 * @param[in]  i       The index of the action to check.
 *
 * @return     True if the action has been excuted , False otherwise.
 */
int hasBeenExcutedBufferAction(const BufferGame * buffer, int i);

/**
 * @brief      Set the boolean hasBeenExecuted of the action.
 *
 * @param[in]  buffer  Pointer to BufferGame.
 * @param[in]  i       The inde of the action to which we set the value.
 * @param[in]  value   The new value to set.
 */
void setExecutedBufferAction(const BufferGame * buffer, int i, int value);

void changeFirstToGoBuffer(const BufferGame * buffer, int x, int y);
void clearCharacBuffer(BufferGame * buffer);
#endif