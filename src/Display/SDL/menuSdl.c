#include "menuSdl.h"


void game(SDL_Window * screen, SDL_Renderer * renderer){
    
	Rpg * rpg = loadRpgFromFile("data/Init/rpg.init");
	RpgSdl  rpgSdl;
    rpgSdlInit(&rpgSdl, rpg, screen, renderer);

	int go = 1;
	Fight * fight;
	int id;
	while(go){
		fight = launchRpg(&rpgSdl, &id);
		if(fight != NULL){
			fightFromRpg(screen, renderer, &rpgSdl, fight, id);
		} else{
			go = 0;
		}
	}

	// menu(screen, renderer);
	saveRpgOnFile(rpg, "data/Save/rpg.save");
	rpgDestroy(&rpg);
	rpgSdlFree(&rpgSdl);
}

void initMenuSprite(MenuSdl * menuSdl, SDL_Renderer * renderer){
	menuSdl->menuSprite = loadImage("data/Image/menu.png", renderer);
	
	menuSdl->continueFalseSprite = loadImage("data/Image/continueFalse.png", renderer);
	menuSdl->newGameFalseSprite = loadImage("data/Image/newGameFalse.png", renderer);
	menuSdl->creditFalseSprite = loadImage("data/Image/creditFalse.png", renderer);
	menuSdl->quitFalseSprite = loadImage("data/Image/quitFalse.png", renderer);
	menuSdl->keyFalseSprite = loadImage("data/Image/keyFalse.png", renderer);

	menuSdl->continueTrueSprite = loadImage("data/Image/continueTrue.png", renderer);
	menuSdl->newGameTrueSprite = loadImage("data/Image/newGameTrue.png", renderer);
	menuSdl->creditTrueSprite = loadImage("data/Image/creditTrue.png", renderer);
	menuSdl->quitTrueSprite = loadImage("data/Image/quitTrue.png", renderer);
	menuSdl->keyTrueSprite = loadImage("data/Image/keyTrue.png", renderer);

	menuSdl->creditSprite = loadImage("data/Image/credits.png", renderer);
	menuSdl->commandSprite = loadImage("data/Image/command.png", renderer);
}

void menuSdlFree(MenuSdl * menuSdl){

	if (menuSdl->menuSprite != NULL){
		SDL_DestroyTexture(menuSdl->menuSprite);
		menuSdl->menuSprite = NULL;
	}

	if (menuSdl->continueTrueSprite != NULL){
		SDL_DestroyTexture(menuSdl->continueTrueSprite);
		menuSdl->continueTrueSprite = NULL;
	}

	if (menuSdl->newGameTrueSprite != NULL){
		SDL_DestroyTexture(menuSdl->newGameTrueSprite);
		menuSdl->newGameTrueSprite = NULL;
	}

	if (menuSdl->creditTrueSprite != NULL){
		SDL_DestroyTexture(menuSdl->creditTrueSprite);
		menuSdl->creditTrueSprite = NULL;
	}

	if (menuSdl->quitTrueSprite != NULL){
		SDL_DestroyTexture(menuSdl->quitTrueSprite);
		menuSdl->quitTrueSprite = NULL;
	}


	if (menuSdl->keyTrueSprite != NULL){
		SDL_DestroyTexture(menuSdl->keyTrueSprite);
		menuSdl->keyTrueSprite = NULL;
	}


	if (menuSdl->continueFalseSprite != NULL){
		SDL_DestroyTexture(menuSdl->continueFalseSprite);
		menuSdl->continueFalseSprite = NULL;
	}

	if (menuSdl->newGameFalseSprite != NULL){
		SDL_DestroyTexture(menuSdl->newGameFalseSprite);
		menuSdl->newGameFalseSprite = NULL;
	}

	if (menuSdl->creditFalseSprite != NULL){
		SDL_DestroyTexture(menuSdl->creditFalseSprite);
		menuSdl->creditFalseSprite = NULL;
	}

	if (menuSdl->quitFalseSprite != NULL){
		SDL_DestroyTexture(menuSdl->quitFalseSprite);
		menuSdl->quitFalseSprite = NULL;
	}

	if (menuSdl->keyFalseSprite != NULL){
		SDL_DestroyTexture(menuSdl->keyFalseSprite);
		menuSdl->keyFalseSprite = NULL;
	}

	if (menuSdl->commandSprite != NULL){
		SDL_DestroyTexture(menuSdl->commandSprite);
		menuSdl->commandSprite = NULL;
	}

	if (menuSdl->creditSprite != NULL){
		SDL_DestroyTexture(menuSdl->creditSprite);
		menuSdl->creditSprite = NULL;
	}

    free(menuSdl->tabButton);
}

