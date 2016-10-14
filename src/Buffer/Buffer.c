#include "Buffer.h"

void bufferInit(Buffer * buffer){
	int i;
	buffer->soldier = malloc(MAX_BUFFER*sizeof(int));

	for(i=0;i<MAX_BUFFER;i++){
		buffer->soldier[i] = -1;
	}

	buffer->currentIndex = 0;
	buffer->nbEvent = 0;

}

void bufferFree(Buffer * buffer){
	free(buffer->soldier);
	buffer->soldier = NULL;
	buffer->currentIndex = 0;
}

Buffer* bufferCreate(){
	Buffer * buffer;
	buffer = malloc(sizeof(Buffer));

	bufferInit(buffer);

	return buffer;
}

void bufferDestroy(Buffer ** buffer){
	bufferFree(*buffer);
	free(*buffer);

	*buffer = NULL;
}

void printBuffer(Buffer * buffer){
	int i;
	for(i=0;i<MAX_BUFFER;i++){
		printf("%d ", buffer->soldier[i]);
	}
	printf("\n");
}

void addEventToBuffer(Buffer * buffer, int event){
	if(buffer->nbEvent < MAX_BUFFER){
		buffer->soldier[buffer->nbEvent] = event;
		buffer->nbEvent++;
	} else {
		// printf("vilis\n");
	}
}

void removeEventFromBuffer(Buffer * buffer, int i){
	assert(i<MAX_BUFFER);
	assert(i>=0);

	int j;

	for(j=i;j<MAX_BUFFER-1;j++){
		buffer->soldier[j] = buffer->soldier[j+1];
	}

	buffer->soldier[MAX_BUFFER-1] = -1;
	
	buffer->nbEvent--;
	if(buffer->nbEvent < 0)
		buffer->nbEvent = 0;
}

int getEventIBuffer(Buffer * buffer, int i){
	assert(i<MAX_BUFFER);
	assert(i>=0);

	return buffer->soldier[i];
}

void setElemntIBuffer(Buffer * buffer, int i, int value){
	buffer->soldier[i] = value;
}

int getCurrentIndexBuffer(const Buffer* buffer){
	return buffer->currentIndex;
}

void setCurrentIndexBuffer(Buffer* buffer, const int currentIndex){
	buffer->currentIndex = currentIndex;
}


int getNbEventBuffer(const Buffer* buffer){
	return buffer->nbEvent;
}

int isEmptyBuffer(const Buffer* buffer){
	int i;
	for(i=0;i<MAX_BUFFER;i++){
		if(buffer->soldier[i] != -1){
			return 0;
		}
	}
	return 1;
}

