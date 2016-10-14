#include "Monster.h"

void monsterInit(Monster * monster, const char * name){
	monster->name = strdup(name); /*To be freed*/
	monster->weapon = weaponCreate("Default", 1, 2, 1, 5, 3, 0); /*To be freed*/
	monster->spellBar = spellBarCreate(); /*to be freed*/
	monster->pos = malloc(sizeof(Position)); /*to be freed*/
	setPosX(monster->pos, 0);
	setPosY(monster->pos, 0);
	monster->lifePoints = 15;
	monster->strength = 25;
	monster->intelligence = 11;
	monster->strengthRes = 10;
	monster->intellRes = 5;
}

Monster* monsterCreate(const char * name){
	Monster * monster;
	monster = malloc(sizeof(Monster));

	monsterInit(monster, name);
	return monster;
}

void monsterDestroy(Monster ** monster){
	monsterFree(*monster);
	free(*monster);
	*monster = NULL;
}

void monsterFree(Monster * monster){
	free(monster->name);
	monster->name = NULL;

	weaponDestroy(&monster->weapon);
	monster->weapon = NULL;

	spellBarDestroy(&monster->spellBar);
	monster->spellBar = NULL;

	free(monster->pos);
	monster->pos = NULL;

}

Monster* loadMonsterFromFile(char* fileName){
	FILE* file;
	Monster * monster;
	int idW;
	char name[CHAR_SIZE_MAX];
	char idWTxt[10];
	char fileW[CHAR_SIZE_MAX];

	#ifdef WINDOWS_OS
		strreplace(fileName, '/', '\\');
	#endif
		
	file = fopen(fileName, "r");
	assert(file != NULL);

	monster = monsterCreate(" ");

	

	fscanf(file, "id:%d\n", &monster->id);
	fscanf(file, "name:");
	fgets(name, CHAR_SIZE_MAX, file);
	strremoveEOL(name);
	setNameMonster(monster, name);
	fscanf(file, "lifePoints:%d\n", &monster->lifePoints);
	fscanf(file, "strength:%d\n", &monster->strength);
	fscanf(file, "intelligence:%d\n", &monster->intelligence);
	fscanf(file, "strengthRes:%d\n", &monster->strengthRes);
	fscanf(file, "intellRes:%d\n", &monster->intellRes);
	fscanf(file, "weaponId:%d\n", &idW);


	strcpy(fileW, "data/Init/Weapon/weapon");
	sprintf(idWTxt, "%d", idW);
	strcat(fileW, idWTxt);
	strcat(fileW, ".init");
	setWeaponMonster(monster, loadWeaponFromFile(fileW));



	fclose(file);
	return monster;
}

char* getNameMonster(const Monster * monster){
	return monster->name;
}

void setNameMonster(Monster * monster, const char* name){
	free(monster->name);
	monster->name = strdup(name);
}

int getLifePointsMonster(const Monster * monster){
	return monster->lifePoints;
}

void setLifePointsMonster(Monster * monster, int lifePoints){
	monster->lifePoints = lifePoints;
}

int getStrengthMonster(const Monster * monster){
	return monster->strength;
}

void setStrengthMonster(Monster * monster, int strength){
	monster->strength = strength;
}

int getIntelligenceMonster(const Monster * monster){
	return monster->intelligence;
}

void setIntelligenceMosnter(Monster * monster, int intelligence){
	monster->intelligence = intelligence;
}

int getStrengthResMonster(const Monster * monster){
	return monster->strengthRes;
}

void setStrengthResMonster(Monster * monster, int strengthRes){
	monster->strengthRes = strengthRes;
}

int getIntellResMonster(const Monster * monster){
	return monster->intellRes;
}

void setIntellResMonster(Monster * monster, int intellRes){
	monster->intellRes = intellRes;
}

SpellBar* getSpellBarMonster(const Monster * monster){
	return monster->spellBar;
}

void setSpellBarMonster(Monster * monster, SpellBar* spellBar){
	spellBarDestroy(&monster->spellBar);
	monster->spellBar = spellBar;
}

Weapon* getWeaponMonster(const Monster * monster){
	return monster->weapon;
}

void setWeaponMonster(Monster * monster, Weapon * weapon){
	weaponDestroy(&monster->weapon);
	monster->weapon = weapon;
}

Position* getPositionMonster(const Monster * monster){
	return monster->pos;
}

void setPositionMonster(Monster * monster, int x, int y){
	setPosX(monster->pos, x);
	setPosY(monster->pos, y);
}

int getIdMonster(const Monster* monster){
	return monster->id;
}

void setIdMonster(Monster* monster, const int id){
	monster->id = id;
}

