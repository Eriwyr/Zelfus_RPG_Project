#include "NPC.h"


void npcInit(NPC * npc, char* name, char* dialog, int id){

	npc->id = id;
	npc->name = strdup(name);
	npc->dialog = strdup(dialog);
	npc->quest = questCreate(0, "", 0, 0);
	npc->pos = malloc(sizeof(Position));
	setPosX(npc->pos, 0);
	setPosY(npc->pos, 0);
	npc->hasRewarded = 0;
	npc->roomId = 0;
}

void npcFree(NPC* npc){
	free(npc->name);
	free(npc->dialog);
	npc->name=NULL;
	npc->dialog=NULL;
	questDestroy(&npc->quest);
	free(npc->pos);
	
}

void setIdNpc(NPC* npc, int id){
	npc->id =id;
}

int getIdNpc(const NPC* npc){
	return npc->id;

}

void setQuestNpc(NPC * npc, Quest * quest){
	questDestroy(&npc->quest);
	npc->quest = quest;
}

NPC* npcCreate(char* name, char* dialog, int id){

	NPC* npc;

	npc = malloc(sizeof(NPC));
	npcInit(npc, name, dialog, id);
	return npc;
}

void npcDestroy(NPC** npc){
	npcFree(*npc);
	free(*npc);
	*npc=NULL;

}

char* getNameNpc(const NPC* npc){

	return(npc->name);	
}

char* getDialogNpc(const NPC* npc){

	return(npc->dialog);	
}

void setDialogNpc(NPC* npc, char* dialog){
	free(npc->dialog);
	npc->dialog = strdup(dialog);
}


Quest* getQuestNpc(const NPC* npc){
	return npc->quest;
}


int isAcceptedNpc(const NPC* npc){
	return npc->isAccepted;
}

void setAcceptedNpc(NPC* npc, const int isAccepted){
	assert(isAccepted>=0);
	assert(isAccepted<=1);
	npc->isAccepted = isAccepted;
}

int hasRewardedNpc(const NPC* npc){
	return npc->hasRewarded;
}

void setRewardedNpc(NPC* npc, const int hasRewarded){
	assert(hasRewarded>=0);
	assert(hasRewarded<=1);
	npc->hasRewarded = hasRewarded;
}


Position* getPositionNpc(const NPC* npc){
	return npc->pos;
}

void setPositionNpc(NPC* npc, int x, int y){
	setPosX(npc->pos, x);
	setPosY(npc->pos, y);
}

NPC* loadNPCFromFile(char* fileName){
	FILE* file;
	NPC* npc;
	int questId, id, isAccepted;
	char name[CHAR_SIZE_MAX];
	char dialog[CHAR_SIZE_MAX];
	char questFile[CHAR_SIZE_MAX];
	char questIdTxt[10];


	#ifdef WINDOWS_OS
		strreplace(fileName, '/', '\\');
	#endif

	file = fopen(fileName, "r");
	assert(file != NULL);


	fscanf(file, "id:%d\n", &id);
	fscanf(file, "name:");
	fgets(name, CHAR_SIZE_MAX, file);
	strremoveEOL(name);
	fscanf(file, "dialog:");
	fgets(dialog, CHAR_SIZE_MAX, file);
	strremoveEOL(dialog);
	npc = npcCreate(name, dialog, id);

	fscanf(file, "questId:%d\n", &questId);
	fscanf(file, "isAccepted:%d\n", &isAccepted);
	fscanf(file, "roomId:%d\n", &npc->roomId);
	sprintf(questIdTxt, "%d", questId);

	if(exist("data/Save/load.load")){
		strcpy(questFile, "data/Save/Quest/quest");
		strcat(questFile, questIdTxt);
		strcat(questFile, ".save");
	} else {
		strcpy(questFile, "data/Init/Quest/quest");
		strcat(questFile, questIdTxt);
		strcat(questFile, ".init");
	}
	


	setQuestNpc(npc, loadQuestFromFile(questFile));
	setAcceptedNpc(npc, isAccepted);

	fclose(file);
	return npc;
}

void saveNPCOnFile(NPC * npc, char* fileName){
	FILE * file;

	#ifdef WINDOWS_OS
		strreplace(fileName, "/", "\\");
	#endif

	char idQ[10];
	char questFile[CHAR_SIZE_MAX];

	file = fopen(fileName, "w+");

	fprintf(file, "id:%d\n", getIdNpc(npc));
	fprintf(file, "name:%s\n", npc->name);
	fprintf(file, "dialog:%s\n", npc->dialog);
	fprintf(file, "questId:%d\n", getIdQ(getQuestNpc(npc)));
	fprintf(file, "isAccepted:%d\n", npc->isAccepted);
	fprintf(file, "roomId:%d\n", npc->roomId);
	sprintf(idQ, "%d", getIdQ(getQuestNpc(npc)));
	strcpy(questFile, "data/Save/Quest/quest");
	strcat(questFile, idQ);
	strcat(questFile, ".save");
	saveQuestOnFile(getQuestNpc(npc), questFile);
	fclose(file);
}

int getRoomIdNpc(const NPC* npc){
	return npc->roomId;
}


void npcTest(){
	NPC npc;
	NPC * pNPC;
	printf("==== Tests of NPC ====\n");
	
	printf("Initializing using npcInit()... ");
	npcInit(&npc, "Non Player Character", "Hello", 0);
	assert(strcmp(npc.name, "Non Player Character") == 0);
	assert(strcmp(npc.dialog, "Hello") == 0);
	printf("Ok.\n");

	printf("Initializing using npcCreate()... ");
	pNPC = npcCreate("Non Player Character 2", "Hello again", 0);
	assert(strcmp(pNPC->name, "Non Player Character 2") == 0);
	assert(strcmp(pNPC->dialog, "Hello again") == 0);
	printf("Ok.\n");
	


	printf("Freeing npc... ");
	npcFree(&npc);
	printf("Ok.\n");

	printf("Freeing pNPC... ");
	npcDestroy(&pNPC);
	assert(pNPC == NULL);
	printf("Ok.\n");

	printf("Test of loadNPCFromFile()... ");
	NPC* pNPc1;
	pNPc1 = loadNPCFromFile("data/Init/NPC/npc1.init");
	npcDestroy(&pNPc1);
	printf("Ok.\n");
	

	printf("==== The tests went well ==== \n\n");
	
	
}

