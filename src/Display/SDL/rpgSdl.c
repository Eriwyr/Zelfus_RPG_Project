#include "rpgSdl.h"

Fight* launchRpg(RpgSdl * rpgSdl, int * id){
    SDL_Event event;
    Fight* fight = NULL;
    Mix_Chunk *diarySound, *questSound, *pickSound;
    Mix_Music *rpgMusic;

    int go = 1;
    int action;
    int i;
    int npcId, objectId, mustFight;
    Uint32  t = SDL_GetTicks(), nt;
    
    rpgMusic = Mix_LoadMUS("data/Music/rpg.mp3"); // we load the rpg music
    Mix_PlayMusic(rpgMusic, -1); // we play music infinity

    Mix_AllocateChannels(3); // we allocate 3 channel to play a short song
    diarySound = Mix_LoadWAV("data/Music/diary.wav"); // we load the short songs
    questSound = Mix_LoadWAV("data/Music/quest.wav");
    pickSound = Mix_LoadWAV("data/Music/pick.wav");

    drawRpg(rpgSdl);

    while(go){

        mustFight=0;
        nt = SDL_GetTicks();

        checkObjectSdl(rpgSdl);
        checkQuests(rpgSdl->rpg);
        if(checkDoors(rpgSdl->rpg)){
            setcurrentPosCharacSdl(rpgSdl->characSdl, 
                getPosX(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64,
                getPosY(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64);

            clearBufferGame(rpgSdl->buffer, CHARACTER);

            changeFirstToGoBuffer(rpgSdl->buffer, 
                getPosX(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64, 
                getPosY(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64);
        }

        while(SDL_PollEvent(&event)){

            action = inputKeyboardRpg(event);


            fight = checkForFight(rpgSdl->rpg, id);
            if(fight != NULL){
                saveRpgOnFile(rpgSdl->rpg, "data/Save/rpg.save");
                go = 0;
                mustFight=1;
            }

            if(action != -1){
                 for(i=0;i<getNbNpcRpg(rpgSdl->rpg);i++){ 
                       setIsTalkingNpcSdl(rpgSdl->npcSdl[i], 0);
                       rpgSdl->npcSdl[i]->displayDialog = 0;
                }
            }

            if(action == -2 ){
                clearBufferGame(rpgSdl->buffer, CHARACTER);
            }
            switch(action){
                case MOVE_DOWNWARD :
                addActionToBufferGame(rpgSdl->buffer, DOWN);
                break;

                case MOVE_UPWARD :
                addActionToBufferGame(rpgSdl->buffer, UP);
                break;

                case MOVE_LEFT :
                addActionToBufferGame(rpgSdl->buffer, LEFT);
                break;

                case MOVE_RIGHT :
                addActionToBufferGame(rpgSdl->buffer, RIGHT);
                break;

                case TALK:
                    for(i=0;i<getNbNpcRpg(rpgSdl->rpg);i++){ 
                        if(getNbSquares(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)), getPositionNpc(getNpcIRpg(rpgSdl->rpg, i))) == 0){
                            dialogSdl(rpgSdl, getNpcIRpg(rpgSdl->rpg, i));
                            if(Mix_PlayChannel(-1,questSound,0)<0){
                                printf("error playing quest sound\n");
                            }
                        }
                    }
                break;

                case DIARY:
                    if(Mix_PlayChannel(-1, diarySound,0)<0){
                        printf("error playing diary sound\n");
                    }
                    if(rpgSdl->drawDiary == 1){
                        rpgSdl->drawDiary=0;
                    }
                    else{
                        rpgSdl->drawDiary=1;
                    }
                break;

                case PICK:
                    if(pickUpObject(rpgSdl->rpg, &npcId, &objectId)){
                        removeObjectSdlRpg(rpgSdl, npcId, objectId);
                        if(Mix_PlayChannel(-1, pickSound,0)<0){
                                 printf("error playing pick sound\n");
                        }
                    }
                break;

                case QUIT: 
                    go =0;
                break;

                default:
                break;
            }
        }
        if(nt - t > 4000){
            movingAuto(rpgSdl);
            t = nt;
        }

        updatePlayerAction(rpgSdl);
        updatePlayerDisplayRpg(rpgSdl);
        updateNpcDisplay(rpgSdl);
        drawRpg(rpgSdl);
    }

    Mix_FreeMusic(rpgMusic); // we free all songs and the music of the rpg
    Mix_FreeChunk(diarySound);
    Mix_FreeChunk(questSound);
    Mix_FreeChunk(pickSound);

    if(mustFight)
        return fight;
    return NULL;
}   

void updatePlayerDisplayRpg(RpgSdl * rpgSdl){
    int i, j, x, y, curX, curY;
    i = getIFromElmtBufferGame(rpgSdl->buffer, CHARACTER);
    Position * current;

    if(i != -1){
        setIsIdleCharacSdl(rpgSdl->characSdl, 0);
        setCurrentIndexBufferGame(rpgSdl->buffer, i); 
        x = getXBufferGame(rpgSdl->buffer, i);
        y = getYBufferGame(rpgSdl->buffer, i);
        curX = getPosX(getCurrentPosCharacSdl(rpgSdl->characSdl));
        curY = getPosY(getCurrentPosCharacSdl(rpgSdl->characSdl));
        if( curX == x && curY == y){
            j = getIndexIBufferGame(rpgSdl->buffer, i);
            removeEventFromBufferGame(rpgSdl->buffer, i);
            if(j != -1 && j != -2){
                removeActionFromBufferGame(rpgSdl->buffer, j);
            }
            
            setIsIdleCharacSdl(rpgSdl->characSdl, 1);
        } 

        else {
            current = getCurrentPosCharacSdl(rpgSdl->characSdl);
            if( (y-curY) > 0 ) {
                actionMoveSdl(getDirectionCharacSdl(rpgSdl->characSdl), current,  DOWN);
            } else if( (y-curY) < 0 ){
                actionMoveSdl(getDirectionCharacSdl(rpgSdl->characSdl), current,  UP);
            }else if( (x-curX) < 0){
                actionMoveSdl(getDirectionCharacSdl(rpgSdl->characSdl), current, LEFT);
            }else if( (x-curX) > 0){
                actionMoveSdl(getDirectionCharacSdl(rpgSdl->characSdl), current, RIGHT);
            }
        }
    }      
}

void updatePlayerAction(RpgSdl * rpgSdl){
    int action;
    action = getActionIBufferGame(rpgSdl->buffer, 0);
    if(hasBeenExcutedBufferAction(rpgSdl->buffer, 0) == 0){
        switch(action){
            case DOWN:
                movePlayerOnRpg(rpgSdl->rpg, DOWN);
            break;

            case UP:
                movePlayerOnRpg(rpgSdl->rpg, UP);
            break;

            case RIGHT:
                movePlayerOnRpg(rpgSdl->rpg, RIGHT);
            break;

            case LEFT:
                movePlayerOnRpg(rpgSdl->rpg, LEFT);
            break;

            case -1:
            break;

            default:
            break;
        }

        setExecutedBufferAction(rpgSdl->buffer, 0, 1);
        addEventToBufferGame(rpgSdl->buffer, CHARACTER, getPosX(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64, 
            getPosY(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64, 0);
            // removeEventFromBuffer(rpgSdl->buffer->action, i);
    }
}

void checkObjectSdl(RpgSdl * rpgSdl){
    int i, j;
    for(i=0;i<getNbNpcRpg(rpgSdl->rpg);i++){
        for(j=0;j<getNbObjNpcSdl(rpgSdl->npcSdl[i]);j++){
            if(isAcceptedNpc(getNpcIRpg(rpgSdl->rpg, i)))
                setDisplayObjectSdl(getObjectSdlINpcSdl(rpgSdl->npcSdl[i], j), 1);
        }
    }
}

void updateNpcDisplay(RpgSdl * rpgSdl){
    int i, x, y , curX, curY, j;
    NpcSdl * npc;
    Position * current;
        
    i = getIFromElmtBufferGame(rpgSdl->buffer, _NPC);

        if(i != -1){


            setCurrentIndexBufferGame(rpgSdl->buffer, i);
            j = getIndexIBufferGame(rpgSdl->buffer, i);

            npc = rpgSdl->npcSdl[j];
            setIsIdleNpcSdl(npc, 0);
            x = getXBufferGame(rpgSdl->buffer, i);
            y = getYBufferGame(rpgSdl->buffer, i);
            curX = getPosX(getCurrentPosNpcSdl(npc));
            curY = getPosY(getCurrentPosNpcSdl(npc));
            if( curX == x && curY == y){
                    removeEventFromBufferGame(rpgSdl->buffer, i);
                    setIsIdleNpcSdl(npc, 1);
            } 

            else {
                current = getCurrentPosNpcSdl(npc);
                if( (y-curY) > 0 ) {
                    actionMoveSdl(getDirectionNpcSdl(npc), current, DOWN);
                } else if( (y-curY) < 0 ){
                    actionMoveSdl(getDirectionNpcSdl(npc), current, UP);
                }else if( (x-curX) < 0){
                    actionMoveSdl(getDirectionNpcSdl(npc), current, LEFT);
                }else if( (x-curX) > 0){
                    actionMoveSdl(getDirectionNpcSdl(npc), current, RIGHT);
                }
            }
        } 
}

void rpgSdlInit(RpgSdl * rpgSdl, Rpg * rpg, SDL_Window * screen, SDL_Renderer * renderer){
	

    int i;
    rpgSdl->screen = screen;
    assert(rpgSdl->screen != NULL);
    
    rpgSdl->renderer = renderer;
    assert(rpgSdl->renderer != NULL);

    rpgSdl->rpg = rpg;
    rpgSdl->mapSdl = mapSdlCreate("data/Image/mapTileset1.png", rpgSdl->renderer);
    rpgSdl->characSdl = characSdlCreate(getCharacterRpg(rpgSdl->rpg), rpgSdl->renderer);
    rpgSdl->buffer = bufferGameCreate();
    rpgSdl->nbNpc = getNbNpcRpg(rpg);
    rpgSdl->diarySdl = questDiarySdlCreate(rpgSdl->renderer);
    rpgSdl->drawDiary = 0;
    rpgSdl->nbMstr = getNbMstrRpg(rpg);
    rpgSdl->size = getNbMstrRpg(rpg);
    rpgSdl->monsterSdl = malloc(rpgSdl->nbMstr*sizeof(MonsterSdl*));
    rpgSdl->npcSdl = malloc(rpgSdl->nbNpc*sizeof(NpcSdl*));
    for(i=0;i<rpgSdl->nbNpc;i++){
        rpgSdl->npcSdl[i] = npcSdlCreate(getNpcIRpg(rpg, i), rpgSdl->renderer);
    }
    for(i=0;i<rpgSdl->nbMstr;i++){
        rpgSdl->monsterSdl[i] = monsterSdlCreate(getPositionMonsterRpg(getMonsterRpgIRpg(rpg, i)), rpgSdl->renderer);
    }
}  

RpgSdl*  rpgSdlCreate(Rpg * rpg, SDL_Window * screen, SDL_Renderer * renderer) {
    RpgSdl * rpgSdl;

    rpgSdl = malloc(sizeof(RpgSdl));
    rpgSdlInit(rpgSdl, rpg, screen, renderer);

    return rpgSdl;
}

void rpgSdlFree(RpgSdl * rpgSdl){
    int i;
    if (rpgSdl->mapSdl !=NULL){
        mapSdlDestroy(&(rpgSdl->mapSdl));
    }
    characSdlDestroy(&(rpgSdl->characSdl));
    questDiarySdlDestroy(&(rpgSdl->diarySdl));
    for(i = 0; i<rpgSdl->nbMstr;i++){
        if(rpgSdl->monsterSdl[i] != NULL){
            monsterSdlDestroy(&rpgSdl->monsterSdl[i]);
        }
    }
    free(rpgSdl->monsterSdl);
    for(i=0;i<rpgSdl->nbNpc;i++){
        if(rpgSdl->npcSdl[i] !=NULL){
            npcSdlDestroy(&rpgSdl->npcSdl[i]);
        }
    }
    free(rpgSdl->npcSdl);
    bufferGameDestroy(&(rpgSdl->buffer));
}

void rpgSdlDestroy(RpgSdl ** rpgSdl){
    rpgSdlFree(*rpgSdl);
    free(*rpgSdl);
    *rpgSdl = NULL;
}

int inputKeyboardRpg(SDL_Event event){
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

            case SDLK_y:
            return YES;
            break;

            case SDLK_n:
            return NO;
            break;

            case SDLK_j:
                return DIARY;
            break;

            case SDLK_t:
                return TALK;
            break;

            case SDLK_p:
                return PICK;
            break;

            case SDLK_ESCAPE:
            return QUIT;
            break;
        }
        break; 

        case SDL_KEYUP:
            switch (event.key.keysym.sym){
                case SDLK_z:
                return -2;
                break;

                case SDLK_s:
                return -2;
                break;

                case SDLK_q:
                return -2;
                break;

                case SDLK_d:
                return -2;
                break;

                default:
                return -1;
                break;
            }
        break;
    }

    return -1;
}

void drawRpg(RpgSdl* rpgSdl){
    int i, j;
    // 
    // SDL_RenderClear(rpgSdl->renderer);
    SDL_SetRenderDrawColor( rpgSdl->renderer, 230, 0, 0, 0);
    drawImage(getBackground(rpgSdl->mapSdl), 0, 0, rpgSdl->renderer);
    rpgInitSecondMap(rpgSdl->rpg);
    drawMap(rpgSdl->mapSdl,getMapRpg(rpgSdl->rpg), rpgSdl->renderer);
    drawPlayer(rpgSdl->characSdl, rpgSdl->renderer);

    for(i = 0; i < rpgSdl->nbMstr; i++){
        if( getRoomIdMonsterRpg(getMonsterRpgIRpg(rpgSdl->rpg, i)) == getIdMap(getMapRpg(rpgSdl->rpg)) )
            drawMonster(rpgSdl->monsterSdl[i], rpgSdl->renderer);
    }
    for(i = 0; i<rpgSdl->nbNpc; i++){
        if(getIdMap(getMapRpg(rpgSdl->rpg)) == getRoomIdNpc(getNpcIRpg(rpgSdl->rpg, i)))
            drawNpc(rpgSdl->npcSdl[i], rpgSdl->renderer);
        for(j=0;j<getNbObjNpcSdl(rpgSdl->npcSdl[i]);j++){
            if(getDisplayObjectSdl(getObjectSdlINpcSdl(rpgSdl->npcSdl[i], j))){
                if(getIdMap(getMapRpg(rpgSdl->rpg)) == getRoomIdObject(getObjectIObjset(getObjectsObjective(getObjectiveQ(getQuestNpc(getNpcIRpg(rpgSdl->rpg, i)))), j)))
                    drawObject(getObjectSdlINpcSdl(rpgSdl->npcSdl[i], j), rpgSdl->renderer);
            }
        }
        if(rpgSdl->npcSdl[i]->displayDialog == 1)
            drawDialog(getDialogNpcSdl(rpgSdl->npcSdl[i]), getDialogNpc(getNpcIRpg(rpgSdl->rpg, i)), getCurrentPosNpcSdl(rpgSdl->npcSdl[i]), rpgSdl->renderer);
    }



    if(rpgSdl->drawDiary==1){
        drawQuestDiary(rpgSdl->diarySdl, getDiaryCharacter(getCharacterRpg(rpgSdl->rpg)), rpgSdl->renderer);
    }
    
    SDL_Delay(12);
    SDL_RenderPresent(rpgSdl->renderer);
}

void dialogSdl(RpgSdl * rpgSdl, NPC * npc){
    int i = getIdFromNpc(rpgSdl->rpg, npc);
    setIsTalkingNpcSdl(rpgSdl->npcSdl[i], 1);
    setDisplayDialogNpcSdl(rpgSdl->npcSdl[i], 1);
    talkToNpc(rpgSdl->rpg, npc);
}

void fightFromRpg(SDL_Window * screen, SDL_Renderer * renderer, RpgSdl* rpgSdl, Fight * fight, int id){
    FightSdl fightSdl;
    Mix_Chunk *winSound, *looseSound;
    int i;
    int win;
    RewardSdl rewardSdl;
    int x, y;
    int nbMstrKilled, nbMstrQuest;
    fightSdlInit(&fightSdl, screen, renderer, fight);
    
    Mix_AllocateChannels(3);
    winSound = Mix_LoadWAV("data/Music/win.wav");
    looseSound = Mix_LoadWAV("data/Music/loose.wav");

    x = getPosX(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)));
    y = getPosY(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)));
    win = launchFight(&fightSdl);

    setPositionCharacter(getCharacterRpg(rpgSdl->rpg), x, y);
    nbMstrKilled = getNbMstrKilledFight(fightSdl.fight);
    fightSdlFree(&fightSdl);
    rewardSdlInit(&rewardSdl, renderer);
    
    if(win == 1){           
        
        drawReward(&rewardSdl, 1, renderer);
        SDL_RenderPresent(renderer);
        
        if(Mix_PlayChannel(-1,winSound,0)<0){
            printf("error playing win sound\n"); //we play the win sound
        }

        for(i=0;i<getNbQuestDiary(getDiaryCharacter(getCharacterRpg(rpgSdl->rpg)));i++){
            nbMstrQuest = getNbMstrObjective(getObjectiveQ(getQuestIDiary(getDiaryCharacter(getCharacterRpg(rpgSdl->rpg)), i)));
            while(nbMstrQuest > 0 && nbMstrKilled > 0){
                nbMstrQuest--;
                nbMstrKilled--;
            }
            setNbMstrObjective(getObjectiveQ(getQuestIDiary(getDiaryCharacter(getCharacterRpg(rpgSdl->rpg)), i)), nbMstrQuest);
        }

        SDL_Event event;
        SDL_WaitEvent(&event);  // we waiting that the player press enter to continue
        removeMonsterSdlIRpg(rpgSdl, id+1);
        removeMonsterRpgI(rpgSdl->rpg, id+1);
    } else {
        drawReward(&rewardSdl, 0, renderer);
        SDL_RenderPresent(renderer);
        
        if(Mix_PlayChannel(-1,looseSound,0)<0){
            printf("error playing loose sound\n"); 
        }

        SDL_Event event;
        SDL_WaitEvent(&event);  // we waiting that the player press enter to continue
        removeMonsterSdlIRpg(rpgSdl, id+1);
        removeMonsterRpgI(rpgSdl->rpg, id+1);
    } 
    // fightDestroy(&fight); 
     clearCharacBuffer(rpgSdl->buffer);
     setIsIdleCharacSdl(rpgSdl->characSdl, 1);
     setcurrentPosCharacSdl(rpgSdl->characSdl, 
                getPosX(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64,
                getPosY(getPositionCharacter(getCharacterRpg(rpgSdl->rpg)))*64);
    

    rewardSdlFree(&rewardSdl);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(looseSound);
}

