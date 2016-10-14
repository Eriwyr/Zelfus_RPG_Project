#include "Horde.h"

void hordeInit(Horde * horde, int nbMstr){
	assert(nbMstr >= 0);
	// int i;
	horde->nbMstr = 0;
	horde->size = nbMstr;
	horde->monsters = malloc(nbMstr*sizeof(Monster*));
}

void hordeFree(Horde * horde){
	int i;
	for(i=0;i<horde->nbMstr;i++){
		if(horde->monsters[i] != NULL)
			monsterDestroy(&horde->monsters[i]);
	}
	free(horde->monsters);
	horde->monsters = NULL;
	horde->nbMstr = 0;
}
	
Horde* hordeCreate(int nbMstr){
	Horde * horde;
	horde = malloc(sizeof(Horde)); /*We create space for a horde object*/
	assert (horde != NULL);
	hordeInit(horde, nbMstr); /*We initialize*/

	return horde;
}

void hordeDestroy(Horde ** horde){
	hordeFree(*horde);
	free(*horde);
	*horde = NULL;
}

void addMonster(Horde * horde, Monster * newMonster){
	if(horde->nbMstr < horde->size){ /*If we have as much monsters as the number max of monsters possible*/
		horde->monsters[horde->nbMstr] = newMonster;
		setIdMonster(horde->monsters[horde->nbMstr], horde->nbMstr);
		horde->nbMstr++;
	}
	/*We can now add the element because we made sure there is enough place*/
	/*We increment the number of monsters*/
	
}

void removeMonster(Horde * horde, int ind){
	int j;
	/*Making sure that the ind is <= to the number of monsters and > 0 */
	assert(ind <= horde->nbMstr);
	assert(ind > 0);
	for(j = ind-1; j<horde->nbMstr-1;j++){ /*We start the loop from the ind ( minus one to keep first element at ind 1 )*/
		horde->monsters[j] = horde->monsters[j+1]; /*Each elements is then shifted from 1*/
		setIdMonster(horde->monsters[j], getIdMonster(horde->monsters[j])-1);
	}
	horde->nbMstr--; // There is now one element less

	// We redifine the size once there is enough free slots
	Monster ** tmp = horde->monsters; //We save the current monsters
	horde->size--;
	horde->monsters = malloc(horde->size*sizeof(Monster*)); //We reallocate memory
	for(j=0;j<horde->nbMstr;j++){
		horde->monsters[j] = tmp[j]; //Restoration of the saved monsters
	}
	free(tmp);
}

Monster** getMonstersHorde(const Horde * horde){
	return horde->monsters;
}

Monster* getElementIHorde(const Horde * horde, int i){
	assert(i>=0);
	assert(i<horde->nbMstr);
	return horde->monsters[i];
}

int getNbMstrHorde(const Horde * horde){
	return horde->nbMstr;
}

int getSizeHorde(const Horde* horde){
	return horde->size;
}




void hordeTest(){
	Horde horde;
	Horde *horde1;
	Monster * pMonster;
	printf("==== Tests of Horde ==== \n");

	printf("Initialisation using hordeInit()... ");
	hordeInit(&horde, 1);
	assert(horde.nbMstr == 0);
	assert(horde.size == 1);
	assert(sizeof(horde.monsters) == sizeof(horde.size*sizeof(Monster*)));
	printf("Ok.\n");

	printf("Initialisation using hordeCreate()... ");
	horde1 = hordeCreate(2);
	assert(horde1->size == 2);
	assert(horde1->nbMstr == 0);
	assert(sizeof(horde1->monsters) == sizeof(horde1->size*sizeof(Monster*)));
	printf("Ok.\n");


	printf("AddMonster test... ");
	pMonster = monsterCreate("name");
	setLifePointsMonster(pMonster, 121);
	addMonster(horde1, pMonster);
	assert(getLifePointsMonster(horde1->monsters[0]) == getLifePointsMonster(pMonster) );
	assert(horde1->nbMstr == 1);
	printf("Ok.\n");

	printf("Freeing horde... ");
	hordeFree(&horde);
	assert (horde.monsters == NULL);
	printf("Ok.\n");

	printf("Freeing horde1... ");
	hordeDestroy(&horde1);
	assert(horde1 == NULL);
	printf("Ok\n");

	//monsterDestroy(&pMonster); //A monster created by monsterCreate will be freed but not it's pointer

	printf("==== The tests went well ====\n\n");
}