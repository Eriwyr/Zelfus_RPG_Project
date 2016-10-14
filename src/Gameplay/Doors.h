#ifndef DOORS_H
#define DOORS_H

#include <stdio.h>
#include <stdlib.h>
#include "OS.h"
#include "str.h"

#include "Map.h"
#include "Position.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
 * @struct Door
 * @brief The struct which manage the changement of maps
 */
typedef struct {
	int id;
	Map * map;
	int roomId;
	Position * pos;
	Position * posArrival;
}Door;


void doorInit(Door * door);
Door* doorCreate();

void doorFree(Door * door);
void doorDestroy(Door ** door);
Door* loadDoorFromFile(char* fileName);
int getRoomIdDoor(const Door* door);
void setRoomIdDoor(Door* door, const int roomId);
Map* getMapDoor(const Door* door);
Position* getPositionDoor(const Door* door);
Position* getPosArrivalDoor(const Door* door);

#endif