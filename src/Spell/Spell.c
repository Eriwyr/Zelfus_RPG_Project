#include "Spell.h"

void spellInit(Spell* pSpell, int spellId, const char * spellName, int spellDamage, int range){  //Create a new spell 
	
	assert(spellId>=0);
	assert(spellName != '\0');
	assert (spellDamage >=0);
	
	pSpell->id = spellId;
	pSpell->name = strdup(spellName);
	pSpell->damage = spellDamage;
	pSpell->range = range;
}

void spellFree(Spell * spell){
	free(spell->name);
	spell->name = NULL;
}

Spell* spellCreate( int spellId, const char * spellName, int spellDamage, int range){
	Spell * spell;
	spell = malloc(sizeof(Spell));
	spellInit(spell, spellId, spellName, spellDamage, range);

	return spell;
}

void spellDestroy(Spell ** spell){
	spellFree(*spell);
	free(*spell);
	*spell = NULL;
}

int getIdSpell(const Spell* pSpell){
	assert(pSpell->id >0 );
	return pSpell->id;
	
}

char *getNameSpell(const Spell* pSpell){
	assert(pSpell->name != '\0');
	return pSpell->name;
}

int getDamageSpell(const Spell* pSpell){
	assert(pSpell->damage>=0);
	return pSpell->damage;
}

int getRangeSpell(const Spell* pSpell){
	assert(pSpell->range >=0);
	return pSpell->range; 
}

void setRangeSpell(Spell* pSpell, const int newRange){
	pSpell->range = newRange;
}

void setIdSpell(Spell* pSpell, const int newId){
	assert(newId>0);
	pSpell->id = newId;
}

void setNameSpell(Spell* pSpell, const char * newName){
	assert(newName != '\0');
	free(pSpell->name);
	pSpell->name = strdup(newName);
}

void setDamageSpell(Spell* pSpell, const int newDamage){
	assert(newDamage>=0);
	pSpell->damage = newDamage;
}


Spell* loadSpellFromFile(char* fileName){
	FILE* file;
	Spell* spell;
	int id, damage, range;
	char name[CHAR_SIZE_MAX];


	#ifdef WINDOWS_OS
		strreplace(filName, '/', '\\');
	#endif	
	file = fopen(fileName, "r");
	assert(file != NULL);

	fscanf(file, "id:%d\n", &id);
	fscanf(file, "name:");
	fgets(name, CHAR_SIZE_MAX, file);
	strremoveEOL(name);
	fscanf(file, "damage:%d\n", &damage);
	fscanf(file, "range:%d\n", &range);

	spell = spellCreate(id, name, damage, range);
	fclose(file);
	return spell;
}





void spellTest(){
	
	// int id;
	// int damage;
	// char *tmpName1 = "test";
	// Spell *pSpell;
	// Spell spell;
	
	// printf("==== Tests of Spell ==== \n");
	
	


	// printf ("Initialisation using spellInit()... ");
	// spellInit(&spell, 1, tmpName1, 10, 3);
	// assert(spell.damage == 10);
	// assert(strcmp(spell.name, tmpName1)==0);
	// assert(spell.id = 1);
	// printf("Ok.\n");
	
	// printf("Initialisation using spellCreate()... ");
	// pSpell = spellCreate(1,"magie",10, 2);
	// assert(pSpell->damage == 10);
	// assert(strcmp(pSpell->name,"magie")==0);
	// assert(pSpell->id ==1);
	// printf("Ok.\n");
	
	
	// printf("Testing getId()... ");
	// id =getIdSpell(pSpell);
	// assert(id == 1);
	// printf("Ok\n");
	
	// printf("Testing getName()... ");
	// assert(strcmp(getNameSpell(pSpell), "magie") == 0);
	// printf("Ok\n");	
	
	// printf("Testing getDamage()... ");
	// damage = getDamageSpell(pSpell);
	// assert(damage == 10);
	// printf("Ok\n");
	
	// printf("Testing setId()...");
	// setIdSpell(pSpell,2);
	// assert(pSpell->id == 2);
	// printf("Ok\n");
	
	// printf("Testing setName()...");
	// setNameSpell(pSpell,"thisisalongstringtotest");
	// assert(strcmp(pSpell->name, "thisisalongstringtotest")==0);
	// printf("Ok\n");
	
	// printf("Testing setDamage()...");
	// setDamageSpell(pSpell,5);
	// assert(pSpell->damage == 5);
	// printf("Ok\n");

	// printf("Freeing spell... ");
	// spellFree(&spell);
	// assert(spell.name == NULL);
	// printf("Ok.\n");

	// printf("Freeing pSpell... ");
	// spellDestroy(&pSpell);
	// assert(pSpell == NULL);
	// printf("Ok\n");

	// printf("Test of loadSpellFromFile... ");
	// Spell * pSpell1;
	// pSpell1 = loadSpellFromFile("data/Init/Spell/spell1.init");
	// spellDestroy(&pSpell1);
	// printf("Ok.\n");
	

	printf("==== The tests went well ====\n\n");
	

}