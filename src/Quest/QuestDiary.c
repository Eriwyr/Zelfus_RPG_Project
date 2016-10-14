#include "QuestDiary.h"
#include <assert.h>


void diaryInit(QuestDiary * diary){
	diary->nbQuests = 0;
	diary->size = 1;
	diary->quests = malloc(sizeof(Quest*));
}

void diaryFree(QuestDiary * diary){
	free(diary->quests);
	diary->quests = NULL;
	diary->nbQuests = 0;
}

QuestDiary *diaryCreate(){
	QuestDiary * diary;
	diary = malloc(sizeof(QuestDiary)); /*We create space for a questDiary object*/
	assert (diary != NULL);
	diaryInit(diary); /*We initialize*/

	return diary;
}

void diaryDestroy(QuestDiary ** diary){
	diaryFree(*diary);
	free(*diary);
	*diary = NULL;
}

Quest** getQuestDiary(const QuestDiary* diary){
	return diary->quests;
}

Quest* getQuestIDiary(const QuestDiary* diary, int i){
	assert(i>=0);
	assert(i<diary->nbQuests);
	return diary->quests[i];
}


void addQuest(QuestDiary * diary, Quest * newQuest){
	Quest ** tmpQuests; /*Temp quest to save the previous quests*/
	int i;
	if(diary->nbQuests == diary->size){ /*If we have as much quests as the number max of quests possible*/
		tmpQuests = diary->quests;
		diary->quests = malloc(2*diary->size*sizeof(Quest*)); /*We redefine a new array twice as big so we can store new quests*/
		for(i = 0; i<diary->size;i++){
			diary->quests[i] = tmpQuests[i]; /*We reintegrate the previous elements*/
		}
		/*We actualize the size*/
		diary->size = 2*diary->size;
		/*We free the memory*/
		free(tmpQuests);
	}
	/*We can now add the element because we made sure there is enough place*/
	diary->quests[diary->nbQuests] = newQuest;
	/*We increment the number of quests*/
	diary->nbQuests++;
}

void deleteQuest(QuestDiary * diary, int index){
	int j;
	/*Making sure that the index is < to the number of quests and > 0 */
	assert(index <= diary->nbQuests);
	assert(index >= 0);
	  
	for(j = index-1; j<diary->nbQuests-1;j++){ /*We start the loop from the index ( minus one to keep first element at index 1 )*/
		questDestroy(&diary->quests[j]);
		diary->quests[j] = diary->quests[j+1]; /*Each elements is then shifted from 1*/
	}
	diary->nbQuests--; /*There is now one element less*/

	/*We redifine the size once there is enough free slots*/
	if(diary->nbQuests < (diary->size / 3)){
		Quest ** tmp = diary->quests; /*We save the current quests*/
		diary->size = diary->size / 2;
		diary->quests = malloc(diary->size*sizeof(Quest)); /*We reallocate memory*/
		for(j=0;j<diary->nbQuests;j++){
			diary->quests[j] = tmp[j]; /*Restoration of the saved quests*/
		}
		free(tmp);
	}
} 

int getNbQuestDiary(const QuestDiary * diary){
	return diary->nbQuests;
}

int getIndexById(const QuestDiary * diary, int id){
	int i;
	for(i = 0;i<diary->nbQuests;i++){
		if(getIdQ(diary->quests[i]) == id)
			return i;
	}
	return -1;
}

int getIdFromQuest(const QuestDiary * diary, Quest * quest){
	int i;
	for(i=0;i<diary->nbQuests;i++){
		if(getQuestIDiary(diary, i) == quest)
			return i;
	}
	return -1;
}

QuestDiary* loadQuestDiaryFromFile(char* fileName){
	FILE* file;
	QuestDiary* diary;
	int i, nbQuests, questId;
	char questIdTxt[10];
	char questFile[CHAR_SIZE_MAX];

	#ifdef WINDOWS_OS
		strreplace(fileName, '/', '\\');
	#endif

	file = fopen(fileName, "r");
	assert(file != NULL);
	
	diary = diaryCreate();
	fscanf(file, "size:%d\n", &diary->size);
	fscanf(file, "nbQuests:%d\n", &nbQuests);
	for(i = 0;i<nbQuests;i++){
		fscanf(file, "QuestId:%d\n", &questId);
		if(exist("data/Save/load.load")){
			strcpy(questFile, "data/Save/Quest/quest");
			sprintf(questIdTxt, "%d", questId);
			strcat(questFile, questIdTxt);
			strcat(questFile, ".save");
		} else {
			strcpy(questFile, "data/Init/Quest/quest");
			sprintf(questIdTxt, "%d", questId);
			strcat(questFile, questIdTxt);
			strcat(questFile, ".init");
		}
		
		addQuest(diary, loadQuestFromFile(questFile));
	}
	fclose(file);
	return diary;
}

void saveQuestDiaryOnFile(QuestDiary* diary, char* fileName){
	FILE* file;
	int i;
	char questFile[CHAR_SIZE_MAX];
	char idQ[10];
	#ifdef WINDOWS_OS
		strreplace(fileName, "/", "\\");
	#endif
	file = fopen(fileName, "w+");
	assert(file != NULL);

	fprintf(file, "size:%d\n", diary->size);
	fprintf(file, "nbQuests:%d\n", diary->nbQuests);

	for(i=0;i<diary->nbQuests;i++){
		strcpy(questFile, "data/Save/Quest/quest");
		sprintf(idQ, "%d", getIdQ(diary->quests[i]));
		strcat(questFile, idQ);
		strcat(questFile, ".save");
		saveQuestOnFile(diary->quests[i], questFile);
		fprintf(file, "QuestId:%d\n", getIdQ(diary->quests[i]));
	}

	fclose(file);
}





void diaryTest(){
	QuestDiary diary;
	QuestDiary *diary1;
	printf("==== Tests of DiaryQuest ==== \n");

	printf("Initialisation using diaryInit()... ");
	diaryInit(&diary);
	assert(diary.nbQuests == 0);
	assert(diary.size == 1);
	assert(sizeof(diary.quests) == sizeof(diary.size*sizeof(Quest)));
	printf("Ok.\n");

	printf("Initialisation using diaryCreate()... ");
	diary1 = diaryCreate();
	assert(diary1->size == 1);
	assert(diary1->nbQuests == 0);
	assert(sizeof(diary1->quests) == sizeof(diary1->size*sizeof(Quest)));
	printf("Ok.\n");


	/*printf("AddQuest test... ");*/

	printf("Freeing diary... ");
	diaryFree(&diary);
	assert (diary.quests == NULL);
	printf("Ok.\n");

	printf("Freeing diary1... ");
	diaryDestroy(&diary1);
	assert(diary1 == NULL);
	printf("Ok\n");

	printf("==== The tests went well ====\n\n");

}