void movingAuto(RpgSdl * rpgSdl){
    int i;
    i = 0;
    NPC* npc;
    npc = getNpcIRpg(rpgSdl->rpg, i);
    i = moveNpcRandom(rpgSdl->rpg);
    npc = getNpcIRpg(rpgSdl->rpg, i);
    addEventToBufferGame(rpgSdl->buffer, _NPC, getPosX(getPositionNpc(npc))*64,
                                getPosY(getPositionNpc(npc))*64, i);
}

void removeMonsterSdlIRpg(RpgSdl * rpgSdl, int ind){
    int j;
    /*Making sure that the ind is <= to the number of monsters and > 0 */
    assert(ind <= rpgSdl->nbMstr);
    assert(ind > 0);
    if(rpgSdl->nbMstr == 1)
         monsterSdlDestroy(&rpgSdl->monsterSdl[0]);
    for(j = ind-1; j<rpgSdl->nbMstr-1;j++){ /*We start the loop from the ind ( minus one to keep first element at ind 1 )*/
        if(rpgSdl->monsterSdl[j] != NULL)
            monsterSdlDestroy(&rpgSdl->monsterSdl[j]);
        rpgSdl->monsterSdl[j] = rpgSdl->monsterSdl[j+1]; /*Each elements is then shifted from 1*/
    }
    rpgSdl->nbMstr--; // There is now one element less

    // We redifine the size once there is enough free slots
    MonsterSdl ** tmp = rpgSdl->monsterSdl; //We save the current monsters
    rpgSdl->size--;
    rpgSdl->monsterSdl = malloc(rpgSdl->size*sizeof(MonsterSdl*)); //We reallocate memory
    for(j=0;j<rpgSdl->nbMstr;j++){
        rpgSdl->monsterSdl[j] = tmp[j]; //Restoration of the saved monsters
    }
    free(tmp);
}

void removeObjectSdlRpg(RpgSdl * rpgSdl, int i, int j){
    NpcSdl * npcSdl;

    if(i != -1 && j != -1){
        npcSdl =  rpgSdl->npcSdl[i];
        removeObjectSdlNpcSdl(npcSdl, j+1);
    }
}