#include "Weapon.h"

void weaponInit(Weapon * weapon, const char * name, int damage, int strength, int intelligence, int wisdom, int range, int id){
    weapon->name = strdup(name);
    weapon->damage = damage;
    weapon->strength = strength;
    weapon->intelligence = intelligence;
    weapon->wisdom = wisdom;
    weapon->range = range;
    weapon->id = id;
}

Weapon* weaponCreate(const char * name, int damage, int strength, int intelligence, int wisdom, int range, int id){
    Weapon * weapon;
    weapon = malloc(sizeof(Weapon));
    weaponInit(weapon, name, damage, strength, intelligence, wisdom, range, id);
    
    return weapon;
}

void weaponFree(Weapon * weapon){
    free(weapon->name);
    weapon->name = NULL;
}

void weaponDestroy(Weapon ** weapon){
    weaponFree(*weapon);
    free(*weapon);
    *weapon = NULL;
}

char* getNameWeapon(const Weapon * weapon){
    return weapon->name;
}

Weapon* loadWeaponFromFile(char* fileName){
    FILE* file;
    Weapon * weapon;
    char name[CHAR_SIZE_MAX];
    int damage, strength, intelligence, wisdom, range, id;


    #ifdef WINDOWS_OS
        strreplace(fileName, '/', '\\');
    #endif

    file = fopen(fileName, "r");
    assert(file != NULL);

    fscanf(file, "id:%d\n", &id);
    fscanf(file, "name:");
    fgets(name, CHAR_SIZE_MAX, file);
    strremoveEOL(name);
    fscanf(file, "damage:%d\n", &damage);
    fscanf(file, "strength:%d\n", &strength);
    fscanf(file, "intelligence:%d\n", &intelligence);
    fscanf(file, "wisdom:%d\n", &wisdom);
    fscanf(file, "range:%d\n", &range);
    weapon = weaponCreate(name, damage, strength, intelligence, wisdom, range, id);

    fclose(file);
    return weapon;
}

void setNameWeapon(Weapon * weapon,const char * name){
    assert(name != NULL);
    free(weapon->name);
    weapon->name = strdup(name);
}

int getDamageWeapon(const Weapon * weapon){
    return weapon->damage;
}

void setDamageWeapon(Weapon * weapon, int damage){
    weapon->damage = damage;
}

int getStrengthWeapon(const Weapon * weapon){
    return weapon->strength;
}

void setStrengthWeapon(Weapon * weapon, int strength){
    weapon->strength = strength;
}

int getIntelligenceWeapon(const Weapon * weapon){
    return weapon->intelligence;
}

void setIntelligenceWeapon(Weapon * weapon, int intelligence){
    weapon->intelligence = intelligence;
}

int getWisdomWeapon(const Weapon * weapon){
    return weapon->wisdom;
}

void setWisdomWeapon(Weapon * weapon, int wisdom){
    weapon->wisdom = wisdom;
}

int getRangeWeapon(const Weapon* weapon){
    return weapon->range;
}

void setRangeWeapon(Weapon* weapon, const int range){
    weapon->range = range;
}



int getIdWeapon(const Weapon* weapon){
    return weapon->id;
}

void setIdWeapon(Weapon* weapon, const int id){
    weapon->id = id;
}



void weaponTest(){
    Weapon * pWeapon;
    Weapon weapon;

    printf("==== Tests of Weapon ==== \n");

    printf("Initialisation using weaponInit()... ");
    weaponInit(&weapon, "weapon", 5, 3, 6, 2, 1, 1);
    assert(strcmp(weapon.name, "weapon") == 0);
    assert(weapon.damage == 5);
    assert(weapon.strength == 3);
    assert(weapon.intelligence == 6);
    assert(weapon.wisdom == 2);
    printf("Ok.\n");

    printf("Initialisation using weaponCreate()... ");
    pWeapon = weaponCreate("weapon", 5, 3, 6, 2, 1, 1);
    assert(strcmp(pWeapon->name, "weapon") == 0);
    assert(pWeapon->damage == 5);
    assert(pWeapon->strength == 3);
    assert(pWeapon->intelligence == 6);
    assert(pWeapon->wisdom == 2);
    printf("Ok.\n");

    printf("Test of getNameWeapon... ");
    assert(strcmp(getNameWeapon(pWeapon), "weapon") == 0);
    printf("Ok.\n");

    printf("Test of setNameWeapon... ");
    setNameWeapon(pWeapon, "thisisalongsentencetotest");
    assert(strcmp(pWeapon->name, "thisisalongsentencetotest") == 0);
    printf("Ok.\n");

    printf("Test of getDamageWeapon... ");
    assert(getDamageWeapon(pWeapon) == 5);
    printf("Ok.\n");

    printf("Test of setDamageWeapon... ");
    setDamageWeapon(pWeapon, 12);
    assert(pWeapon->damage == 12);
    printf("Ok.\n");

    printf("Test of getStrengthWeapon... ");
    assert(getStrengthWeapon(pWeapon) == 3);
    printf("Ok.\n");

    printf("Test of setDamageWeapon... ");
    setStrengthWeapon(pWeapon, 15);
    assert(pWeapon->strength == 15);
    printf("Ok.\n");

    printf("Test of getIntelligenceWeapon... ");
    assert(getIntelligenceWeapon(pWeapon) == 6);
    printf("Ok.\n");

    printf("Test of setIntelligenceWeapon... ");
    setIntelligenceWeapon(pWeapon, 9);
    assert(pWeapon->intelligence == 9);
    printf("Ok.\n");

    printf("Test of getWisdomWeapon... ");
    assert(getWisdomWeapon(pWeapon) == 2);
    printf("Ok.\n");

    printf("Test of setWisdomWeapon... ");
    setWisdomWeapon(pWeapon, 45);
    assert(pWeapon->wisdom == 45);
    printf("Ok.\n");

    printf("Freeing weapon... ");
    weaponFree(&weapon);
    assert(weapon.name == NULL);
    printf("Ok.\n");

    printf("Freeing pWeapon... ");
    weaponDestroy(&pWeapon);
    assert(pWeapon == NULL);
    printf("Ok.\n");

    printf("Test of loadWeaponFromFile()... ");
    Weapon * pWeapon1;
    pWeapon1 = loadWeaponFromFile("data/Init/Weapon/weapon1.init");
    weaponDestroy(&pWeapon1);
    printf("Ok.\n");
    

    printf("==== The tests went well ====\n\n");
}