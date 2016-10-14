#ifndef BUFFER_H
#define BUFFER_H

#define MAX_BUFFER 10

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @struct Buffer 
 * @brief Define the atributs of a buffer
 */
typedef struct{

	int *soldier; /**< Array of int to store*/
	int currentIndex; /**< The current index traited */
	int nbEvent; /**< The nb of event currently contained */

}Buffer;


/**
 * @brief      Initialize the buffer
 *
 * @param[in,out]     buffer  The buffer to initialize
 */
void bufferInit(Buffer * buffer);

/**
 * @brief      Free the memory
 *
 * @param[in,out]     buffer  Pointer to buffer
 */
void bufferFree(Buffer * buffer);

/**
 * @brief      Create a buffer in the Heap.
 *
 * @return     Return a pointer to Buffer initialized
 */
Buffer* bufferCreate();

/**
 * @brief      Free memory when initialised with bufferCreate()
 *
 * @param[in,out]     buffer  Double pointer to buffer ( allow to access the adresses of the buffer, thus to free it).
 */
void bufferDestroy(Buffer ** buffer);

/**
 * @brief      Add a new event to the buffer
 *
 * @param[in,out]     buffer  Pointer to buffer.
 * @param[in]  event   The event you want to add.
 */
void addEventToBuffer(Buffer * buffer, int event);

/**
 * @brief      Get the Ith element of the buffer.
 *
 * @param[in,out]     buffer  Pointer to buffer.
 * @param[in]  i       The index of the tab.
 * @warning    i must be between 0 and MAX_BUFFER.
 *
 * @return     Event i buffer.
 */
int getEventIBuffer(Buffer * buffer, int i);

/**
 * @brief      Get the current index of the buffer.
 *
 * @param[in]  buffer  Pointer to buffer.
 *
 * @return     The current index of the buffer
 */
int getCurrentIndexBuffer(const Buffer* buffer);

/**
 * @brief      Set the current index of the buffer.
 *
 * @param[in,out]     buffer        Pointer to buffer.
 * @param[in]  currentIndex  The new currentIndex to set. ( must be between 0 and MAX_BUFFEr)
 */
void setCurrentIndexBuffer(Buffer* buffer, const int currentIndex);

/**
 * @brief      Get the number of events in the buffer.
 *
 * @param[in]  buffer  Pointer to buffer.
 *
 * @return     The number of events the buffer contains.
 */
int getNbEventBuffer(const Buffer* buffer);

/**
 * @brief      Shift every case of the buffer from i to the max ( which remove the Ith value)
 *
 * @param[in,out]     buffer  Pointer to buffer.
 * @param[in]  i       Index of the event to remove.
 */
void removeEventFromBuffer(Buffer * buffer, int i);

/**
 * @brief      Print every value of the buffer
 *
 * @param[in,out]     buffer  Pointer to buffer.
 */
void printBuffer(Buffer * buffer);

/**
 * @brief      Set the Ith element of the buffer.
 *
 * @param[in,out]     buffer  Pointer to buffer
 * @param[in]  i       the index of the element to set.
 * @param[in]  value   The value which will be set.
 */
void setElemntIBuffer(Buffer * buffer, int i, int value);

/**
 * @brief      Determine if the buffer is empty or not.
 *
 * @param[in]  buffer  Pointer to buffer.
 *
 * @return     True the buffer is empty, False otherwise.
 */
int isEmptyBuffer(const Buffer* buffer);

#endif // BUFFER_H
