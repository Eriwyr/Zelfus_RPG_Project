#include "AI.h"



void hitNRun(Fight * fight, int turn){
    Monster * monster;
    monster = getElementIHorde(getHordeFight(fight), turn);
    int distance = getNbSquares(getPositionMonster(monster), getPositionCharacter(getCharacterFight(fight)))+1;
    int range = getRangeWeapon(getWeaponMonster(monster));

    if(getApEnnemyFight(fight) > 0 ){
    	if(range <= distance){
	    	if(attackPlayer(monster, fight->player)){
	    		setApEnnemyFight(fight, getApEnnemyFight(fight)-1);
	    		return;
	    	}

    	}
    }
    if(getMpEnnemyFight(fight) > 0){
    		if(getApEnnemyFight(fight) <= 0){
    			getAway(fight, turn);
    		} else {
    			getCloser(fight, turn);
    		}
    		return;
    } 
    
    setApEnnemyFight(fight, 3);
	setMpEnnemyFight(fight, 3);
    
}


void getCloser(Fight * fight, int i){
        int direction;
        direction = moveToward(fight, i, getPositionCharacter(getCharacterFight(fight)), getMapFight(fight));
        if(getMpEnnemyFight(fight) > 0){
        	if(moveMonsterOnFight(fight, i, direction))
            	setMpEnnemyFight(fight, getMpEnnemyFight(fight)-1);
        }
}

void  getAway(Fight * fight, int i){

    int direction;
            
    direction = moveAway(fight, i, getPositionCharacter(getCharacterFight(fight)), getMapFight(fight));
   	if(getMpEnnemyFight(fight) > 0){
   		if(moveMonsterOnFight(fight, i, direction))
        	setMpEnnemyFight(fight, getMpEnnemyFight(fight)-1);
   	}
}

int attackPlayer(Monster * monster, Character * player){
	int damage, range, distance, resistance, i;
	
	damage = getDamageWeapon(getWeaponMonster(monster));
	damage += getStrengthMonster(monster);
	resistance = 0;
	for(i=0;i<4;i++){
		resistance += getResistancestrengthStuff(getStuffICharacter(player, i));
	}

	resistance /= 4;
	damage -= resistance;
	

	range = getRangeWeapon(getWeaponMonster(monster));
	distance = getNbSquares(getPositionMonster(monster), getPositionCharacter(player))+1;

	if(distance <= range){
		setLifePointsCharacter(player, getLifePointsCharacter(player)-damage);
		if(getLifePointsCharacter(player) < 0)
			setLifePointsCharacter(player, 0);
		return 1;
	}
	return 0;
}

int moveToward(Fight * fight,int i, Position * pos, Map * map){
	int Xmon, Ymon, X, Y;
	int left, right, up, down;
	Monster * monster = getElementIHorde(getHordeFight(fight), i);
	left=1;
	right=1;
	up=1;
	down=1;
	Xmon = getPosX(getPositionMonster(monster));
	Ymon = getPosY(getPositionMonster(monster));
	X = getPosX(pos);
	Y = getPosY(pos);
	while(left == 1 || right == 1 || up == 1|| down == 1){
		if(abs(Xmon - X) > abs(Ymon - Y)){
			if ( (Xmon - X) > 0 && left == 1){
				if(isEmpty(fight, getPosX(getPositionMonster(monster))-1, getPosY(getPositionMonster(monster))))
					return LEFT;
				else {
					while((Xmon - X) > 0){
						Xmon--;
					}
					left = 0;
				}
			}
			else if ((Xmon - X ) <= 0 && right == 1) {
				if(isEmpty(fight, getPosX(getPositionMonster(monster))+1, getPosY(getPositionMonster(monster))))
					return RIGHT;
				else {
					while((Xmon - X) <= 0){
						Xmon++;
					}
					right = 0;
				}
			}
		} else {
			if (Ymon - Y > 0 && up == 1){
				if(isEmpty(fight, getPosX(getPositionMonster(monster)), getPosY(getPositionMonster(monster))-1))
					return UP;
				else {
					while(Ymon - Y > 0){
						Ymon--;
					}
					up = 0;
				}
			}
			else if(Ymon - Y <= 0 && down == 1){
				if(isEmpty(fight, getPosX(getPositionMonster(monster)), getPosY(getPositionMonster(monster))+1))
					return DOWN;
				else {
					while(Ymon - Y <= 0){
						Ymon++;
					}
					down = 0;
				}
			}
		}
	}
	
	return -1;
}

int moveAway(Fight * fight, int i, Position * pos, Map * map){
	int Xmon, Ymon, X, Y;
	int left, right, up, down;
	Monster * monster = getElementIHorde(getHordeFight(fight), i);
	left=1;
	right=1;
	up=1;
	down=1;
	Xmon = getPosX(getPositionMonster(monster));
	Ymon = getPosY(getPositionMonster(monster));
	X = getPosX(pos);
	Y = getPosY(pos);
	while(left || right || up || down){
		if((Xmon - X) > (Ymon - Y)){
			if (Xmon - X > 0 && right){
				if(isEmpty(fight, getPosX(getPositionMonster(monster))+1, getPosY(getPositionMonster(monster))))
					return RIGHT;
				else {
					while(Xmon - X > 0){
						Xmon--;
					}
					right = 0;
				}
			} else if(Xmon-X <= 0 && left){
				if(isEmpty(fight, getPosX(getPositionMonster(monster))-1, getPosY(getPositionMonster(monster))))
					return LEFT;
				else {
					while(Xmon - X <= 0){
						Xmon--;
					}
					left=0;
				}
			}
		} else {
			if (Ymon - Y > 0 && down){
				if(isEmpty(fight, getPosX(getPositionMonster(monster)), getPosY(getPositionMonster(monster))+1))
					return DOWN;
				else {
					while(Ymon - Y > 0){
						Ymon--;
					}
					down= 0;
				}
			}
			else if(Ymon - Y <= 0 && up){
				if(isEmpty(fight, getPosX(getPositionMonster(monster)), getPosY(getPositionMonster(monster))-1))
					return UP;
				else {
					while(Ymon - Y <= 0){
						Ymon--;
					}
					up=0;
				}
			}
		}
	}
	
	return -1;
}

