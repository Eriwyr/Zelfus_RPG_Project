#include "ObjectSet.h"

void objsetInit(ObjectSet * objset, int nbObj){
	assert(nbObj >= 0);
	objset->nbObj = 0;
	objset->size = nbObj;
	objset->objects = malloc(nbObj*sizeof(QuestObject*));
}

void objsetFree(ObjectSet * objset){
	int i;
	for(i=0;i<objset->nbObj;i++){
		if(objset->objects[i] != NULL)
			questObjectDestroy(&(objset->objects[i]));
	}
	free(objset->objects);
	objset->objects = NULL;
	objset->nbObj = 0;
}

ObjectSet *objsetCreate(int nbObj){
	assert(nbObj>=0);
	ObjectSet * objset;
	objset = malloc(sizeof(ObjectSet)); /*We create space for a objset object*/
	assert (objset != NULL);
	objsetInit(objset, nbObj); /*We initialize*/

	return objset;
}

void objsetDestroy(ObjectSet ** objset){
	objsetFree(*objset);
	free(*objset);
	*objset = NULL;
}

void addQuestObject(ObjectSet * objset, QuestObject * newQuestObject){
	if(objset->nbObj < objset->size){
		objset->objects[objset->nbObj] = newQuestObject;
		objset->nbObj++;
	}


}

void removeQuestObject(ObjectSet * objset, int ind){
	int j;
	/*Making sure that the ind is <= to the number of objects and > 0 */
	assert(ind <= objset->nbObj);
	assert(ind > 0);
	for(j = ind-1; j<(objset->nbObj-1);j++){ /*We start the loop from the ind ( minus one to keep first element at ind 1 )*/
		objset->objects[j] = objset->objects[j+1]; /*Each elements is then shifted from 1*/
	}
	objset->nbObj--; /*There is now one element less*/

	/*We redifine the size*/

	QuestObject ** tmp = objset->objects; /*We save the current objects*/
	objset->size--;
	objset->objects = malloc(objset->size*sizeof(QuestObject*)); /*We reallocate memory*/
	for(j=0;j<objset->nbObj;j++){
		objset->objects[j] = tmp[j]; /*Restoration of the saved objects*/
	}
	free(tmp);
}

int getNbObjSet(const ObjectSet * objset){
	return objset->nbObj;
}

QuestObject** getObjectObjset(const ObjectSet * objset){
	return objset->objects;
}

QuestObject* getObjectIObjset(const ObjectSet * objset, int i){
	assert(i >= 0);
	assert(i < objset->nbObj);
	return objset->objects[i];
}

int getIdFromObject(ObjectSet * objset, QuestObject * object){
	int i;
	for(i=0;i<objset->nbObj;i++){
		if(getObjectIObjset(objset, i) == object)
			return i;
	}
	return -1;
}


void objsetTest(){
	ObjectSet objset;
	ObjectSet *pObjset;
	QuestObject objectTest;
	QuestObject ** pObject;
	objectTest.id = 0;
	printf("==== Tests of QuestObjectSet ==== \n");

	printf("Initialisation using objsetInit()... ");
	objsetInit(&objset, 1);
	assert(objset.nbObj == 0);
	assert(objset.size == 1);
	assert(sizeof(objset.objects) == sizeof(objset.size*sizeof(QuestObject*)));
	printf("Ok.\n");

	printf("Initialisation using objsetCreate()... ");
	pObjset = objsetCreate(2);
	assert(pObjset->size == 2);
	assert(pObjset->nbObj == 0);
	assert(sizeof(pObjset->objects) == sizeof(pObjset->size*sizeof(QuestObject*)));
	printf("Ok.\n");


	printf("Test of addQuestObject()... ");
	questObjectInit(&objectTest, 1, "test", "typeTest", 1, 1, 0);
	addQuestObject(pObjset, &objectTest);
	assert(pObjset->nbObj == 1);
	assert(strcmp(getNameObject(pObjset->objects[0]), getNameObject(&objectTest)) == 0);
	assert(strcmp(getTypeObject(pObjset->objects[0]), getTypeObject(&objectTest)) == 0);
	assert(getIdObject(pObjset->objects[0]) == objectTest.id);
	printf("Ok.\n");

	printf("Test of getQuestObject()... ");
	pObject = getObjectObjset(pObjset);
	assert(strcmp(getNameObject(pObject[0]), getNameObject(&objectTest)) == 0);
	printf("Ok.\n");


	printf("Test of removeQuestObject()... ");
	removeQuestObject(pObjset, 1);
	assert(pObjset->size == 1);
	printf("Ok.\n");

	printf("Freeing objset... ");
	objsetFree(&objset);
	assert (objset.objects == NULL);
	printf("Ok.\n");

	printf("Freeing pObjset... ");
	objsetDestroy(&pObjset);
	assert(pObjset == NULL);
	printf("Ok\n");

	printf("==== The tests went well ====\n\n");

	questObjectFree(&objectTest);
}