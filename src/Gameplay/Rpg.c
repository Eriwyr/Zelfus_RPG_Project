#include "Rpg.h"

void acceptQuest(Rpg * rpg, NPC * npc){
	addQuest(getDiaryCharacter(rpg->player), getQuestNpc(npc));
	setAcceptedNpc(npc, 1);
	setDialogNpc(npc, "Come back when you fulfilled the quest");
	updateSecondMap(rpg);
}


QuestObject* getClosestObject(Rpg * rpg){
	int distance, idNpc, i, j, tmpDistance;
	ObjectSet * set;
	/*We set the distance and the index to the first element*/
	int closest = -1;
	for(i=0;i<rpg->nbNpc;i++){
		set = getObjectsObjective(getObjectiveQ(getQuestNpc(getNpcIRpg(rpg, i))));

		if(getNbObjSet(set) <= 0)
			return NULL;

		distance = getDistance(getPositionCharacter(rpg->player), 
				getPositionObject(getObjectIObjset(set, 0)));
		idNpc = 0;
		
		for(j = 0; j<getNbObjSet(set); j++){
			tmpDistance = getDistance(getPositionCharacter(rpg->player), 
					getPositionObject(getObjectIObjset(set, i)));
			if(tmpDistance <= distance){
				/*if there is a monster with a 
					shorter distance, we change the distance
				 	and the index*/
				distance = tmpDistance;
				closest = j;
				idNpc = i;
			}
				
		}
	}

	set = getObjectsObjective(getObjectiveQ(getQuestNpc(getNpcIRpg(rpg, idNpc))));
	
	/*We return the element with the shortest distance*/
	if(closest >= 0){
		return getObjectIObjset(set, closest);
	}
	else 
		return NULL;	
}


int getNpcIdFromObject(Rpg * rpg, QuestObject * obj){
	int i, j;
	ObjectSet * set;
	for(i=0;i<rpg->nbNpc;i++){
		set = getObjectsObjective(getObjectiveQ(getQuestNpc(rpg->npc[i])));
		for(j=0;j<getNbObjSet(set);j++){
			if(getObjectIObjset(set, j) == obj)
				return i;
		}
		
	}
	return -1;
}

Character* getCharacterRpg(const Rpg* rpg){
	return rpg->player;
}

void setCharacterRpg(Rpg* rpg, Character* player){
	rpg->player = player;
}

Map* getMapRpg(const Rpg* rpg){
	return rpg->map;
}

void setMapRpg(Rpg* rpg, Map* map){
	rpg->map = map;
}

int moveNpcRandom(Rpg * rpg){
	int direction, i, x, y;
	i = rand() % getNbNpcRpg(rpg);
	x = getPosX(getPositionNpc(getNpcIRpg(rpg, i)));
	y = getPosY(getPositionNpc(getNpcIRpg(rpg, i)));
	direction = (rand() % 5) -1 ; //We set a radom number between -1 et 3
	switch(direction){
			case 3:
				if(isEmptyRpg(rpg, x, y-1) && getElementXYMap(rpg->map1, x, y-1) != 2){
					setPositionNpc(getNpcIRpg(rpg, i), x, y-1);
					// setElementXYMap(rpg->map1, x, y, 0);
					// setElementXYMap(rpg->map1, x, y-1, 1);
				}
			break;
			case 0:
				if(isEmptyRpg(rpg, x, y+1) && getElementXYMap(rpg->map1, x, y+1) != 2){
					setPositionNpc(getNpcIRpg(rpg, i), x, y+1);
					// setElementXYMap(rpg->map1, x, y, 0);
					// setElementXYMap(rpg->map1, x, y+1, 1);
				}
			break;
			case 1:
				if(isEmptyRpg(rpg, x-1, y) && getElementXYMap(rpg->map1, x-1, y) != 2){
					setPositionNpc(getNpcIRpg(rpg, i), x-1, y);
					// setElementXYMap(rpg->map1, x, y, 0);
					// setElementXYMap(rpg->map1, x-1, y, 1);
				}
			break;
			case 2:
				if(isEmptyRpg(rpg, x+1, y) && getElementXYMap(rpg->map1, x+1, y) != 2){
					setPositionNpc(getNpcIRpg(rpg, i), x+1, y);
					// setElementXYMap(rpg->map1, x, y, 0);
					// setElementXYMap(rpg->map1, x+1, y, 1);
				}
			break;
		}	

	return i ;
}

int getIdFromNpc(Rpg * rpg, NPC * npc){
	int i;
	for(i=0; i<rpg->nbNpc;i++){
		if(getNpcIRpg(rpg, i) == npc){
			return i;
		}
	}
	return -1;
}

