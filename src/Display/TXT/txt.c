#include "txt.h"

void clear(){
	#ifdef WINDOWS_OS
		system("cls");
	#else
		system("clear");
	#endif
}


void setMapTxt(Map * map){
	int height, width, i, j;
	height = getHeightMap(map);
	width = getWidthMap(map);
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(isAllowedTile(map, j, i) || getElementXYMap(map, j, i) == 0)
				setElementXYMap(map, j, i, 1);
			else
				setElementXYMap(map, j, i, 9);
		}
	}
}
void setPlayerTxt(Character * player, Map* map){
	int x, y;
	x = getPosX(getPositionCharacter(player));
	y = getPosY(getPositionCharacter(player));
	setElementXYMap(map, x, y, 2);
}

void setMonsterTxt(Horde * horde, Map* map){
	 int i, x, y;
	 for(i=0;i<getNbMstrHorde(horde);i++){
	 	x = getPosX(getPositionMonster(getElementIHorde(horde, i)));
	 	y = getPosY(getPositionMonster(getElementIHorde(horde, i)));
	 	setElementXYMap(map, x, y, 3);
	 }
}



void drawMapTxt(Map* map){
	int height, width, i, j;
	height = getHeightMap(map);
	width = getWidthMap(map);
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			printf("%d ", getElementXYMap(map, j, i));
		}
		printf("\n");
	}
}



void delayTxt(unsigned int ms){
	#ifdef WINDOWS_OS
		Sleep(ms);
	#else 
		usleep(ms*1000);
	#endif
}

int convertSecToMillisec(int sec){
	return sec*1000;
}
