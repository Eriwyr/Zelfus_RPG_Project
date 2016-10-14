#include "Stuff.h"

void stuffInit(Stuff* newStuff, const char *newName, int newResistancestrength, int newResistanceIntelligence, int newBonusWisdom, int id){
    assert(newResistancestrength>=0);
    assert(newResistanceIntelligence>=0);
    assert(newBonusWisdom>=0);
    
    newStuff->name = strdup(newName);  /*Don't forget to free newStuff->name*/
    newStuff->resistancestrength = newResistancestrength;
    newStuff->resistanceIntelligence = newResistanceIntelligence;
    newStuff->bonusWisdom = newBonusWisdom;
    newStuff->id = id;

}

void stuffFree(Stuff* stuff){
    free(stuff->name);
    stuff->name = NULL;
}



Stuff *stuffCreate(const char *newName, int newResistancestrength, int newResistanceIntelligence, int newBonusWisdom, int id){
    Stuff * stuff;
    stuff = malloc(sizeof(Stuff));
    stuffInit(stuff, newName, newResistancestrength, newResistanceIntelligence, newBonusWisdom, id);
    
    return stuff;
    
    
}

void stuffDestroy(Stuff ** stuff){
    stuffFree(*stuff);
    free(*stuff);
    *stuff = NULL;
}


int getResistancestrengthStuff(const Stuff* stuff){
    return stuff->resistancestrength;
}

int getResistanceIntelligenceStuff(const Stuff* stuff){
    return stuff->resistanceIntelligence;
}

char* getNameStuff(const Stuff* stuff){
    return stuff->name;
}

int getBonusWisdomStuff(const Stuff* stuff){
    return stuff->bonusWisdom;
}


int getIdStuff(const Stuff* stuff){
    return stuff->id;
}

void setIdStuff(Stuff* stuff, const int id){
    stuff->id = id;
}




Stuff* loadStuffFromFile(char* fileName){
    FILE* file;
    Stuff* stuff;
    char name[CHAR_SIZE_MAX];
    int resistanceStrength, resistanceIntelligence, bonusWisdom, id;

    #ifdef WINDOWS_OS
        strreplace(fileName, '/', '\\');
    #endif
        
    file = fopen(fileName, "r");
    assert(file != NULL);

    fscanf(file, "name:");
    fgets(name, CHAR_SIZE_MAX, file);
    fscanf(file, "resistanceStrength:%d\n", &resistanceStrength);
    fscanf(file, "resistanceIntelligence:%d\n", &resistanceIntelligence);
    fscanf(file, "bonusWisdom:%d\n", &bonusWisdom);
    fscanf(file, "id:%d", &id);
    stuff = stuffCreate(name, resistanceStrength, resistanceIntelligence, bonusWisdom, id);

    fclose(file);
    return stuff;
}



void stuffTest(){

    char *tmpName1 = "test";
    Stuff *pStuff;
    Stuff stuff;
    int resI, resS, bon;
    
    printf("==== Tests of Stuff ==== \n");
    

    printf ("Initialisation using stuffInit()... ");
    stuffInit(&stuff, tmpName1, 2, 10, 5, 0);
    assert(stuff.resistancestrength == 2);
    assert(stuff.resistanceIntelligence == 10);
    assert(stuff.bonusWisdom == 5);
    assert(strcmp(stuff.name, tmpName1)==0);
    printf("Ok.\n");
    
    printf("Initialisation using stuffCreate()... ");
    pStuff = stuffCreate("stuff", 2, 10, 5, 0);
    assert(pStuff->resistancestrength == 2);
    assert(pStuff->resistanceIntelligence == 10);
    assert(pStuff->bonusWisdom == 5);
    assert(strcmp(pStuff->name, "stuff")==0);
    printf("Ok->\n");
    
    
    printf("Testing getResistancestrengthStuff()... ");
    resS =getResistancestrengthStuff(pStuff);
    assert(resS == 2);
    printf("Ok\n");
    
    printf("Testing getName()... ");
    assert (strcmp(getNameStuff(pStuff), "stuff") == 0);
    printf("Ok\n"); 
    
    printf("Testing getResistanceIntelligenceStuff()... ");
    resI = getResistanceIntelligenceStuff(pStuff);
    assert(resI == 10);
    printf("Ok\n");
    
    printf("Testing getBonusWisdomStuff()... ");
    bon = getBonusWisdomStuff(pStuff);
    assert(bon == 5);
    printf("Ok\n");

    printf("Freeing stuff... ");
    stuffFree(&stuff);
    assert(stuff.name == NULL);
    printf("Ok.\n");

    printf("Freeing pStuff... ");
    stuffDestroy(&pStuff);
    assert(pStuff == NULL);
    printf("Ok\n");

    printf("Test of loadStuffFromFile()... ");
    Stuff* pStuff1;
    pStuff1 = loadStuffFromFile("data/Init/Stuff/stuff1.init");
    stuffDestroy(&pStuff1);
    printf("Ok.\n");

    

    printf("==== The tests went well ====\n\n");
}