int talkToNpc(Rpg * rpg, NPC * npc){ 
	if(isAcceptedNpc(npc)){
		if(isAccomplished(getQuestNpc(npc))){
			if(!hasRewardedNpc(npc)){
				reward(rpg->player, npc);
				setDialogNpc(npc, "There you go.");
				deleteQuest(getDiaryCharacter(rpg->player), getIdFromQuest(getDiaryCharacter(rpg->player), getQuestNpc(npc)) + 1);
			}
			
		} 
		return 1;
	} else {
		acceptQuest(rpg, npc);
	}
	return 0;
}

void changeLevelRpg(Rpg * rpg, Map * map){
	// mapDestroy(&rpg->map);
	rpg->map = map;
	rpgInitSecondMap(rpg);
}

void checkQuests(Rpg * rpg){
	int i;
	Quest * quest;
	for(i=0;i<getNbQuestDiary(getDiaryCharacter(rpg->player));i++){
		quest = getQuestIDiary(getDiaryCharacter(rpg->player), i);
		if(checkIsFinishQuest(quest)){
			questFinish(quest);
		}
	}
}

Fight* checkForFight(Rpg * rpg, int * id){
	int x, y, monsterX, monsterY, i;
	x = getPosX(getPositionCharacter(rpg->player));
	y = getPosY(getPositionCharacter(rpg->player));
	for(i=0;i<rpg->nbMstr;i++){
		monsterX = getPosX(getPositionMonsterRpg(rpg->monsters[i]));
		monsterY = getPosY(getPositionMonsterRpg(rpg->monsters[i]));
		if(getIdMap(rpg->map) == getRoomIdMonsterRpg(rpg->monsters[i])){
			if(monsterX == x && monsterY == y){
				*id = i;
				return getFightMonsterRpg(rpg->monsters[i]);
			}
		}
		
	}
	*id = -1;
	return NULL;
}


int getIFromFightRpg(Rpg * rpg, Fight * fight){
	int i;
	for(i=0;i<rpg->nbMstr;i++){
		if(getFightMonsterRpg(rpg->monsters[i]) == fight)
			return i;
	}
	return -1;
}

void removeMonsterRpgI(Rpg * rpg, int ind){
	int j;
	/*Making sure that the ind is <= to the number of monsters and > 0 */
	assert(ind <= rpg->nbMstr);
	assert(ind > 0);
	if(rpg->nbMstr == 1)
		monsterRpgDestroy(&rpg->monsters[0]);
	for(j = ind-1; j<rpg->nbMstr-1;j++){ /*We start the loop from the ind ( minus one to keep first element at ind 1 )*/
		if(rpg->monsters[j] != NULL)
			monsterRpgDestroy(&rpg->monsters[j]);
		rpg->monsters[j] = rpg->monsters[j+1]; /*Each elements is then shifted from 1*/
	}
	rpg->nbMstr--; // There is now one element less

	// We redifine the size once there is enough free slots
	MonsterRpg ** tmp = rpg->monsters; //We save the current monsters
	rpg->size--;
	rpg->monsters = malloc(rpg->size*sizeof(MonsterRpg*)); //We reallocate memory
	for(j=0;j<rpg->nbMstr;j++){
		rpg->monsters[j] = tmp[j]; //Restoration of the saved monsters
	}
	free(tmp);
}


int pickUpObject(Rpg * rpg, int * i, int * j){


	int npcId, id, x, y;
	Position * posObj;
	Position * posPlayer;
	QuestObject * object = getClosestObject(rpg);
	if(object != NULL){

		posPlayer = getPositionCharacter(rpg->player);
		posObj = getPositionObject(object);


		npcId = getNpcIdFromObject(rpg, object);
		ObjectSet * set;
		set = getObjectsObjective(getObjectiveQ(getQuestNpc(rpg->npc[npcId])));
		id = getIdFromObject(set, object);

		if(getRoomIdObject(object) == getIdMap(rpg->map)){
			if(getNbSquares(posPlayer, posObj) == 0){
				if(isAcceptedNpc(rpg->npc[npcId])){
					removeQuestObject(set, id+1);
					x = getPosX(posObj);
					y = getPosY(posObj);
					setElementXYMap(rpg->map1, x, y, 0);
					questObjectDestroy(&object);
					*i = npcId;
					*j = id;
					return 1;
				}
			}
		}	
		
	}
	*i = -1;
	*j = -1;
	return 0;
	


}

