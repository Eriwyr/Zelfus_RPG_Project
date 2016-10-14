#include "Fight.h"


void loadFight(Fight * fight){

	

	/*We set the character on the map*/
	setPositionCharacter(fight->player, 0, 5);

	// We then set every monster of the horde on the map
	setMonstersOnRandomPosition(fight);

	fight->apEnnemy = 0;
	fight->apPlayer = 0;
	fight->mpEnnemy = 0;
	fight->mpPlayer = 0;
	/*We are ready to start the fight*/	
}

void setMonstersOnRandomPosition(Fight * fight){
	int i, posX, posY;
	
	for ( i = 0; i < getNbMstrHorde(fight->horde); i++){
		do {
			posX = rand() % getWidthMap(fight->map); /*We generate random positions*/
			posY = rand() % getHeightMap(fight->map);
		} while (isEmpty(fight, posX, posY) == 0); /*We resart while there is something on this position*/
		
		setPositionMonster(getElementIHorde(fight->horde, i), posX, posY);
	}
}

int isEmpty(Fight * fight, int x, int y){

	if(isAllowedTile(fight->map, x, y)){

		if(x == getPosX(getPositionCharacter(fight->player))
		   && y == getPosY(getPositionCharacter(fight->player))){
			// If the player is in this position
			return 0; /*Then it's not empty*/
		}
		int i;
		for(i = 0; i < getNbMstrHorde(fight->horde);i++){
			if(x == getPosX(getPositionMonster(getElementIHorde(fight->horde, i)))
			   && y == getPosY(getPositionMonster(getElementIHorde(fight->horde, i)))){
					/*If any of the horde's monster is there*/
					/*Then it's not empty*/
					return 0;
			}
		}

		/*Otherwise it's empty*/
		return 1;
	} 
	return 0;
}

Monster* getClosestMonster(Fight * fight){
	int distance;
	int closest;
	int i;
	int tmpDistance;
	/*We set the distance and the index to the first element*/
	distance = getDistance(getPositionCharacter(fight->player), 
				getPositionMonster(getElementIHorde(fight->horde, 0)) );
	closest = 0;
	for(i = 0; i<getNbMstrHorde(fight->horde); i++){
		tmpDistance = getDistance(getPositionCharacter(fight->player), 
				getPositionMonster(getElementIHorde(fight->horde, i)));
		if(tmpDistance <= distance){
			/*if there is a monster with a 
				shorter distance, we change the distance
			 	and the index*/
			distance = tmpDistance;
			closest = i;
		}
			
	}
	/*We return the element with the shortest distance*/
	return getElementIHorde(fight->horde, closest);
}

int isFinished(Fight * fight){
	if(getLifePointsCharacter(fight->player) <= 0)
		/*If the character is dead we return 1*/
		return 1;

	if(getNbMstrHorde(fight->horde) == 0)
		/*If we killed all monsters*/
		return 1;

	/*Otherwise we continue*/
	return 0;
}


void actionMove(Fight * fight, int direction){
	switch(direction){
		case DOWN:
			if(getMpPlayerFight(fight) > 0){
                            /*We check if there is enough mp to move*/
				if(movePlayerOnFight(fight, DOWN)){
	                                /*If the movement succeed, we decrement the mps*/
					setMpPlayerFight(fight, getMpPlayerFight(fight)-1);
				}          
			}
		break;

		case UP:
			if(getMpPlayerFight(fight) > 0){
                            /*We check if there is enough mp to move*/
				if(movePlayerOnFight(fight, UP)){
	                                /*If the movement succeed, we decrement the mps*/
					setMpPlayerFight(fight, getMpPlayerFight(fight)-1);

				}          
			}
		break;

		case RIGHT:
			if(getMpPlayerFight(fight) > 0){
                            /*We check if there is enough mp to move*/
				if(movePlayerOnFight(fight, RIGHT)){
	                                /*If the movement succeed, we decrement the mps*/
					setMpPlayerFight(fight, getMpPlayerFight(fight)-1);

				}          
			}
		break;

		case LEFT:
			if(getMpPlayerFight(fight) > 0){
                            /*We check if there is enough mp to move*/
				if(movePlayerOnFight(fight, LEFT)){
	                                /*If the movement succeed, we decrement the mps*/
					setMpPlayerFight(fight, getMpPlayerFight(fight)-1);

				}          
			}
		break;
	}
}

