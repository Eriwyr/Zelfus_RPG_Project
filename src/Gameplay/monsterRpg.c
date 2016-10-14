#include "monsterRpg.h"

void monsterRpgInit(MonsterRpg * monsterRpg){
	monsterRpg->fight = fightCreate();
	monsterRpg->idRoom = 0;
	monsterRpg->id = 0;
	monsterRpg->pos = malloc(sizeof(Position));
}

void monsterRpgFree(MonsterRpg * monsterRpg){
	free(monsterRpg->pos);
	fightDestroy(&monsterRpg->fight);
}

MonsterRpg* monsterRpgCreate(){
	MonsterRpg * monsterRpg;
	monsterRpg = malloc(sizeof(MonsterRpg));
	monsterRpgInit(monsterRpg);

	return monsterRpg;
}

void monsterRpgDestroy(MonsterRpg ** monsterRpg){
	monsterRpgFree(*monsterRpg);
	free(*monsterRpg);
	*monsterRpg = NULL;
}


MonsterRpg* loadMonsterRpgFromFile(char* fileName, Character* player){
	FILE* file;
	MonsterRpg* monsterRpg;
	int idRoom;
	int idFight;
	char fightIdText[10];
	char fightFile[CHAR_SIZE_MAX];
	int x, y;

	#ifdef WINDOWS_OS
		strreplace(filName, '/', '\\');
	#endif
	
	file = fopen(fileName, "r");
	assert(file != NULL);
	strcpy(fightFile, "data/Init/Fight/fight");
	monsterRpg = monsterRpgCreate();
	fscanf(file, "id : %d\n", &monsterRpg->id);
	fscanf(file, "idFight : %d\n", &idFight);
	sprintf(fightIdText, "%d", idFight);
	strcat(fightFile, fightIdText);
	strcat(fightFile, ".init");
	fscanf(file, "idRoom : %d\n", &idRoom);
	fscanf(file, "x:%d  y:%d", &x, &y);

	free(monsterRpg->fight);
	monsterRpg->fight = loadFightFromFile(fightFile, player);
	monsterRpg->idRoom = idRoom;
	setPosX(monsterRpg->pos, x);
	setPosY(monsterRpg->pos, y);

	fclose(file);
	
	return monsterRpg;
}

void saveMonsterRpgOnFile(MonsterRpg* monsterRpg, char* fileName){
	FILE* file;

	file = fopen(fileName, "w+");

	fprintf(file, "id : %d\n", monsterRpg->id);
	fprintf(file, "idFight : %d\n", getIdFight(monsterRpg->fight));
	fprintf(file, "idRoom : %d\n", monsterRpg->idRoom);
	fclose(file);
}


void setPositionMonsterRpg(MonsterRpg* monsterRpg, int x, int y){
	setPosX(monsterRpg->pos, x);
	setPosY(monsterRpg->pos, y);
}

Position* getPositionMonsterRpg(const MonsterRpg* monsterRpg){
	return monsterRpg->pos;
}

Fight* getFightMonsterRpg(const MonsterRpg* monsterRpg){
	return monsterRpg->fight;
}


int getIdMonsterRpg(const MonsterRpg* monsterRpg){
	return monsterRpg->id;
}

void setIdMonsterRpg(MonsterRpg* monsterRpg, const int id){
	monsterRpg->id = id;
}

int getRoomIdMonsterRpg(const MonsterRpg* monsterRpg){
	return monsterRpg->idRoom;
}