void reward(Character * player, NPC *npc){
	Reward * reward;
	Quest * quest = getQuestNpc(npc);
	reward = getRewardQ(quest);
	setMoneyCharacter(player, getMoneyReward(reward) + getMoneyCharacter(player));
	setXpCharacter(player, getXpReward(reward) + getXpCharacter(player));
	setRewardedNpc(npc, 1);
}


int isEmptyRpg(Rpg * rpg, int x, int y){

	if(isAllowedTile(rpg->map, x, y)){

		if(x == getPosX(getPositionCharacter(rpg->player))
		   && y == getPosY(getPositionCharacter(rpg->player))){
			// If the player is in this position
			return 0; /*Then it's not empty*/
		}
		if(getElementXYMap(rpg->map1, x, y) == 1) /*If there is something on the map*/
			return 0; /*Then it's not empty*/

		/*Otherwise it's empty*/
		return 1;
	} 
	return 0;
}

int movePlayerOnRpg(Rpg * rpg, int direction){
	int x = getPosX(getPositionCharacter(rpg->player));
	int y = getPosY(getPositionCharacter(rpg->player));

	switch(direction){
		case UP:
			if(isEmptyRpg(rpg, x, y-1))
				if(movePlayerOnMap(rpg->player, rpg->map, UP))
					return 1;
			break;
		case DOWN:
			if(isEmptyRpg(rpg, x, y+1))
				if(movePlayerOnMap(rpg->player, rpg->map, DOWN))
					return 1;
			break;
		case LEFT:
			if(isEmptyRpg(rpg, x-1, y))
				if(movePlayerOnMap(rpg->player, rpg->map, LEFT))
					return 1;
			break;
		case RIGHT:
			if(isEmptyRpg(rpg, x+1, y))
				if(movePlayerOnMap(rpg->player, rpg->map, RIGHT))
					return 1;
			break;
		default:
			return 0;
			break;
	}
	return 0;
}

void rpgInit(Rpg* rpg){
	rpg->player = NULL;
	rpg->map = NULL;
	rpg->map1 = NULL;
	rpg->npc = NULL;
	rpg->monsters = NULL;
	rpg->size = 0;
}

Rpg* loadRpgFromFile(char* fileName){
	Rpg* rpg;
	rpg = malloc(sizeof(Rpg));
	rpgInit(rpg);
	FILE* file;
	int mapNumber, i, idN, idM, idDoor;
	char mapNumberText[10];
	char mapFile[CHAR_SIZE_MAX];
	char idNTxt[10], idMTxt[10], idDTxt[10];
	char npcFile[CHAR_SIZE_MAX], mstrFile[CHAR_SIZE_MAX], doorFile[CHAR_SIZE_MAX];

	Position pos;
	rpg->npc = NULL;

	strcpy(mapFile, "data/Map/map");

	#ifdef WINDOWS_OS
		strreplace(fileName, '/', '\\');
	#endif

	file = fopen(fileName, "r");
	assert(file != NULL);

	fscanf(file, "#mapFile : %d\n", &mapNumber);
	sprintf(mapNumberText, "%d", mapNumber);
	strcat(mapFile, mapNumberText);
	strcat(mapFile, ".map");
	// rpg->map = loadMapFromFile(mapFile);
	fscanf(file, "#nbNPC : %d\n", &(rpg->nbNpc));
	rpg->npc = malloc(rpg->nbNpc*sizeof(NPC*));
	for(i=0;i<rpg->nbNpc;i++){
		fscanf(file, "idN:%d\n", &idN);
		sprintf(idNTxt, "%d", idN);

		if(exist("data/Save/load.load")){
			strcpy(npcFile, "data/Save/NPC/npc");
			strcat(npcFile, idNTxt);
			strcat(npcFile, ".save");
		} else {
			strcpy(npcFile, "data/Init/NPC/npc");
			strcat(npcFile, idNTxt);
			strcat(npcFile, ".init");
		}
		
		rpg->npc[i] = loadNPCFromFile(npcFile);
		fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
		setPositionNpc(rpg->npc[i], pos.x, pos.y);
	}
	
	if(exist("data/Save/load.load")){
		rpg->player = loadCharacterFromFile("data/Save/Character/character.save");
	} else {
		rpg->player = loadCharacterFromFile("data/Init/Character/character.init");
	}

	fscanf(file, "#nbMstr : %d\n", &rpg->nbMstr);
	rpg->monsters = malloc(rpg->nbMstr*sizeof(MonsterRpg*));
	rpg->size = rpg->nbMstr;
	for(i=0;i<rpg->nbMstr;i++){
		fscanf(file, "idM:%d\n", &idM);
		sprintf(idMTxt, "%d", idM);
		strcpy(mstrFile, "data/Init/MonsterRpg/monsterRpg");
		strcat(mstrFile, idMTxt);
		strcat(mstrFile, ".init");
		rpg->monsters[i] = loadMonsterRpgFromFile(mstrFile, rpg->player);
		fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
		setPositionMonsterRpg(rpg->monsters[i], pos.x, pos.y);
	}

	

	fscanf(file, "#nbDoors : %d\n", &rpg->nbDoors);
	rpg->doors = malloc(rpg->nbDoors*sizeof(Door*));
	for(i=0;i<rpg->nbDoors;i++){
		fscanf(file, "idD:%d\n", &idDoor);
		sprintf(idDTxt, "%d", idDoor);
		strcpy(doorFile, "data/Init/Door/door");
		strcat(doorFile, idDTxt);
		strcat(doorFile, ".init");
		rpg->doors[i] = loadDoorFromFile(doorFile);
	}
	rpg->map = getMapDoor(rpg->doors[1]);
	
	

	rpg->map1 = mapCreate(MAX_MAP_X, MAX_MAP_Y);
	rpgInitSecondMap(rpg);

	fclose(file);
	return rpg;
}