int actionAttack(Fight * fight, int attack){


	if(getApPlayerFight(fight) > 0){
		/*We check if we have enough ap to attack*/
		fight->actualMonsterAttacked = getClosestMonster(fight);

		switch(attack){
			case ATTACK_1:
				if(attackMonster(fight->player, fight->actualMonsterAttacked))
					setApPlayerFight(fight, getApPlayerFight(fight)-1); /*If the attack is successful, we decrement the aps*/
				if(getLifePointsMonster(fight->actualMonsterAttacked) <= 0){
					fight->toKill =  1;
				}
				return 1;
			break;

			case ATTACK_2:
				if(attackMonsterSpell(fight->player, fight->actualMonsterAttacked, getSpell(getSpellBarCharacter(fight->player), 0) )){
					setApPlayerFight(fight, getApPlayerFight(fight)-1); /*If the attack is successful, we decrement the aps*/
					if(getLifePointsMonster(fight->actualMonsterAttacked) <= 0){
						fight->toKill =  1;
					}
					return 2;
                }
			break;

			case ATTACK_3:
				if(attackMonsterSpell(fight->player, fight->actualMonsterAttacked, getSpell(getSpellBarCharacter(fight->player), 1) )){
					/*If the attack is successful, we decrement the aps*/
					setApPlayerFight(fight, getApPlayerFight(fight)-1);
					if(getLifePointsMonster(fight->actualMonsterAttacked) <= 0){
						fight->toKill =  1;
					}
					return 2;
                }

		}

		
		

	}

	return 0;
}

void killMonster(Fight * fight, Monster * monster){

	// we delete the monster from the horde
	removeMonster(fight->horde, getIdMonster(monster)+1); 
	// We free it
	monsterDestroy(&monster);

	fight->nbMstrKilled++;
}

int getNbMstrKilledFight(const Fight * fight){
	return fight->nbMstrKilled;
}

int moveMonsterOnFight(Fight * fight, int i, int direction){
	int x, y;
	Monster * monster;
	monster = getElementIHorde(fight->horde, i);
	x = getPosX(getPositionMonster(monster));
	y = getPosY(getPositionMonster(monster));
		switch(direction){
			case UP:
				if(isEmpty(fight, x, y-1)){
					setPositionMonster(monster, x, y-1);

					return 1;
				}
				return 0;
				break;
			case DOWN:
				if(isEmpty(fight, x, y+1)){
					setPositionMonster(monster, x, y+1);
					return 1;
				}
				return 0;
				break;
			case LEFT:
				if(isEmpty(fight, x-1, y)){
					setPositionMonster(monster, x-1, y);
					return 1;
				}
				return 0;
				break;
			case RIGHT: 
				if(isEmpty(fight, x+1, y)){
					setPositionMonster(monster, x+1, y);
					return 1;
				}
				return 0;
				break;
			case -1:
				return 1; 
			default:
				return 0;
				break;
	}
	return 0;
}

int movePlayerOnFight(Fight * fight, int direction){
	int x = getPosX(getPositionCharacter(fight->player));
	int y = getPosY(getPositionCharacter(fight->player));
	switch(direction){
		case UP:
			if(isEmpty(fight, x, y-1))
				if(movePlayerOnMap(fight->player, fight->map, UP))
					return 1;
			break;
		case DOWN:
			if(isEmpty(fight, x, y+1))
				if(movePlayerOnMap(fight->player, fight->map, DOWN))
					return 1;
			break;
		case LEFT:
			if(isEmpty(fight, x-1, y))
				if(movePlayerOnMap(fight->player, fight->map, LEFT))
					return 1;
			break;
		case RIGHT:
			if(isEmpty(fight, x+1, y))
				if(movePlayerOnMap(fight->player, fight->map, RIGHT))
					return 1;
			break;
		default:
			return 0;
			break;
	}
	return 0;
}

Map* getMapFight(const Fight* fight){
	return fight->map;
}

Character* getCharacterFight(const Fight* fight){
	return fight->player;
}

Horde* getHordeFight(const Fight* fight){
	return fight->horde;
}

void setMapFight(Fight* fight, Map* map){
	fight->map = map;
}


int getApPlayerFight(const Fight* fight){
	return fight->apPlayer;
}

void setApPlayerFight(Fight* fight, const int apPlayer){
	fight->apPlayer = apPlayer;
}


int getMpPlayerFight(const Fight* fight){
	return fight->mpPlayer;
}

void setMpPlayerFight(Fight* fight, const int mpPlayer){
	fight->mpPlayer = mpPlayer;
}


int getApEnnemyFight(const Fight* fight){
	return fight->apEnnemy;
}

void setApEnnemyFight(Fight* fight, const int apEnnemy){
	fight->apEnnemy = apEnnemy;
}


int getMpEnnemyFight(const Fight* fight){
	return fight->mpEnnemy;
}

void setMpEnnemyFight(Fight* fight, const int mpEnnemy){
	fight->mpEnnemy = mpEnnemy;
}

