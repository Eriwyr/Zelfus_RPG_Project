#include "fightSdl.h"

int launchFight(FightSdl * fightSdl){
	SDL_Event events;
	
	Mix_Music *fightMusic;
	Mix_Chunk *fireSound, *waterSound,*passSound, *damageSound;
	
	enum actual_player actual = PLAYER;
	int go = 1;
	int action;
	int monsterId = 0;
	int tmpLife;
	Uint32  t = SDL_GetTicks(), nt;
	int quit;
	fightMusic = Mix_LoadMUS("data/Music/fight.mp3"); // we loading the fight music

	Mix_AllocateChannels(3); // we allocate 3 channels to play short songs
	fireSound = Mix_LoadWAV("data/Music/fire.wav");
	waterSound = Mix_LoadWAV("data/Music/water.wav");
 	passSound = Mix_LoadWAV("data/Music/pass.wav");
 	damageSound = Mix_LoadWAV("data/Music/damage.wav");
 	if(fightMusic == NULL){
 		printf("error loading fightMusic\n");
 	}
 	
 	Mix_VolumeMusic(MIX_MAX_VOLUME);

    Mix_PlayMusic(fightMusic, -1);
    Mix_AllocateChannels(3);
    Mix_Volume(1, MIX_MAX_VOLUME);

    setLifePointsCharacter(getCharacterFight(fightSdl->fight), 20);


	while(go){
		quit = 0;
		if(isFinished(fightSdl->fight))
			go = 0;
		nt = SDL_GetTicks();
		
		tmpLife = getLifePointsCharacter(getCharacterFight(fightSdl->fight));
		while (SDL_PollEvent(&events)){

			action = inputKeyboard(events);
			if(action == QUIT){
				go = 0;
				quit = 1;
			}

			if(action == -2){
				clearBufferGame(fightSdl->buffer, CHARACTER);
			}

			if(actual == PLAYER) {
				
				switch(action){
					
					case MOVE_DOWNWARD:					
						addActionToBufferGame(fightSdl->buffer, DOWN);
					break;

					case MOVE_UPWARD:
						addActionToBufferGame(fightSdl->buffer, UP);
					break;

					case MOVE_LEFT:
						addActionToBufferGame(fightSdl->buffer, LEFT);
					break;

					case MOVE_RIGHT:
						addActionToBufferGame(fightSdl->buffer, RIGHT);

					break;

					case ATTACK_1:
						actionAttackSdl(fightSdl, ATTACK_1);
					break;

					case ATTACK_2:
						if(Mix_PlayChannel(-1,fireSound,0)<0){
                            printf("error playing fire sound");
                        }
                        clearSpellBuffer(fightSdl->buffer);
						actionAttackSdl(fightSdl, ATTACK_2);
					break;

					case ATTACK_3:
						if(Mix_PlayChannel(-1,waterSound,0)<0){
                            printf("error playing water sound");
                        }
						actionAttackSdl(fightSdl, ATTACK_3);
					break;

					case NOTHING:

						if(Mix_PlayChannel(-1,passSound,0)<0){
                            printf("error playing pass sound");
                        }
						actual = ENNEMY;

						if(isEmptyBufferElmt(fightSdl->buffer))
							actual = ENNEMY;
					break;

					case -1:
						setIsIdleCharacSdl(fightSdl->characSdl,1);
				}	
			}			
		}
		if (nt-t>300){

			if(actual == ENNEMY){
				hitNRunSdl(fightSdl, monsterId);
				if (tmpLife != getLifePointsCharacter(getCharacterFight(fightSdl->fight)) ){
						if(Mix_PlayChannel(-1,damageSound,0)<0){
                            printf("error playing damage sound");
                        }					
				}
				
				if(getMpEnnemyFight(fightSdl->fight) == 3 && getApEnnemyFight(fightSdl->fight) == 3)
					monsterId++;
				if(monsterId >= fightSdl->nbMstrSdl){
					actual = PLAYER;
					setApPlayerFight(fightSdl->fight, 3);
					setMpPlayerFight(fightSdl->fight, 3);
					monsterId = 0;
				}

			}
            t = nt;
        }
		

		// updatePlayerDisplay(fightSdl);
		// updateMonsterDisplay(fightSdl);
		updatePlayerActionFight(fightSdl);
		updateSpellDisplay(fightSdl);
		updateDisplay(fightSdl);

		drawGame(fightSdl);

        // SDL_RenderPresent(fightSdl->renderer);
	}
	Mix_FreeMusic(fightMusic);
	Mix_FreeChunk(fireSound);
	Mix_FreeChunk(waterSound);
	Mix_FreeChunk(passSound);
	Mix_FreeChunk(damageSound);
	if(quit)
		return 0;
	if(getLifePointsCharacter(getCharacterFight(fightSdl->fight)) > 0)
		return 1;
	else return 0;


}

