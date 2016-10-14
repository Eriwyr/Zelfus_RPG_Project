#include "Quest.h"

void questInit(Quest * quest,int id, const char* name, int nbMstr, int nbObj){
	assert(name != NULL);
	assert(nbMstr >= 0);
	assert(nbObj >= 0); 
	quest->name = strdup(name); /*strdup reallocate suffisent memory and copy name into name*/
	quest->id = id;
	quest->isAccomplished = 0;
	quest->reward = rewardCreate(0, 0);
	quest->objective = objectiveCreate(nbMstr, nbObj);

}

Quest* questCreate(int id, const char* name, int nbMstr, int nbObj){
	Quest* quest;
	quest = malloc(sizeof(Quest));
	questInit(quest, id, name, nbMstr, nbObj);

	return quest;
}


int checkIsFinishQuest(Quest * quest){
	int nbObj, nbMstr;
	nbObj = getNbObjSet(getObjectsObjective(getObjectiveQ(quest)));
	nbMstr= getNbMstrObjective(getObjectiveQ(quest));
	if(nbObj == 0 && nbMstr == 0){
		return 1;
	}
	return 0;
}

void questFree(Quest * quest){
	free(quest->name);
	quest->name = NULL;
	quest->isAccomplished = 0;
	rewardDestroy(&quest->reward);
	quest->reward = NULL;
	objectiveDestroy(&quest->objective);
	quest->objective = NULL;
	
}

void questDestroy(Quest ** quest){
	questFree(*quest);
	free(*quest);
	*quest = NULL;
}



void setObjectiveQ(Quest * quest, Objective * newObjective){
	objectiveDestroy(&(quest->objective));
	quest->objective = newObjective;
}


void setRewardQ(Quest * quest, Reward * newReward){
	rewardDestroy(&(quest->reward));
	quest->reward = newReward;
}

int getIdQ(const Quest * quest){
	return quest->id;
}

Objective * getObjectiveQ(const Quest * quest){
	return quest->objective;
}

Reward * getRewardQ(const Quest * quest){
	return quest->reward;
}

int isAccomplished(const Quest * quest){
	return quest->isAccomplished;
}

void questFinish(Quest * quest){
	quest->isAccomplished = 1;
}

char* getNameQ(const Quest * quest){
	return quest->name;
}

void setNameQ(Quest * quest, const char* newName){
	assert(newName != NULL);
	free(quest->name);
	quest->name = NULL;
	quest->name = strdup(newName);

}

Quest* loadQuestFromFile(char* fileName){
	FILE* file;
	Quest * quest;
	char name[CHAR_SIZE_MAX];
	int nbObj, nbMstr, id, xp, money, roomId, isAccomplished;
	int i, idO;
	char nameO[CHAR_SIZE_MAX];
	char typeO[CHAR_SIZE_MAX];


	#ifdef WINDOWS_OS
		strreplace(fileName, '/', '\\');
	#endif
		
	file = fopen(fileName, "r");
	assert(file != NULL);

	
	fscanf(file, "#nbObj : %d\n", &nbObj);
	fscanf(file, "#nbMstr : %d\n", &nbMstr);
	fscanf(file, "name:");
	fgets(name, CHAR_SIZE_MAX, file);
	strremoveEOL(name);
	fscanf(file, "id:%d\n", &id);
	quest = questCreate(id, name, nbMstr, nbObj);

	Reward * reward;
	fscanf(file, "xp:%d\n", &xp);
	fscanf(file, "money:%d\n", &money);
	fscanf(file, "isAccomplished:%d\n", &isAccomplished);
	if(isAccomplished == 1)
		questFinish(quest);
	reward = rewardCreate(xp, money);
	setRewardQ(quest, reward);
	Position pos;
	
	for(i=0; i<nbObj;i++){
		fscanf(file, "Object:\n");
		fscanf(file, "id:%d\n", &idO);
		fscanf(file, "name:");
		fgets(nameO, CHAR_SIZE_MAX, file);
		strremoveEOL(nameO);
		fscanf(file, "type:");
		fgets(typeO, CHAR_SIZE_MAX, file);
		strremoveEOL(typeO);
		fscanf(file, "RoomId:%d\n", &roomId);
		fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
		addQuestObject(getObjectsObjective(quest->objective), questObjectCreate(idO, nameO, typeO, pos.x, pos.y, roomId));
	}



	fclose(file);
	return quest;
}

