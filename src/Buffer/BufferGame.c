#include "BufferGame.h"

void bufferGameInit(BufferGame * buffer){
	buffer->elmt = bufferCreate();
	buffer->toGoX = bufferCreate();
	buffer->toGoY = bufferCreate();
	buffer->index = bufferCreate();
	buffer->action = bufferCreate();
	buffer->hasBeenExecuted = bufferCreate();
}

void bufferGameFree(BufferGame * buffer){
	bufferDestroy(&buffer->elmt);
	bufferDestroy(&buffer->toGoX);
	bufferDestroy(&buffer->toGoY);
	bufferDestroy(&buffer->index);
	bufferDestroy(&buffer->action);
	bufferDestroy(&buffer->hasBeenExecuted);
}

BufferGame* bufferGameCreate(){
	BufferGame * buffer;
	buffer = malloc(sizeof(BufferGame));

	bufferGameInit(buffer);

	return buffer;
}

void bufferGameDestroy(BufferGame ** buffer){
	bufferGameFree(*buffer);
	free(*buffer);

	*buffer = NULL;
}

void addEventToBufferGame(BufferGame* buffer, MovingElement elmt, int x, int y, ...){
	addEventToBuffer(buffer->elmt, elmt);
	addEventToBuffer(buffer->toGoX, x);
	addEventToBuffer(buffer->toGoY, y);
	if(elmt == MONSTER){
		int i;
		va_list ap;
		va_start(ap, y);
		i = va_arg(ap, int);
		addEventToBuffer(buffer->index, i);
	} else if(elmt == SPELL){
		int i;
		va_list ap;
		va_start(ap, y);
		i = va_arg(ap, int);
		addEventToBuffer(buffer->index, i);
	} else if(elmt == _NPC) {
		int i;
		va_list ap;
		va_start(ap, y);
		i = va_arg(ap, int);
		addEventToBuffer(buffer->index, i);
	} else if(elmt == CHARACTER){
		int i;
		va_list ap;
		va_start(ap, y);
		i = va_arg(ap, int);
		addEventToBuffer(buffer->index, i);
	} else{
		addEventToBuffer(buffer->index, -2);
	}
}

void addActionToBufferGame(BufferGame * buffer, int action){
	addEventToBuffer(buffer->action, action);
	addEventToBuffer(buffer->hasBeenExecuted, 0);
}

void removeEventFromBufferGame(BufferGame * buffer, int i){
	removeEventFromBuffer(buffer->elmt, i);
	removeEventFromBuffer(buffer->toGoX, i);
	removeEventFromBuffer(buffer->toGoY, i);
	removeEventFromBuffer(buffer->index, i);
	// removeEventFromBuffer(buffer->action, i);
}

void removeActionFromBufferGame(BufferGame * buffer, int i){
	removeEventFromBuffer(buffer->action, i);
	removeEventFromBuffer(buffer->hasBeenExecuted, i);
}

int hasBeenExcutedBufferAction(const BufferGame * buffer, int i){
	return getEventIBuffer(buffer->hasBeenExecuted, i);
}

void setExecutedBufferAction(const BufferGame * buffer, int i, int value){
	setElemntIBuffer(buffer->hasBeenExecuted, i, value);
}

int getNbEventBufferGame(BufferGame * buffer){
	return getNbEventBuffer(buffer->elmt);
}

void setCurrentIndexBufferGame(BufferGame* buffer, const int currentIndex){
	setCurrentIndexBuffer(buffer->elmt, currentIndex);
	setCurrentIndexBuffer(buffer->toGoX, currentIndex);
	setCurrentIndexBuffer(buffer->toGoX, currentIndex);
	setCurrentIndexBuffer(buffer->index, currentIndex);
}

int getCurrentIndexBufferElmt(BufferGame* buffer){
	return getCurrentIndexBuffer(buffer->elmt);
}

int getIFromElmtBufferGame(BufferGame * buffer, int elmt){
	int i;
	for(i=0;i<getNbEventBuffer(buffer->elmt);i++){
		if(getEventIBuffer(buffer->elmt, i) == elmt)
			return i;
	}
	return -1;
}

int getIndexIBufferGame(const BufferGame * buffer, int i){
	return getEventIBuffer(buffer->index, i);
}

int getEventIBufferGame(const BufferGame * buffer, int i){
	return getEventIBuffer(buffer->elmt, i);
}

int getActionIBufferGame(const BufferGame * buffer, int i){
	return getEventIBuffer(buffer->action, i);
}

int getXBufferGame(const BufferGame * buffer, int i){
	return getEventIBuffer(buffer->toGoX, i);
}

int getYBufferGame(const BufferGame * buffer, int i){
	return getEventIBuffer(buffer->toGoY, i);
}

int isEmptyBufferElmt(const BufferGame * buffer){
	return isEmptyBuffer(buffer->elmt);
}

int countElementBuffer(const BufferGame * buffer, int elmt){
	int i;
	int count =0;
	for(i=0;i<MAX_BUFFER;i++){
		if(getEventIBufferGame(buffer, i) == elmt)
			count++;
	}
	return count;
}

void clearBufferGame(BufferGame * buffer, int elmt){
	int i = 0;
	int first = 0;
	int nbEvent = countElementBuffer(buffer, elmt);
	if(nbEvent > 0){
		for(i=0;i<nbEvent;i++){
			if(first == 0)
				first = 1;
			else{
				removeEventFromBufferGame(buffer, getIFromElmtBufferGame(buffer, elmt));
			}
		}
		if(elmt == CHARACTER)
					// removeActionFromBufferGame(buffer, j);
					clearActionBufferGame(buffer);
	}

}

void clearSpellBuffer(BufferGame * buffer){
	int i;
	int nbEvent = countElementBuffer(buffer, SPELL);
	if(nbEvent > 0){
		for (i=0;i<nbEvent;i++){
			removeEventFromBufferGame(buffer, getIFromElmtBufferGame(buffer, SPELL));
		}
	}
}

void clearCharacBuffer(BufferGame * buffer){
	int i;
	int nbEvent = countElementBuffer(buffer, CHARACTER);
	if(nbEvent > 0){
		for (i=0;i<nbEvent;i++){
			removeEventFromBufferGame(buffer, getIFromElmtBufferGame(buffer, CHARACTER));
		}
	}
}

void clearActionBufferGame(BufferGame * buffer){
	int i;
	for(i = 1; i < MAX_BUFFER; i++){
		removeActionFromBufferGame(buffer, 1);
	}
}

int getCurrentIndexBufferAction(const BufferGame * buffer){
	return getCurrentIndexBuffer(buffer->action);
}

void changeFirstToGoBuffer(const BufferGame * buffer, int x, int y){
	setElemntIBuffer(buffer->toGoX, 0, x);
	setElemntIBuffer(buffer->toGoY, 0, y);
}