#include "SpellBar.h"

void spellBarInit(SpellBar * spellBar){
    spellBar->spells = malloc(5*sizeof(Spell*));
    spellBar->nbSpell = 0;
}

SpellBar * spellBarCreate(){
    SpellBar * spellBar;
    spellBar = malloc(sizeof(SpellBar));
    
    spellBarInit(spellBar);
    return spellBar;
}

void addSpell(SpellBar* spellBar, Spell *newSpell){
    assert(newSpell != NULL);
    assert(spellBar != NULL);
    
    if (spellBar->nbSpell < 5){
    spellBar->spells[spellBar->nbSpell] = newSpell;
    spellBar->nbSpell++;
    }
}

void spellBarFree(SpellBar * spellBar){
    int i;
    for(i=0;i<spellBar->nbSpell;i++){
        spellDestroy(&spellBar->spells[i]);
    }
    free(spellBar->spells);
    spellBar->spells = NULL;
    spellBar->nbSpell = 0;
}

void spellBarDestroy(SpellBar ** spellBar){
    spellBarFree(*spellBar);
    free(*spellBar);
    *spellBar = NULL;
}

int getNbSpell(SpellBar * spellBar){
    return spellBar->nbSpell;
}

Spell* getSpell(const SpellBar* spellBar, int i){

    assert(i>=0);
    assert(i<spellBar->nbSpell);

    return spellBar->spells[i];
}


SpellBar* loadSpellBarFromFile(char* fileName){
    FILE* file;
    SpellBar* spellBar;
    int spellId, i, nbSpell;
    char spellIdTxt[10];
    char spellFile[CHAR_SIZE_MAX];

    #ifdef WINDOWS_OS
        strreplace(filName, '/', '\\');
    #endif
    
    file = fopen(fileName, "r");
    assert(file != NULL);

    spellBar = spellBarCreate();

    fscanf(file, "nbSpells:%d\n", &nbSpell);
    for(i=0;i<nbSpell;i++){
        fscanf(file, "SpellId:%d\n", &spellId);
        if(exist("data/Save/load.load")){
            strcpy(spellFile, "data/Init/Spell/spell");
            sprintf(spellIdTxt, "%d", spellId);
            strcat(spellFile, spellIdTxt);
            strcat(spellFile, ".init");
        } else {
            strcpy(spellFile, "data/Init/Spell/spell");
            sprintf(spellIdTxt, "%d", spellId);
            strcat(spellFile, spellIdTxt);
            strcat(spellFile, ".init");
        }
        
        addSpell(spellBar, loadSpellFromFile(spellFile));
    }

    fclose(file);
    return spellBar;
}

void saveSpellBarOnFile(SpellBar * spellBar, char* fileName){
    FILE * file;
    int i;

    #ifdef WINDOWS_OS
        strreplace(fileName, "/", "\\");
    #endif

    file = fopen(fileName, "w+");
    assert(file != NULL);

    fprintf(file, "nbSpells:%d\n", spellBar->nbSpell);
    for(i=0;i<spellBar->nbSpell;i++){
        fprintf(file, "SpellId:%d\n", getIdSpell(spellBar->spells[i]));
    }

    fclose(file);
}


void spellBarTest(){
    SpellBar spellBar;
    SpellBar * pSpellBar;
    Spell *spell;
    Spell *spell2;

    printf("==== Tests of SpellBar ==== \n");

    printf("Initialisation using spellBarInit()... ");
    spellBarInit(&spellBar);
    assert(sizeof(spellBar.spells) == sizeof(5*sizeof(Spell)));
    printf("Ok.\n");

    printf("Initialisation using spellBarCreate()... ");
    pSpellBar = spellBarCreate();
    assert(sizeof(SpellBar)== sizeof(*pSpellBar));
    printf("OK.\n");


    printf("Test of addSpell()... ");
    spell = spellCreate(1, "First Spell", 12, 2);
    spell2 = spellCreate(2, "Second Spell", 3, 2);
    addSpell(pSpellBar, spell);
    assert(getIdSpell((pSpellBar->spells[0])) == 1);
    assert(strcmp(getNameSpell((pSpellBar->spells[0])), "First Spell") == 0);
    assert(getDamageSpell((pSpellBar->spells[0])) == 12);
    assert(pSpellBar->nbSpell == 1);

    addSpell(pSpellBar, spell2);
    assert(getIdSpell((pSpellBar->spells[1])) == 2);
    assert(strcmp(getNameSpell((pSpellBar->spells[1])), "Second Spell") == 0);
    assert(getDamageSpell((pSpellBar->spells[1])) == 3);
    assert(pSpellBar->nbSpell == 2);
    printf("Ok.\n");



    printf("Freeing spellBar... ");
    spellBarFree(&spellBar);
    assert(spellBar.spells == NULL);
    printf("Ok.\n");

    printf("Freeing pSpellBar... ");
    spellBarDestroy(&pSpellBar);
    assert(pSpellBar == NULL);
    printf("Ok.\n");

    // spellFree(&spell);
    // spellFree(&spell2);

    SpellBar* spellBar1;
    spellBar1 = loadSpellBarFromFile("data/Init/Character/spellBar.init");
    spellBarDestroy(&spellBar1);
    printf("==== The tests went well ==== \n\n");
}

