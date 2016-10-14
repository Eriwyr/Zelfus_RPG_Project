#include "Position.h"

int getPosX(const Position * pos){
	return pos->x;
}

int getPosY(const Position * pos){
	return pos->y;
}

void setPosX(Position * pos, int x){
	pos->x = x;
}

void setPosY(Position * pos, int y){
	pos->y = y;
}

int getDistance(Position * pos1, Position * pos2){
	int distance;

	distance = ceil( sqrt( pow((pos1->x - pos2->x),2) + pow((pos1->y - pos2->y),2) ) );

	return distance;
}

int getNbSquares(Position * pos1, Position * pos2){
	return ( abs((pos1->x - pos2->x)) + abs((pos1->y - pos2->y)) - 1);
}

void positionTest(){
	Position pos;
	Position pos1;
	pos.x = 10;
	pos.y = 10;

	pos1.x = 2;
	pos1.y = 2;
	int distance; 

	printf("Test of getDistance... ");
	distance = getDistance(&pos, &pos1);
	assert(distance == 12);

	pos.x = 7;
	pos.y = 14;

	pos1.x = 6;
	pos1.y = 9;
	
	distance = getDistance(&pos, &pos1);
	assert(distance == 6);
	printf("Ok.\n");
	
	
}