int inputKeyboard(SDL_Event event){

	switch (event.type){
		case SDL_QUIT:
			return QUIT;
        break;

		case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
            	case SDLK_z:
            		return MOVE_UPWARD;
            	break;

            	case SDLK_s:
            		return MOVE_DOWNWARD;
            	break;

            	case SDLK_q:
            		return MOVE_LEFT;
            	break;

            	case SDLK_d:
            		return MOVE_RIGHT;
            	break;

            	case SDLK_RETURN:
            		return NOTHING;
            	break;

            	case SDLK_KP_1:
            		return ATTACK_1;
            	break;

            	case SDLK_KP_2:
            		return ATTACK_2;
            	break;

            	case SDLK_KP_3:
            		return ATTACK_3;
            	break;

            	case SDLK_KP_4:
            		return ATTACK_4;
            	break;

            	case SDLK_ESCAPE:
            		return QUIT;
            	break;
			}
        break; 
	}
    return -1;
}

void updatePlayerDisplay(FightSdl * fightSdl){
	int i, j, x, y, curX, curY;
	i = getIFromElmtBufferGame(fightSdl->buffer, CHARACTER);
	Position * current;
	
	if(i != -1){
		setIsIdleCharacSdl(fightSdl->characSdl,0);
		setCurrentIndexBufferGame(fightSdl->buffer, i);	
		x = getXBufferGame(fightSdl->buffer, i);
		y = getYBufferGame(fightSdl->buffer, i);
		curX = getPosX(getCurrentPosCharacSdl(fightSdl->characSdl));
		curY = getPosY(getCurrentPosCharacSdl(fightSdl->characSdl));
		if( curX == x && curY == y){
				j = getIndexIBufferGame(fightSdl->buffer, i);
            	removeEventFromBufferGame(fightSdl->buffer, i);
           		if(j != -1 && j != -2){
                	removeActionFromBufferGame(fightSdl->buffer, j);
            	}

				setIsIdleCharacSdl(fightSdl->characSdl, 1);
		} 

		else {
			current = getCurrentPosCharacSdl(fightSdl->characSdl);
			if( (y-curY) > 0 ) {
				actionMoveSdl(getDirectionCharacSdl(fightSdl->characSdl), current,  DOWN);
			} else if( (y-curY) < 0 ){
				actionMoveSdl(getDirectionCharacSdl(fightSdl->characSdl), current,  UP);
			}else if( (x-curX) < 0){
				actionMoveSdl(getDirectionCharacSdl(fightSdl->characSdl), current, LEFT);
			}else if( (x-curX) > 0){
				actionMoveSdl(getDirectionCharacSdl(fightSdl->characSdl), current, RIGHT);
			}
		}
	}	
}	

void updatePlayerActionFight(FightSdl * fightSdl){
	int action;
    action = getActionIBufferGame(fightSdl->buffer, 0);
    if(hasBeenExcutedBufferAction(fightSdl->buffer, 0) == 0){
        switch(action){
            case DOWN:
                actionMove(fightSdl->fight, DOWN);
            break;

            case UP:
                actionMove(fightSdl->fight, UP);
            break;

            case RIGHT:
                actionMove(fightSdl->fight, RIGHT);
            break;

            case LEFT:
                actionMove(fightSdl->fight, LEFT);
            break;

            case -1:
            break;

            default:
            break;
        }

        setExecutedBufferAction(fightSdl->buffer, 0, 1);
        addEventToBufferGame(fightSdl->buffer, CHARACTER, getPosX(getPositionCharacter(getCharacterFight(fightSdl->fight)))*64, 
            getPosY(getPositionCharacter(getCharacterFight(fightSdl->fight)))*64, 0);
            // removeEventFromBuffer(fightSdl->buffer->action, i);
    }
}

