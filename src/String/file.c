#include "file.h"

int exist(char* fileName){
	FILE* file;
	int i = 0;
	file = fopen(fileName, "r");
	assert(file != NULL);
	fscanf(file, "save:%d", &i);

	fclose(file);
	return i;
}