void menuSdlInit(MenuSdl *menuSdl, SDL_Window * screen, SDL_Renderer * renderer){
 	   
	menuSdl->screen = screen;

    assert(menuSdl->screen != NULL);
    menuSdl->renderer = renderer;
    assert(menuSdl->renderer != NULL);


	initMenuSprite(menuSdl, menuSdl->renderer);

	menuSdl->tabButton = malloc(5*sizeof(int));
	menuSdl->tabButton[0]=1;
	menuSdl->tabButton[1]=0;
	menuSdl->tabButton[2]=0;
	menuSdl->tabButton[3]=0;
	menuSdl->tabButton[4]=0;

	menuSdl->currentIndex = 0;
	menuSdl->option=-1;
}

void drawMenu( MenuSdl* menuSdl){

	SDL_Rect destMenu, srcMenu, destContinue, srcContinue, destNewGame, srcNewGame, destCredit, srcCredit, destQuit, srcQuit, destKey, srcKey,srcOption, destOption;



	

	destMenu.x=0;
	destMenu.y=0;
	destMenu.w=1344;
	destMenu.h=700;

	srcMenu.x=0;
	srcMenu.y=0;
	srcMenu.w=1344;
	srcMenu.h=700;


	srcContinue.x=0;
	srcContinue.y=0;
	srcContinue.h=75;
	srcContinue.w=375;



	srcNewGame.x=0;
	srcNewGame.y=0;
	srcNewGame.h=75;
	srcNewGame.w=375;


	srcCredit.x=0;
	srcCredit.y=0;
	srcCredit.h=75;
	srcCredit.w=375;

	srcQuit.x=0;
	srcQuit.y=0;
	srcQuit.h=75;
	srcQuit.w=375;

	srcKey.x =0;
	srcKey.y=0;
	srcKey.h=178;
	srcKey.w=200;


	srcOption.x=0;
	srcOption.y=0;
	srcOption.w=WIDTH_SCREEN+1;
	srcOption.h=HEIGHT_SCREEN+1;


	destOption.x=0;
	destOption.y=0;
	destOption.h=HEIGHT_SCREEN;
	destOption.w=WIDTH_SCREEN;

	if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->menuSprite, &srcMenu, &destMenu, 0, 0, SDL_FLIP_NONE) < 0){
		printf("Error rendererMenuStatCopy\n");
	}

	if(menuSdl->tabButton[0] == 1){
		
		destContinue.x=480;
		destContinue.y=250;
		destContinue.h=85;
		destContinue.w=385;
		
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->continueTrueSprite, &srcContinue, &destContinue, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}
	else{

		destContinue.x=493;
		destContinue.y=250;
		destContinue.h=64;
		destContinue.w=358;

		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->continueFalseSprite, &srcContinue, &destContinue, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}


	if(menuSdl->tabButton[1] == 1){
		
		destNewGame.x=493;
		destNewGame.y=350;
		destNewGame.h=75;
		destNewGame.w=375;
		
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->newGameTrueSprite, &srcNewGame, &destNewGame, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}
	else{

		destNewGame.x=493;
		destNewGame.y=350;
		destNewGame.h=64;
		destNewGame.w=358;

		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->newGameFalseSprite, &srcNewGame, &destNewGame, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}

	if(menuSdl->tabButton[2] == 1){
		
		destCredit.x=493;
		destCredit.y=450;
		destCredit.h=75;
		destCredit.w=375;
		
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->creditTrueSprite, &srcCredit, &destCredit, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}
	else{

		destCredit.x=493;
		destCredit.y=450;
		destCredit.h=64;
		destCredit.w=358;

		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->creditFalseSprite, &srcCredit, &destCredit, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}

	if(menuSdl->tabButton[3] == 1){
		
		destQuit.x=493;
		destQuit.y=550;
		destQuit.h=75;
		destQuit.w=375;
		
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->quitTrueSprite, &srcQuit, &destQuit, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}
	else{

		destQuit.x=493;
		destQuit.y=550;
		destQuit.h=64;
		destQuit.w=358;

		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->quitFalseSprite, &srcQuit, &destQuit, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuStatCopy\n");
		}
	}

	if(menuSdl->tabButton[4] == 1){
		
		destKey.x=1220;
		destKey.y=590;
		destKey.h=99;
		destKey.w=110;
		
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->keyTrueSprite, &srcKey, &destKey, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuKeyCopy\n");
		}
	}
	else{

		destKey.x=1230;
		destKey.y=600;
		destKey.h=89;
		destKey.w=100;
		
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->keyFalseSprite, &srcKey, &destKey, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererMenuKeyCopy\n");
		}
	}

	if (menuSdl->option==0){

		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->creditSprite, &srcOption, &destOption, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererCreditCopy\n");
		}
	}

	if(menuSdl->option==1){
		if(SDL_RenderCopyEx(menuSdl->renderer, menuSdl->commandSprite, &srcOption, &destOption, 0, 0, SDL_FLIP_NONE) < 0){
			printf("Error rendererCommandCopy\n");
		}
	}

	SDL_RenderPresent(menuSdl->renderer);
}