void updateMonsterDisplay(FightSdl * fightSdl){
	int i, x, y , curX, curY, j;
	MonsterSdl * monster;
	Position * current;
	
	i = getIFromElmtBufferGame(fightSdl->buffer, MONSTER);

	if(i != -1){


		setCurrentIndexBufferGame(fightSdl->buffer, i);
		j = getIndexIBufferGame(fightSdl->buffer, i);

		monster = getMonsterSdlIFromFightSdl(fightSdl, j);
		setIsIdleMonsterSdl(monster, 0);
		x = getXBufferGame(fightSdl->buffer, i);
		y = getYBufferGame(fightSdl->buffer, i);
		curX = getPosX(getCurrentPosMonsterSdl(monster));
		curY = getPosY(getCurrentPosMonsterSdl(monster));
		if( curX == x && curY == y){
				removeEventFromBufferGame(fightSdl->buffer, i);
				setIsIdleMonsterSdl(monster, 1);
		} 

		else {
			current = getCurrentPosMonsterSdl(monster);
			if( (y-curY) > 0 ) {
				actionMoveSdl(getDirectionMonsterSdl(monster), current, DOWN);
			} else if( (y-curY) < 0 ){
				actionMoveSdl(getDirectionMonsterSdl(monster), current, UP);
			}else if( (x-curX) < 0){
				actionMoveSdl(getDirectionMonsterSdl(monster), current, LEFT);
			}else if( (x-curX) > 0){
				actionMoveSdl(getDirectionMonsterSdl(monster), current, RIGHT);
			}
		}

	}
}

void updateDisplay(FightSdl * fightSdl){
	int i;
	i = getEventIBufferGame(fightSdl->buffer, 0);
	if(i != -1){
		switch(i){
			case PLAYER:
				updatePlayerDisplay(fightSdl);
				break;
			case MONSTER:
				updateMonsterDisplay(fightSdl);
		}

	}
}


void actionAttackSdl(FightSdl * fightSdl, int attack){
	int action;
	// action = actionAttack(fightSdl->fight, attack);
	action = 2;
	SpellSdl * spell;
	MonsterSdl * monster;
	int startX, startY, goX, goY;
	startX = getPosX(getCurrentPosCharacSdl(fightSdl->characSdl));
	startY = getPosY(getCurrentPosCharacSdl(fightSdl->characSdl));

	monster = getMonsterSdlIFromFightSdl(fightSdl, getIdMonster(getClosestMonster(fightSdl->fight)));
	goX = getPosX(getCurrentPosMonsterSdl(monster));
	goY = getPosY(getCurrentPosMonsterSdl(monster));
	if(getApPlayerFight(fightSdl->fight) > 0){
		switch(action){

			case 2:
				switch(attack){
					case ATTACK_1:
						actionAttack(fightSdl->fight, ATTACK_1);
						if(getToKillFight(fightSdl->fight) == 1){
							deleteMonster(fightSdl);
							setToKillFight(fightSdl->fight, 0);
						}
					break;
					case ATTACK_2:
						spell = getSpellSdlIFromFightSdl(fightSdl, 0);
						setCurrentPosSpellSdl(spell, startX, startY);
						addEventToBufferGame(fightSdl->buffer, SPELL, goX, goY, 0);
					break;
					case ATTACK_3:
						spell = getSpellSdlIFromFightSdl(fightSdl, 1);
						setCurrentPosSpellSdl(spell, startX, startY);
						addEventToBufferGame(fightSdl->buffer, SPELL, goX, goY, 1);
					break;
				}
			break;

			default:
			break;
		}
	}
}