void saveRpgOnFile(Rpg * rpg, char* fileName){
	FILE* file;
	int i;
	char npcFile[CHAR_SIZE_MAX], mstrFile[CHAR_SIZE_MAX];
	char npcId[10], mstrId[10];

	if(!exist("data/Save/load.load")){
		FILE* file2;
		file2 = fopen("data/Save/load.load", "w+");
		fprintf(file2, "save:1\n");
		fclose(file2);
	}

	#ifdef WINDOWS_OS
		strreplace(fileName, "/", "\\");
	#endif

	file = fopen(fileName, "w+");
	fprintf(file, "#mapFile : %d\n\n", getIdMap(rpg->map));
	fprintf(file, "#nbNPC : %d\n", rpg->nbNpc);
	
	for(i=0;i<rpg->nbNpc;i++){
		fprintf(file, "idN:%d\n", getIdNpc(getNpcIRpg(rpg, i)));
		sprintf(npcId, "%d", getIdNpc(getNpcIRpg(rpg, i)));
		strcpy(npcFile, "data/Save/NPC/npc");
		strcat(npcFile, npcId);
		strcat(npcFile, ".save");
		saveNPCOnFile(getNpcIRpg(rpg, i), npcFile);
		fprintf(file, "x:%d  y:%d\n", getPosX(getPositionNpc(getNpcIRpg(rpg, i))), getPosY(getPositionNpc(getNpcIRpg(rpg, i))));
	}
	fprintf(file, "\n");
	fprintf(file, "#nbMstr : %d\n", rpg->nbMstr);
	for(i=0;i<rpg->nbMstr;i++){
		fprintf(file, "idM:%d\n", getIdMonsterRpg(getMonsterRpgIRpg(rpg, i)));
		sprintf(mstrId, "%d", getIdMonsterRpg(rpg->monsters[i]));
		strcpy(mstrFile, "data/Save/MonsterRpg/monsterRpg");
		strcat(mstrFile, mstrId);
		strcat(mstrFile, ".save");
		saveMonsterRpgOnFile(getMonsterRpgIRpg(rpg, i), mstrFile);
		fprintf(file, "x:%d  y:%d\n", getPosX(getPositionMonsterRpg(getMonsterRpgIRpg(rpg, i))), getPosY(getPositionMonsterRpg(getMonsterRpgIRpg(rpg, i))));
	}
	saveCharacterOnFile(rpg->player, "data/Save/Character/character.save");

	fclose(file);
}

void rpgInitSecondMap(Rpg * rpg){
	int i, j;
	for(i=0;i<getHeightMap(rpg->map1);i++){
		for(j=0;j<getWidthMap(rpg->map1);j++){
			setElementXYMap(rpg->map1, j, i, 0);
		}
	}
	updateSecondMap(rpg);
}

