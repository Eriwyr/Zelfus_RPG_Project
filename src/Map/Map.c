#include "Map.h"

void mapInit(Map * map, int width, int height){
	int i;
	int j;
	map->height = height;
	map->width = width;
	map->array = malloc(width * sizeof(int*));
	for (i=0;i<width;i++){
		map->array[i] = malloc(height*sizeof(int));
	}
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			map->array[i][j] = 0;
		}
	}
	map->id=0;

}

void mapFree(Map* map){
	int i;


	for (i=0; i<(map->width); i++){
	
		free(map->array[i]);
	}
	free(map->array);
	map->array = NULL;
}

Map* mapCreate(int width, int height){
	Map* map;

	map = malloc(sizeof(Map));
	mapInit(map, width, height);
	return map;
}

void mapDestroy(Map** map){
	mapFree(*map);
	free(*map);
	*map = NULL;
}

int getHeightMap(Map* map){
	return map->height;
}

int getWidthMap(Map* map){
	return map->width;
}

void setElementXYMap(Map * map, int x, int y , int element){
	assert(x<map->width);
	assert(x>=0);
	assert(y>=0);
	assert(y<map->height);
	map->array[x][y] = element;
}

int getElementXYMap(const Map* map, int x, int y){
	assert(x>=0);
	assert(x<map->width);
	assert(y>=0);
	assert(y<map->height);
	return map->array[x][y];
}

Map* loadMapFromFile(char* fileName){
	FILE* file;
	Map* map;
	int i, j, id;
	file = fopen(fileName, "r");
	assert(file != NULL);

	map = mapCreate(MAX_MAP_X, MAX_MAP_Y);
	fscanf(file, "id:%d\n", &id);
	map->id = id;
	for(i=0;i<map->height;i++){
		for(j=0;j<map->width;j++){
			fscanf(file, "%d", &map->array[j][i]);
		}
	}

	fclose(file);
	return map;
}


int isAllowedTile(Map * map, int x, int y){
	int notAllowed[NB_NOT_ALLOWED] = {71, 74, 51, 35, 52, 55, 11, 14, 34, 0}; /*The value in wich anyone cannot walk on*/
	int i;
	if(x<getWidthMap(map) && x>=0){ /*If 0 <= x < width*/
		if(y<getHeightMap(map) && y>=0){ /*If 0 <= y < height*/
			/*We are then in the range of the map, we check if we can walk on the tile*/
			for(i=0;i<NB_NOT_ALLOWED;i++){
				if(getElementXYMap(map, x, y) == notAllowed[i]){
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}


int movePlayerOnMap(Character * player, Map * map, int direction){
	int x, y;

		x = getPosX(getPositionCharacter(player));
		y = getPosY(getPositionCharacter(player));
		
		switch(direction){
			case UP:
				if(isAllowedTile(map, x, y-1)){
					setPositionCharacter(player, x, y-1);
					return 1;
				}
				return 0;
				break;
			case DOWN:
				if(isAllowedTile(map, x, y+1)){
					setPositionCharacter(player, x, y+1);
					return 1;
				}
				return 0;
				break;
			case LEFT:
				if(isAllowedTile(map, x-1, y)){
					setPositionCharacter(player, x-1, y);
					return 1;
				}
				return 0;
				break;
			case RIGHT: 
				if(isAllowedTile(map, x+1, y)){
					setPositionCharacter(player, x+1, y);
					return 1;
				}
				return 0;
				break;
			default:
				return 0;
				break;
	}
	return 0;
}

int getIdMap(const Map* map){
	return map->id;
}


void mapTest(){

	Map map;
	Map *pMap;

	printf("==== Tests of Map ==== \n");

	printf("initialisation using mapInit... ");
	mapInit(&map, 20, 25);
	assert(map.height == 25);
	assert(map.width == 20);
	/* assert(sizeof(map.array) == (20*25*sizeof(int))); à voir plus tard  avec un for*/
	printf("Ok\n");

	printf("Test of mapFree...");
	mapFree(&map);
	assert(map.array == NULL);
	printf("Ok...\n");

	printf("Test of mapCreate... ");
	pMap = mapCreate(10,15);
	assert(pMap != NULL);
	printf("Ok\n");

	printf("Test of mapDestroy... ");
	mapDestroy(&pMap);
	assert(pMap == NULL);
	printf("Ok\n");

	printf("===== The tests went well\n\n");
}

