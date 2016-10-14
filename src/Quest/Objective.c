#include "Objective.h"

void objectiveInit(Objective * obj, int nbMstr, int nbOjct){
	assert(nbMstr >= 0);
	assert(nbOjct >= 0);
	// obj->horde = hordeCreate(nbMstr);
	obj->nbMstr = nbMstr;
	obj->objects = objsetCreate(nbOjct);
	
}

void objectiveFree(Objective * obj){
	// hordeDestroy(&(obj->horde));
	obj->nbMstr = 0;
	objsetDestroy(&(obj->objects));
}

Objective *objectiveCreate(int nbMstr, int nbOjct){
	assert(nbMstr >= 0);
	assert(nbOjct >= 0);
	Objective * obj;
	obj = malloc(sizeof(Objective));
	assert(obj != NULL);

	objectiveInit(obj, nbMstr, nbOjct);
	return obj;

}

void objectiveDestroy(Objective ** obj){
	objectiveFree(*obj);
	free(*obj);
	*obj = NULL;
}
int getNbMstrObjective(const Objective * obj){
	return obj->nbMstr;
}

void setNbMstrObjective(Objective * obj, int value){
	obj->nbMstr = value;
}

ObjectSet* getObjectsObjective(const Objective* obj){
	return obj->objects;
}

void objectiveTest(){
	Objective obj;
	Objective* pObj;

	pObj = NULL;
	printf("==== Tests of Objective ==== \n");

	printf("Initialisation using objectiveInit()... ");
	objectiveInit(&obj, 10, 15);
	assert(obj.nbMstr == 10);
	assert(obj.objects != NULL);
	printf("Ok.\n");

	printf("Free using objectiveFree... ");
	objectiveFree(&obj);
	assert(obj.objects == NULL);
	printf("Ok.\n");

	printf("Test of objectiveCreate... ");
	pObj = objectiveCreate(5, 9);
	assert(pObj != NULL);
	assert(sizeof(*pObj) == sizeof(Objective));
	printf("Ok.\n");

	printf("Test of objectiveDestroy... ");
	objectiveDestroy(&pObj);
	assert(pObj == NULL);
	printf("Ok\n");

	printf("==== The tests went well ==== \n\n");
}

