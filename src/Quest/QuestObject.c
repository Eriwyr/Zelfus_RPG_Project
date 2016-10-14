#include "QuestObject.h"

void questObjectInit(QuestObject * object, int id, char * name, char * type, int x, int y, int roomId){
	object->id = id;
	object->name = strdup(name); /*to be freed !!!!! (hiden malloc in strdup*/
	object->type = strdup(type); /*To be freed !!!!!*/
	object->pos = malloc(sizeof(Position));
	setPosX(object->pos, x);
	setPosY(object->pos, y);
	object->roomId = roomId;
}

void questObjectFree(QuestObject * object){
	free(object->name);
	object->name = NULL;
	free(object->type);
	object->type = NULL;
	free(object->pos);
}

QuestObject* questObjectCreate(int id, char * name, char * type, int x, int y, int roomId){
	QuestObject * object;
	object = malloc(sizeof(QuestObject));

	questObjectInit(object, id, name, type, x, y, roomId);
	return object;
} 

void questObjectDestroy(QuestObject ** object){
	questObjectFree(*object);
	free(*object);
	*object = NULL;
}

int getIdObject(const QuestObject * object){
	return object->id;
}

void setIdObject(QuestObject* object, const int id){
	object->id = id;
}


int getRoomIdObject(const QuestObject* object){
	return object->roomId;
}

void setRoomIdObject(QuestObject* object, const int roomId){
	object->roomId = roomId;
}




char* getNameObject(const QuestObject * object){
	return object->name;
}

char* getTypeObject(const QuestObject * object){
	return object->type;
}


Position* getPositionObject(const QuestObject* object){
	return object->pos;
}

void setPositionObject(QuestObject* object, int x, int y){
	setPosX(object->pos, x);
	setPosY(object->pos, y);
}



void questObjectTest(){
	QuestObject * pObject;
	QuestObject object;
	printf("==== Tests of QuestObject ==== \n");

	printf("Initialisation using questObjectInit()... ");
	questObjectInit(&object, 1, "object", "type", 1, 1, 0);
	assert(object.id == 1);
	assert(strcmp(object.name, "object") == 0);
	assert(strcmp(object.type, "type") == 0);
	printf("Ok.\n");

	printf("Initialisation using questObjectCreate()... ");
	pObject = questObjectCreate(2, "object2", "type2", 1, 1, 0);
	assert(pObject->id == 2);
	assert(strcmp(pObject->name, "object2") == 0);
	assert(strcmp(pObject->type, "type2") == 0);
	printf("Ok.\n");

	printf("Freeing object... ");
	questObjectFree(&object);
	assert(object.name == NULL);
	assert(object.type == NULL);
	printf("Ok.\n");

	printf("Freeing pObject... ");
	questObjectDestroy(&pObject);
	assert(pObject == NULL);
	printf("Ok.\n");

	printf("==== The tests went well ====\n\n");
}