void updateSecondMap(Rpg* rpg){
	int x, y, i, j;
	ObjectSet * set;
	for(i=0;i<rpg->nbNpc;i++){
		if(getIdMap(rpg->map) == getRoomIdNpc(getNpcIRpg(rpg, i))){
			x = getPosX(getPositionNpc(rpg->npc[i]));
			y = getPosY(getPositionNpc(rpg->npc[i]));
			setElementXYMap(rpg->map1, x, y, 1);
		}
		set = getObjectsObjective(getObjectiveQ(getQuestNpc(rpg->npc[i])));
		for(j=0;j<getNbObjSet(set);j++){
			if(getIdMap(rpg->map) == getRoomIdObject(getObjectIObjset(set, j))){
				if(isAcceptedNpc(getNpcIRpg(rpg, i))){
					x = getPosX(getPositionObject(getObjectIObjset(set, i)));
					y = getPosY(getPositionObject(getObjectIObjset(set, i)));
					setElementXYMap(rpg->map1, x, y, 1);
				}
				
			}
		}
	}

	for(i=0;i<rpg->nbMstr;i++){
		if(getIdMap(rpg->map) == getRoomIdMonsterRpg(rpg->monsters[i])){
			x = getPosX(getPositionMonsterRpg(rpg->monsters[i]));
			y = getPosY(getPositionMonsterRpg(rpg->monsters[i]));
			setElementXYMap(rpg->map1, x, y, 2);
		}
		
	}

	for(i=0;i<rpg->nbDoors;i++){
		if(getIdMap(rpg->map) == getRoomIdDoor(rpg->doors[i])){
			x = getPosX(getPositionDoor(rpg->doors[i]));
			y = getPosY(getPositionDoor(rpg->doors[i]));
			setElementXYMap(rpg->map1, x, y, 3);
		}
	}
}

void rpgFree(Rpg* rpg){
	int i;
	for(i=0;i<rpg->nbNpc;i++){
		npcDestroy(&rpg->npc[i]);
	}
	free(rpg->npc);
	if(rpg->map1 != NULL){
		mapDestroy(&rpg->map1);
	}
	characterDestroy(&rpg->player);
	for(i=0;i<rpg->nbMstr;i++){
		monsterRpgDestroy(&rpg->monsters[i]);
	}
	free(rpg->monsters);

	for(i=0;i<rpg->nbDoors;i++){
		doorDestroy(&(rpg->doors[i]));
	}
	free(rpg->doors);
}

int checkDoors(Rpg * rpg){
	int i, x, y, xD, yD;
	x = getPosX(getPositionCharacter(rpg->player));
	y = getPosY(getPositionCharacter(rpg->player));
	for(i=0;i<rpg->nbDoors;i++){
		if(getRoomIdDoor(rpg->doors[i]) == getIdMap(rpg->map)){
			xD = getPosX(getPositionDoor(rpg->doors[i]));
			yD = getPosY(getPositionDoor(rpg->doors[i]));
			if(x == xD && y == yD){
				changeLevelRpg(rpg, getMapDoor(rpg->doors[i]));
				setPositionCharacter(rpg->player, getPosX(getPosArrivalDoor(rpg->doors[i])), getPosY(getPosArrivalDoor(rpg->doors[i])));
				return 1;
			}
		}
		
	}
	return 0;
}

void rpgDestroy(Rpg** rpg){
	rpgFree(*rpg);
	free(*rpg);
	*rpg = NULL;
}

int getNbNpcRpg(Rpg * rpg){
	return rpg->nbNpc;
}

NPC* getNpcIRpg(const Rpg * rpg, int i){
	return rpg->npc[i];
}

int getNbMstrRpg(const Rpg * rpg){
	return rpg->nbMstr;
}

MonsterRpg* getMonsterRpgIRpg(const Rpg * rpg, int i){
	return rpg->monsters[i];
}


void rpgTest(){
	NPC * npc;
	// Character * player;
	Quest * quest;
	printf("==== Test of RPG ====\n");
	npc = npcCreate("SlimShady", "My name is what ?", 0);
	// player = characterCreate();
	quest = questCreate(0, "Test", 1, 1);
	setQuestNpc(npc, quest);

	// printf("Test of acceptQuest... ");
	// acceptQuest(player, npc);
	// assert(getNbQuestDiary(getDiaryCharacter(player)) == 1);
	// assert(getQuestIDiary(getDiaryCharacter(player), 0) == quest);
	// printf("Ok.\n");

	// characterDestroy(&player);
	npcDestroy(&npc);

	printf("Test of loadRpgFromFile... ");
	Rpg *rpg;
	rpg = loadRpgFromFile("data/Init/rpg.init");
	assert(rpg != NULL);
	assert(rpg->npc != NULL);
	assert(rpg->nbNpc == 1);
	assert(rpg->map != NULL);
	Position * pos;
	pos = getPositionNpc(rpg->npc[0]);
	assert(getPosX(pos) == 2);
	assert(getPosY(pos) == 5);
	printf("Ok.\n");
		

	printf("Test of rpgDestroy()... ");
	rpgDestroy(&rpg);
	assert(rpg == NULL);
	printf("Ok.\n");
	

	printf("==== The tests went well ==== \n\n");
}
