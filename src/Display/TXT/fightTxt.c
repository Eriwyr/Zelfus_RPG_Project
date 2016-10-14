#include "fightTxt.h"

void launchFightTxt(Fight * fight){
    int actual = PLAYER; /*To see who's turn it is*/
    int action; /*So we can know what the player wants to do*/
    Monster * monster;
    int go = 1;
    // int i;
    int monsterId = 0;
    int t, nt;
    t = convertSecToMillisec(time(NULL));
    drawFightTxt(fight);
    while(go == 1){
        if(isFinished(fight))
            go = 0;

        nt = convertSecToMillisec(time(NULL));
        
        if (actual == PLAYER){ /*If it the player's turn*/
                action = inputKeyboardTxt(); /*we get the action the player wants to do */
                switch(action){
                    /*If the actions is to move, we check the direction*/
                    case MOVE_DOWNWARD :
                        if(getMpPlayerFight(fight) > 0){
                            /*We check if there is enough mp to move*/
                            if(movePlayerOnFight(fight, DOWN)){
                                /*If the movement succeed, we decrement the mps*/
                                setMpPlayerFight(fight, getMpPlayerFight(fight)-1);
                            }
                                    
                        }
                        break;
                    case MOVE_UPWARD :
                        if(getMpPlayerFight(fight) > 0){
                            if(movePlayerOnFight(fight, UP)){
                                setMpPlayerFight(fight, getMpPlayerFight(fight)-1);
                            }
                        }
                        break;
                    case MOVE_LEFT :
                        if(getMpPlayerFight(fight) > 0){
                            if(movePlayerOnFight(fight, LEFT)){
                                setMpPlayerFight(fight, getMpPlayerFight(fight)-1);
                            }
                        }
                        break;
                    case MOVE_RIGHT :
                        if(getMpPlayerFight(fight) > 0){
                            if(movePlayerOnFight(fight, RIGHT)){
                                setMpPlayerFight(fight, getMpPlayerFight(fight)-1);
                            }
                        }
                        break;
                    /* If the player wants to attack*/
                    case ATTACK_1 :
                        if(getApPlayerFight(fight) > 0){
                            /*We check if we have enough ap to attack*/
                            monster = getClosestMonster(fight);
                            if(attackMonster(getCharacterFight(fight), monster))
                                /*If the attack is successful, we decrement the aps*/
                                setApPlayerFight(fight, getApPlayerFight(fight)-1);
                            if(getLifePointsMonster(monster) == 0){
                                deleteMonsterTxt(fight, monster);
                            }
                        }
                        
                        break;
                    case ATTACK_2 :
                        if(getApPlayerFight(fight) > 0){
                            /*We check if we have enough ap to attack*/
                            monster = getClosestMonster(fight);
                            if(attackMonsterSpell(getCharacterFight(fight), monster,getSpell(getSpellBarCharacter(getCharacterFight(fight)),1) ))
                                /*If the attack is successful, we decrement the aps*/
                                setApPlayerFight(fight, getApPlayerFight(fight)-1);
                            if(getLifePointsMonster(monster) == 0){
                                deleteMonsterTxt(fight, monster);
                            }
                        }
                        break;
                    case ATTACK_3 :
                        if(getApPlayerFight(fight) > 0){
                            /*We check if we have enough ap to attack*/
                            monster = getClosestMonster(fight);
                            if(attackMonsterSpell(getCharacterFight(fight), monster,getSpell(getSpellBarCharacter(getCharacterFight(fight)),2) ))
                                /*If the attack is successful, we decrement the aps*/
                                setApPlayerFight(fight, getApPlayerFight(fight)-1);
                            if(getLifePointsMonster(monster) == 0){
                                deleteMonsterTxt(fight, monster);
                            }
                        }    
                        break;
                    case NOTHING :
                        actual = ENNEMY;
                        break;

                    case QUIT:
                        go = 0;
                        break;
                }
        }
        if(nt - t > 300){
            if (actual == ENNEMY){
                hitNRunTxt(fight, monsterId);
                if(getMpEnnemyFight(fight) == 3 && getMpEnnemyFight(fight) == 3)
                    monsterId++;
                if(monsterId >= getNbMstrHorde(getHordeFight(fight))){
                    actual = PLAYER;
                    setApPlayerFight(fight, 3);
                    setMpPlayerFight(fight, 3);
                    monsterId = 0;
                }
            }
            t = nt;
            drawFightTxt(fight);
        }

       
       
    }
}

int inputKeyboardTxt(){
	char a;
	a = getchar();
	switch(a){
		case 'q':
			return MOVE_LEFT;
		break;
		case 'd':
			return MOVE_RIGHT;
		break;
		case 'z':
			return MOVE_UPWARD;
		break;
		case 's':
			return MOVE_DOWNWARD;
		break;
		case 'p':
			return NOTHING;
		break;
		case '1':
			return ATTACK_1;
		break;
		case '2':
			return ATTACK_2;
		break;
		case '3':
			return ATTACK_3;
		break;
		case '4':
			return ATTACK_4;
		break;
		case '=':
			return QUIT;
		break;
	}
	return -1;
}

void drawFightTxt(Fight* fight){
	clear();
	setMapTxt(getMapFight(fight));
	setPlayerTxt(getCharacterFight(fight), getMapFight(fight));
	setMonsterTxt(getHordeFight(fight), getMapFight(fight));
	drawHudTxt(fight);
	drawMapTxt(getMapFight(fight));
	drawSpellBarTxt(fight);	
}


Fight* fightCreateTxt(char* fightName){
	Fight * fight;
    Character *player = characterCreate();
    fight = loadFightFromFile(fightName, player);
    setMonstersOnRandomPosition(fight);
    characterDestroy(&player);
    return fight;
}


void drawHudTxt(Fight * fight){
	printf("Life : %d ", getLifePointsCharacter(getCharacterFight(fight)));
	printf("PM : %d ", getMpPlayerFight(fight));
	printf("PA : %d\n", getApPlayerFight(fight));
}

void drawSpellBarTxt(Fight * fight){
	int i;
	printf("Attack : 1 ");
	for(i=0;i<getNbSpell(getSpellBarCharacter(getCharacterFight(fight)));i++){
		printf("Spell : %d ", i+1);
	}
	printf("Pass : p\n");
}

void deleteMonsterTxt(Fight * fight, Monster * monster){
	killMonster(fight, monster);
}


void hitNRunTxt(Fight * fight, int turn){
        hitNRun(fight, turn);
}