int inputKeyboardMenu(SDL_Event event){
    switch (event.type){
        case SDL_QUIT:
        return QUIT;
        break;

        case SDL_KEYDOWN:
 
        switch (event.key.keysym.sym){
            
            case SDLK_UP:
            	return MOVE_UPWARD;
            break;

            case SDLK_DOWN:
            	return MOVE_DOWNWARD;
            break;

            case SDLK_RETURN:
            	return NOTHING;
            break;

            case SDLK_ESCAPE:
            	return QUIT;
            break;
        }
        break; 
    }

    return -1;
}

void menu(SDL_Window * screen, SDL_Renderer * renderer){
	MenuSdl menuSdl;
	int go, i;
	go = 1;
	menuSdlInit(&menuSdl, screen, renderer);
	while(go) {
	    i = launchMenu(&menuSdl);
	    switch(i){
	    	case NEW:
	    		newGame(menuSdl.screen, menuSdl.renderer);
	    	break;

	    	case CONTINUE:
	    		game(menuSdl.screen, menuSdl.renderer);
	    	break;

	    	case EXIT:
	    		go = 0;
	    	break;

	    	case OPTION:

	    	break;
	    }
	}
	
	menuSdlFree(&menuSdl);
}

int launchMenu(MenuSdl* menuSdl){
	SDL_Event event;
	
	Mix_Music *menuMusic;
	menuMusic = Mix_LoadMUS("data/Music/menu.mp3");
	Mix_PlayMusic(menuMusic, -1);
	int go = 1;
	int action;
	int next;
    while(go){

        drawMenu(menuSdl);
        while(SDL_PollEvent(&event)){

            action = inputKeyboardMenu(event);

            switch(action){
                case MOVE_DOWNWARD :
                menuSdl->option = -1;
                if(menuSdl->currentIndex<MAX_BUTTON){
                	menuSdl->tabButton[menuSdl->currentIndex]=0;
                	menuSdl->tabButton[menuSdl->currentIndex + 1]=1;
                	menuSdl->currentIndex++;

                }
                	
                break;

                case MOVE_UPWARD :

                menuSdl->option = -1;
                	if(menuSdl->currentIndex > 0){
                		menuSdl->tabButton[menuSdl->currentIndex]=0;
                		menuSdl->tabButton[menuSdl->currentIndex - 1]=1;
                		menuSdl->currentIndex--;
                }
                
                break;

                case NOTHING :
                	if(menuSdl->currentIndex == 0){
                		
                		if(exist("data/Save/load.load")){
                			next = CONTINUE;
                			go = 0;
                		}

                		
                	}

                	if(menuSdl->currentIndex == 1){
                		next = NEW;
                		go = 0;
                	}

                	if(menuSdl->currentIndex == 2){
                		if(menuSdl->option == 0){
                			menuSdl->option = -1;
                		}
                		else{
                			menuSdl->option=0;
                		}
                	}

                	if(menuSdl->currentIndex == 3){
                		next = EXIT;
                		go=0;
                	}

                	if(menuSdl->currentIndex == 4){
                		if(menuSdl->option == 1){
                			menuSdl->option =-1;
                		}
                		else{
                			menuSdl->option=1;
                		}
                	}
                break;
                
                case QUIT:
                	next = EXIT;
               		go=0;
                break;

                default:
                break;
            }
        }
    }

    Mix_FreeMusic(menuMusic);
    return next;
}


void newGame(SDL_Window * screen, SDL_Renderer * renderer){
	if(exist("data/Save/load.load")){
		FILE* file;
		file = fopen("data/Save/load.load", "w+");
		assert(file != NULL);
		fprintf(file, "save:0");
		fclose(file);
	}
	game(screen, renderer);
}