void updateSpellDisplay(FightSdl * fightSdl){
	int i, x, y , curX, curY, j;
	SpellSdl * spell;
	Position * current;
	
	i = getIFromElmtBufferGame(fightSdl->buffer, SPELL);

	if(i != -1){
		setCurrentIndexBufferGame(fightSdl->buffer, i);
		j = getIndexIBufferGame(fightSdl->buffer, i);

		spell = getSpellSdlIFromFightSdl(fightSdl, j);
		setDisplaySpellSdl(spell, 1);
		x = getXBufferGame(fightSdl->buffer, i);
		y = getYBufferGame(fightSdl->buffer, i);
		curX = getPosX(getCurrentPosSpellSdl(spell));
		curY = getPosY(getCurrentPosSpellSdl(spell));
		if( curX == x && curY == y){

				setDisplaySpellSdl(spell, 0);
				removeEventFromBufferGame(fightSdl->buffer, i);
				actionAttack(fightSdl->fight, ATTACK_2);
				if(getToKillFight(fightSdl->fight) == 1){
					deleteMonster(fightSdl);
					setToKillFight(fightSdl->fight, 0);
				}
		} 

		else {
			current = getCurrentPosSpellSdl(spell);
			if( (y-curY) > 0 ) {
				actionMoveSdl(getDirectionSpellSdl(spell), current, DOWN);
			} else if( (y-curY) < 0 ){
				actionMoveSdl(getDirectionSpellSdl(spell), current, UP);
			}else if( (x-curX) < 0){
				actionMoveSdl(getDirectionSpellSdl(spell), current, LEFT);
			}else if( (x-curX) > 0){
				actionMoveSdl(getDirectionSpellSdl(spell), current, RIGHT);
			}
		}

	}
}

void fightSdlInit(FightSdl * fightSdl, SDL_Window * screen,  SDL_Renderer * renderer, Fight * fight){

    int i;

	fightSdl->screen = screen;
 	fightSdl->renderer = renderer;


    fightSdl->fight = fight;
    fightSdl->mapSdl = mapSdlCreate("data/Image/mapTileset1.png", fightSdl->renderer);
    fightSdl->hudSdl = hudSdlCreate(fightSdl->renderer);
    fightSdl->characSdl = characSdlCreate(getCharacterFight(fightSdl->fight), fightSdl->renderer);
    fightSdl->nbMstrSdl = getNbMstrHorde(getHordeFight(fight));
    fightSdl->size = getSizeHorde(getHordeFight(fight));
    	

    fightSdl->buffer = bufferGameCreate();

    fightSdl->monsterSdl = malloc(fightSdl->nbMstrSdl*sizeof(MonsterSdl*));

    

    setMonstersOnRandomPosition(fightSdl->fight);

    for(i = 0; i < fightSdl->nbMstrSdl; i++){
        fightSdl->monsterSdl[i] = monsterSdlCreate(getPositionMonster(getElementIHorde(getHordeFight(fightSdl->fight), i)), fightSdl->renderer);
        setIdMonsterSdl(fightSdl->monsterSdl[i], getIdMonster(getElementIHorde(getHordeFight(fight), i)));
    }

    // loadFight(fightSdl->fight);    
}

void fightSdlFree(FightSdl * fightSdl){
    
    mapSdlDestroy(&(fightSdl->mapSdl));
    characSdlDestroy(&(fightSdl->characSdl));
    hudSdlDestroy(&(fightSdl->hudSdl));
    free(fightSdl->monsterSdl);
    bufferGameDestroy(&fightSdl->buffer);

}

void drawGame(FightSdl * fightSdl){
    int i;
    updateHud(fightSdl);
    SDL_RenderClear(fightSdl->renderer);
    //SDL_SetRenderDrawColor( fightSdl->renderer, 230, 240, 255, 255);
    drawImage(getBackground(fightSdl->mapSdl), 0, 0, fightSdl->renderer);
    
    
    drawMap(fightSdl->mapSdl,getMapFight(fightSdl->fight), fightSdl->renderer);
    drawHud(fightSdl->hudSdl, fightSdl->renderer);

    drawPlayer(fightSdl->characSdl, fightSdl->renderer);

    for(i = 0; i < fightSdl->nbMstrSdl; i++){
        drawMonster(fightSdl->monsterSdl[i], fightSdl->renderer);
    }

    for(i=0;i<fightSdl->characSdl->nbSpell;i++){
    	if(getDisplaySpellSdl(getSpellSdlIFromCharacSdl(fightSdl->characSdl, i)) == 1)
    		drawSpell(getSpellSdlIFromCharacSdl(fightSdl->characSdl, i), fightSdl->renderer);
    }
    
    
    SDL_RenderPresent(fightSdl->renderer);
     
    
    SDL_Delay(11);
}

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer){
 
    
     
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);
     
    if (loadedImage != NULL){
    	texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
   		if( texture == NULL){
        	printf("La texture n'a pas été initialisé : %s\n", SDL_GetError());
    	}
     
    
    	SDL_FreeSurface(loadedImage);
   		loadedImage = NULL;
    } else
    	printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
     
    return texture;    
}