void saveQuestOnFile(Quest * quest, char* fileName){
	FILE* file;
	int i;
	QuestObject * object;
	#ifdef WINDOWS_OS
		strreplace(fileName, "/", "\\");
	#endif

	file = fopen(fileName, "w+");
	fprintf(file, "#nbObj:%d\n", getNbObjSet(getObjectsObjective(quest->objective)));
	fprintf(file, "#nbMstr:%d\n\n", getNbMstrObjective(quest->objective));
	fprintf(file, "name:%s\n", getNameQ(quest));
	fprintf(file, "id:%d\n", getIdQ(quest));
	fprintf(file, "xp:%d\n", getXpReward(quest->reward));
	fprintf(file, "money:%d\n\n", getMoneyReward(quest->reward));
	fprintf(file, "isAccomplished:%d\n", quest->isAccomplished);
	fprintf(file, "\n");
	fprintf(file, "Object:\n");
	for(i=0;i<getNbObjSet(getObjectsObjective(quest->objective));i++){
		object = getObjectIObjset(getObjectsObjective(quest->objective), i);
		fprintf(file, "id:%d\n", getIdObject(object));
		fprintf(file, "name:%s\n", getNameObject(object));
		fprintf(file, "type:%s\n", getTypeObject(object));
		fprintf(file, "RoomId:%d\n", getRoomIdObject(object));
		fprintf(file, "x:%d  y:%d\n", getPosX(getPositionObject(object)), getPosY(getPositionObject(object)));
	}

	fclose(file);
}

void questTest(){
	Quest quest;
	Quest * pQuest;
	char * tmp = "test";
	char * tmp2 = "anothertest";
	Objective *obj;
	QuestObject * object;
	Reward * rew;

	printf("\n==== Tests of Quest ==== \n");

	printf("Initialisation using questInit()... ");
	questInit(&quest, 1, tmp, 2, 5);
	assert(quest.id == 1);
	assert(strcmp(quest.name, tmp) == 0); /* We check if the strings are the same*/
	assert(quest.isAccomplished == 0);
	assert(getXpReward(quest.reward) == 0);
	printf("Ok.\n");

	printf("Initialisation using questCreate()... ");
	pQuest = questCreate(2, "Quest", 2, 3);
	assert(pQuest->id == 2);
	assert(strcmp(pQuest->name, "Quest") == 0);
	assert(pQuest->isAccomplished == 0);
	assert(sizeof(*pQuest) == sizeof(Quest));
	printf("Ok.\n");

	printf("Test of setObjectiveQ()... ");
	obj = objectiveCreate(3, 1);
	object = questObjectCreate(1, "name", "type", 1, 1, 0);
	addQuestObject(getObjectsObjective(obj), object);
	setIdObject(*getObjectObjset(getObjectsObjective(obj)), 1);
	setObjectiveQ(&quest, obj);
	assert(getIdObject(*getObjectObjset(getObjectsObjective(quest.objective))) == 1);
	printf("Ok.\n");

	printf("Test of setRewardQ()... ");
	rew = rewardCreate(0, 5);
	setRewardQ(&quest, rew);
	assert(quest.reward == rew);
	printf("Ok.\n");

	printf("Test of getIdQ()... ");
	assert(getIdQ(&quest) == 1);
	printf("Ok.\n");

	printf("Test of isAccomplished()... ");
	assert(isAccomplished(&quest) == 0);
	printf("Ok.\n");

	printf("Test of questFinish()... ");
	questFinish(&quest);
	assert(isAccomplished(&quest) == 1);
	printf("Ok.\n");

	printf("Test of getNameQ()... ");
	assert(strcmp(getNameQ(&quest), tmp) == 0);
	printf("Ok.\n");

	printf("Test of setNameQ()... ");
	setNameQ(&quest, tmp2);
	assert(strcmp(getNameQ(&quest), tmp2) == 0);
	printf("Ok.\n");

	printf("Freeing quest... ");
	questFree(&quest);
	assert(quest.name == NULL);
	printf("Ok.\n");



	printf("Freeing pQuest... ");
	questDestroy(&pQuest);
	assert(pQuest == NULL);
	printf("Ok.\n");


	printf("Test of loadQuestFromFile()... ");
	Quest * pQuest1;
	pQuest1 = loadQuestFromFile("data/Init/Quest/quest1.init");
	assert(pQuest1 != NULL);
	printf("Ok.\n");

	printf("==== The tests went well ==== \n\n");

	questDestroy(&pQuest1);


}