void  monsterTest(){
	Monster monster;
	Monster * pMonster;
	SpellBar* spellBar, *spellBar1;
	Spell * spell;
	Weapon * weapon;
	Position * pos;

	printf("==== Test of Monster ====\n");

	printf("Initalisation using monsterInit()... ");
	monsterInit(&monster, "Test");
	assert(strcmp(monster.name, "Test") == 0);
	assert(monster.weapon != NULL);
	assert(monster.spellBar != NULL);
	printf("Ok.\n");

	printf("Initalisation using monsterCreate()... ");
	pMonster = monsterCreate("Test2");
	assert(strcmp(pMonster->name, "Test2") == 0);
	assert(pMonster->weapon != NULL);
	assert(pMonster->spellBar != NULL);
	printf("Ok.\n");

	printf("Test of getNameMonster()... ");
	assert(strcmp(getNameMonster(pMonster), "Test2") == 0);
	printf("Ok.\n");

	printf("Test of setNameMonster()... ");
	setNameMonster(pMonster, "Thisisaverylongsentencetotest");
	assert(strcmp(getNameMonster(pMonster), "Thisisaverylongsentencetotest") == 0);
	printf("Ok.\n");

	printf("Test of getLifePointsMonster()... ");
	assert(getLifePointsMonster(pMonster) == 15);
	printf("Ok.\n");

	printf("Test of setLifePointsMonster()... ");
	setLifePointsMonster(pMonster, 100);
	assert(getLifePointsMonster(pMonster) == 100);
	printf("Ok.\n");

	printf("Test of getStrengthMonster()... ");
	assert(getStrengthMonster(pMonster) == 25);
	printf("Ok.\n");

	printf("Test of setStrengthMonster()... ");
	setStrengthMonster(pMonster, 50);
	assert(getStrengthMonster(pMonster) == 50);
	printf("Ok.\n");


	printf("Test of getIntelligenceMonster()... ");
	assert(getIntelligenceMonster(pMonster) == 11);
	printf("Ok.\n");

	printf("Test of setIntelligenceMonster()... ");
	setStrengthMonster(pMonster, 23);
	assert(getStrengthMonster(pMonster) == 23);
	printf("Ok.\n");

	printf("Test of getStrengthResMonster()... ");
	assert(getStrengthResMonster(pMonster) == 10);
	printf("Ok.\n");

	printf("Test of setStrengthResMonster()... ");
	setStrengthResMonster(pMonster, 12);
	assert(getStrengthResMonster(pMonster) == 12);
	printf("Ok.\n");

	printf("Test of getIntellResMonster()... ");
	assert(getIntellResMonster(pMonster) == 5);
	printf("Ok.\n");

	printf("Test of setIntellResMonster()... ");
	setIntellResMonster(pMonster, 251);
	assert(getIntellResMonster(pMonster) == 251);
	printf("Ok.\n");

	printf("Test of getSpellBarMonster()... ");
	spellBar = getSpellBarMonster(pMonster);
	assert(pMonster->spellBar == spellBar);
	printf("Ok.\n");

	printf("Test of setSpellBarMonster()... ");

	spellBar1 = spellBarCreate();
	spell = spellCreate(1, "spellName", 14, 1);
	addSpell(spellBar1, spell);
	setSpellBarMonster(pMonster, spellBar1);
	assert(getIdSpell(getSpell(getSpellBarMonster(pMonster), 0)) == 1);
	
	assert(strcmp(getNameSpell(getSpell(getSpellBarMonster(pMonster), 0)), "spellName") == 0);
	assert(getDamageSpell(getSpell(getSpellBarMonster(pMonster), 0)) == 14);
	printf("Ok.\n");

	printf("Test of getWeaponMonster()... ");
	weapon = getWeaponMonster(pMonster);
	assert(pMonster->weapon = weapon);
	printf("Ok.\n");

	printf("Test of setWeaponMonster()... ");
	weaponFree(weapon);
	weapon = weaponCreate("The Destroyer", 14, 12, 10, 9, 2, 1);
	setWeaponMonster(pMonster, weapon);
	assert(strcmp(getNameWeapon(getWeaponMonster(pMonster)), "The Destroyer") == 0);
	assert(getDamageWeapon(getWeaponMonster(pMonster)) == 14); /*We respect encapsulation*/
	assert(getStrengthWeapon(getWeaponMonster(pMonster)) == 12); 
	assert(getIntelligenceWeapon(getWeaponMonster(pMonster)) == 10);
	assert(getWisdomWeapon(getWeaponMonster(pMonster)) == 9);
	printf("Ok.\n");

	printf("Test of getPositionMonster()... ");
	pos = getPositionMonster(pMonster);
	assert(pMonster->pos == pos);
	printf("Ok.\n");

	printf("Test of setPositionMonster()... ");
	setPosX(pos, 15);
	setPosY(pos, 13);
	setPositionMonster(pMonster, getPosX(pos), getPosY(pos));
	assert(getPosX(getPositionMonster(pMonster)) == 15);
	assert(getPosY(getPositionMonster(pMonster)) == 13);
	printf("Ok.\n");


	printf("Freeing monster... ");
	monsterFree(&monster);
	assert(monster.name == NULL);
	assert(monster.weapon == NULL);
	assert(monster.spellBar == NULL);
	assert(monster.pos == NULL);
	printf("Ok.\n");

	printf("Freeing pMonster... ");
	monsterDestroy(&pMonster);
	assert(pMonster == NULL);
	printf("Ok.\n");

	printf("Test of loadMonsterFromFile()... ");
	Monster * pMonster1;
	pMonster1 = loadMonsterFromFile("data/Init/Monster/monster1.init");
	printf("Ok.\n");

	monsterDestroy(&pMonster1);
	


	printf("==== The tests went well ==== \n\n");
	
	
}