void drawImage(SDL_Texture *image, int x, int y, SDL_Renderer* renderer){
 
    SDL_Rect dest;
     
    
    dest.x = x;
    dest.y = y;
     
    

    if(SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h) < 0){
        printf("Erreur de queryTexture%s\n", SDL_GetError());
    }
    
    if(SDL_RenderCopy(renderer, image, NULL, &dest)<0){
        printf("%s\n", SDL_GetError());
    }
}

void deleteMonster(FightSdl * fightSdl){
    int j, ind;
    Monster * monster = getActualMonsterAttackedFight(fightSdl->fight);
    ind = getIdMonster(monster)+1;
    killMonster(fightSdl->fight, monster); /*We delete the mosnter from the array*/
    
   
    /*Making sure that the ind is <= to the number of monsters and > 0 */
    assert(ind <= fightSdl->nbMstrSdl);
    assert(ind >= 0);
    if(fightSdl->nbMstrSdl == 1)
    	monsterSdlDestroy(&fightSdl->monsterSdl[0]);

    for(j = ind-1; j<fightSdl->nbMstrSdl-1;j++){ /*We start the loop from the ind ( minus one to keep first element at ind 1 )*/
    	if(fightSdl->monsterSdl[j] != NULL)
    		monsterSdlDestroy(&fightSdl->monsterSdl[j]);
        fightSdl->monsterSdl[j] = fightSdl->monsterSdl[j+1]; /*Each elements is then shifted from 1*/
        setIdMonsterSdl(fightSdl->monsterSdl[j], getIdMonsterSdl(fightSdl->monsterSdl[j])-1);
    }
    fightSdl->nbMstrSdl--; // There is now one element less

    // We redifine the size once there is enough free slots
    MonsterSdl ** tmp = fightSdl->monsterSdl; //We save the current monsters
    fightSdl->size--;
    
    fightSdl->monsterSdl = malloc(fightSdl->size*sizeof(MonsterSdl*)); //We reallocate memory
    for(j=0;j<fightSdl->nbMstrSdl;j++){
        fightSdl->monsterSdl[j] = tmp[j]; //Restoration of the saved monsters
    }
    free(tmp);
}

void updateHud(FightSdl * fightSdl){
    int i;

    fightSdl->hudSdl->nbMstr=fightSdl->nbMstrSdl;

    convertIntToChar(fightSdl->hudSdl->life, getLifePointsCharacter(fightSdl->fight->player));
    convertIntToChar(fightSdl->hudSdl->mp, fightSdl->fight->mpPlayer);
    convertIntToChar(fightSdl->hudSdl->ap, fightSdl->fight->apPlayer);
    
    for (i=0; i<fightSdl->nbMstrSdl; i++){
        convertIntToChar(fightSdl->hudSdl->lifeMonster[i], getLifePointsMonster(getElementIHorde(fightSdl->fight->horde, i))); // we convert into char the life of the monsters, to display it after 
        fightSdl->hudSdl->posMonsters[i]->x = getPosX(getCurrentPosMonsterSdl(getMonsterSdlIFromFightSdl(fightSdl, i))); //we store the position of each monster to display them life juste above them
        fightSdl->hudSdl->posMonsters[i]->y = getPosY(getCurrentPosMonsterSdl(getMonsterSdlIFromFightSdl(fightSdl, i))); //we store the position of each monster to display them life juste above them
    }
}

MonsterSdl* getMonsterSdlIFromFightSdl(FightSdl * fightSdl, int i){
	assert(i>=0);
	assert(i<fightSdl->nbMstrSdl);
	return fightSdl->monsterSdl[i];
}

void hitNRunSdl(FightSdl * fightSdl, int turn){
	hitNRun(fightSdl->fight, turn);
	Monster * monster;
	monster  = getElementIHorde(getHordeFight(fightSdl->fight), turn);

	addEventToBufferGame(fightSdl->buffer, MONSTER, getPosX(getPositionMonster(monster))*64,
						getPosY(getPositionMonster(monster))*64, turn);
}

SpellSdl* getSpellSdlIFromFightSdl(FightSdl * fightSdl, int i){
	return getSpellSdlIFromCharacSdl(fightSdl->characSdl, i);
}