void fightInit(Fight * fight){
	fight->map = NULL;
	fight->player = NULL;
	fight->horde = NULL;
	fight->apPlayer = 0;
	fight->mpPlayer = 0;
	fight->mpEnnemy = 0;
	fight->apEnnemy = 0;
	fight->toKill = 0;
	fight->nbMstrKilled = 0;
}

Fight* fightCreate(){
	Fight* fight;
	fight = malloc(sizeof(Fight));

	fightInit(fight);
	return fight;
}

void fightFree(Fight * fight){
	if(fight->map != NULL)
		mapDestroy(&fight->map);
	
	hordeDestroy(&fight->horde);
}

void fightDestroy(Fight ** fight){
	fightFree(*fight);
	free(*fight);
	*fight = NULL;
}

Fight* loadFightFromFile(char* fileName, Character* player){
	FILE* file;
	Fight* fight;
	int mapNumber, nbMstr, idM, i;
	char mapNumberText[10];
	char mapFile[CHAR_SIZE_MAX];
	char idMTxt[10];
	char monsterFile[CHAR_SIZE_MAX];


	#ifdef WINDOWS_OS
		strreplace(filName, '/', '\\');
	#endif
	
	file = fopen(fileName, "r");
	assert(file != NULL);


	fight = fightCreate();
	fscanf(file, "id : %d\n", &fight->id);
	fscanf(file, "#mapFile : %d\n", &mapNumber);
	sprintf(mapNumberText, "%d", mapNumber);
	strcpy(mapFile, "data/Map/map");
	strcat(mapFile, mapNumberText);
	strcat(mapFile, ".map");
	fight->map = loadMapFromFile(mapFile);

	fscanf(file, "#nbMstr : %d\n", &nbMstr);
	fight->horde = hordeCreate(nbMstr);
	for(i=0;i<nbMstr;i++){
		fscanf(file, "idM:%d\n", &idM);
		sprintf(idMTxt, "%d", idM);
		strcpy(monsterFile, "data/Init/Monster/monster");
		strcat(monsterFile, idMTxt);
		strcat(monsterFile, ".init");
		addMonster(fight->horde, loadMonsterFromFile(monsterFile));
	}

	fight->player = player;

	Position pos;
	fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
	setPositionCharacter(fight->player, pos.x, pos.y);

	fscanf(file, "mpPlayer:%d\n", &fight->mpPlayer);
	fscanf(file, "apPlayer:%d\n", &fight->apPlayer);
	fscanf(file, "mpEnnemy:%d\n", &fight->mpEnnemy);
	fscanf(file, "apEnnemy:%d\n", &fight->apEnnemy);

	fclose(file);
	return fight;
}	

int getToKillFight(const Fight* fight){
	return fight->toKill;
}

void setToKillFight(Fight* fight, int value){
	fight->toKill=value;
}

Monster* getActualMonsterAttackedFight(const Fight* fight){
	return fight->actualMonsterAttacked;
}


int getIdFight(const Fight* fight){
	return fight->id;
}

void setIdFight(Fight* fight, const int id){
	fight->id = id;
}



void fightTest(){
	// Fight fight;
	// Character * player;
	// Horde * horde;
	// Monster *monster1, *monster2, *monster3;
	// Monster * test;
	// player = characterCreate();
	// monster1 = monsterCreate("Monster 1");
	// monster2 = monsterCreate("Monster 2");
	// monster3 = monsterCreate("Monster 3");

	// horde = hordeCreate(3);

	// setPositionMonster(monster1, 8, 12);
	// setPositionMonster(monster2, 5, 2);
	// setPositionMonster(monster3, 15, 2);
	// setPositionCharacter(player, 0, 0);

	// addMonster(horde, monster1);
	// addMonster(horde, monster2);
	// addMonster(horde, monster3);

	// fight.horde = horde;
	// fight.player = player;

	// printf("==== Test of Fight ====\n");

	// printf("Test of getClosestMonster... ");
	// test = getClosestMonster(&fight);
	// assert(strcmp(getNameMonster(test), getNameMonster(monster2)) == 0 );

	// setPositionCharacter(player, 8, 11);
	// test = getClosestMonster(&fight);
	// assert(strcmp(getNameMonster(test), getNameMonster(monster1)) == 0 );

	// setPositionCharacter(player, 2, 12);
	// test = getClosestMonster(&fight);
	// assert(strcmp(getNameMonster(test), getNameMonster(monster1)) == 0 );
	// printf("Ok.\n");
	
	// characterDestroy(&player);
	// hordeDestroy(&horde);
	// printf("==== The tests went well ==== \n\n");

	// Fight * fight1;
	// fight1 = loadFightFromFile("data/Init/Fight/fight1.init");
	// killMonster(fight1, getElementIHorde(fight1->horde, 1));
	// fightDestroy(&fight1);
}