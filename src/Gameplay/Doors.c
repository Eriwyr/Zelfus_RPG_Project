#include "Doors.h"

void doorInit(Door * door){
	door->id = 0;
	door->map = NULL;
	door->roomId = 0;
	door->pos = malloc(sizeof(Position));
	door->posArrival = malloc(sizeof(Position));
}

Door* doorCreate(){
	Door * hodor;
	hodor = malloc(sizeof(Door));

	doorInit(hodor);

	return hodor;
}

void doorFree(Door * door){
	free(door->pos);
	free(door->posArrival);
	if(door->map != NULL){
		mapDestroy(&door->map);
	}
}

void doorDestroy(Door ** door){
	doorFree(*door);
	free(*door);

	*door = NULL;
}


Door* loadDoorFromFile(char* fileName){
	FILE* file;
	Door* door;

	int mapId;
	char mapNumberText[10];
	char mapFile[CHAR_SIZE_MAX];
	Position pos;
	#ifdef WINDOWS_OS
		strreplace(filName, '/', '\\');
	#endif
	
	file = fopen(fileName, "r");
	assert(file != NULL);

	door = doorCreate();

	fscanf(file, "id:%d\n", &door->id);
	fscanf(file, "idMap:%d\n", &mapId);
	sprintf(mapNumberText, "%d", mapId);
	strcpy(mapFile, "data/Map/map");
	strcat(mapFile, mapNumberText);
	strcat(mapFile, ".map");
	door->map = loadMapFromFile(mapFile);
	fscanf(file, "idRoom:%d\n", &door->roomId);
	fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
	setPosX(door->pos, pos.x);
	setPosY(door->pos, pos.y);
	fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
	setPosX(door->posArrival, pos.x);
	setPosY(door->posArrival, pos.y);

	fclose(file);
	return door;
}


int getRoomIdDoor(const Door* door){
	return door->roomId;
}

void setRoomIdDoor(Door* door, const int roomId){
	door->roomId = roomId;
}


Map* getMapDoor(const Door* door){
	return door->map;
}

Position* getPositionDoor(const Door* door){
	return door->pos;
}

Position* getPosArrivalDoor(const Door* door){
	return door->posArrival;
}

