#include "rpgTxt.h"

int inputKeyboardRpgTxt(){
	char a;
	char clear;
	do{
		a = getchar();
	} while(a == '\n');
	
	clear = getchar(); //To delete the \n from the buffer when we press enter.
	switch (a){
		case 'z':
		return MOVE_UPWARD;
		break;

		case 's':
		return MOVE_DOWNWARD;
		break;

		case 'q':
		return MOVE_LEFT;
		break;

		case 'd':
		return MOVE_RIGHT;
		break;

		case 'p':
		return PICK;
		break;

		case 'y':
		return YES;
		break;

		case 'n':
		return NO;
		break;

		case 't':
		return TALK;
		break;

		case 'j':
		return DIARY;

		case '=':
		return -2;
		break;

		case '\n':
			return -1;
	}

	return -1;
	if(clear)
		;
}

void drawRpgTxt(Rpg * rpg){
	clear();
	setMapTxt(getMapRpg(rpg));
	setPlayerTxt(getCharacterRpg(rpg), getMapRpg(rpg));
	setNpcTxt(rpg);
	// setMonsterTxt(rpg->horde, getMapRpg(rpg));
	drawMapTxt(getMapRpg(rpg));
}

void drawDiaryTxt(Rpg * rpg){
	clear();
	int open = 1;
	int i, a, nbMstr, nbObj;
	QuestDiary* diary = getDiaryCharacter(getCharacterRpg(rpg));
	printf("Your Quest Diary\n");
	while(open){
		for(i=0;i<getNbQuestDiary(diary);i++){
			printf("Quest number %d : \n", i+1);
			printf("%s", getNameQ(getQuestIDiary(diary, i)));
			nbMstr = getNbMstrObjective(getObjectiveQ(getQuestIDiary(diary, i)));
			if(nbMstr > 0)
				printf("Objective :\n \tYou have to kill %d monsters\n", nbMstr);
			else 
				printf("Objective :\n \tNo monsters to kill\n");
			nbObj = getNbObjSet(getObjectsObjective(getObjectiveQ(getQuestIDiary(diary, i))));
			if(nbObj > 0)
				printf("\tYou have to pick %d objects\n", nbObj);
			else 
				printf("\tNo objects to pick");
			printf("\n");
		} 
		a = inputKeyboardRpgTxt();
		if(a == DIARY)
			open = 0;
	}
	// drawRpgTxt(rpg);
}

void setNpcTxt(Rpg * rpg){
	int i, j, x, y;
	ObjectSet * set;
	// Horde * horde;
	for(i=0;i<getNbNpcRpg(rpg);i++){
		x = getPosX(getPositionNpc(getNpcIRpg(rpg, i)));
		y = getPosY(getPositionNpc(getNpcIRpg(rpg, i)));
		setElementXYMap(getMapRpg(rpg), x, y, 4);

		set = getObjectsObjective(getObjectiveQ(getQuestNpc(getNpcIRpg(rpg, i))));
		for(j=0;j<getNbObjSet(set);j++){
			if(getIdMap(getMapRpg(rpg)) == getRoomIdObject(getObjectIObjset(set, j))){
				if(isAcceptedNpc(getNpcIRpg(rpg, i))){
					x = getPosX(getPositionObject(getObjectIObjset(set, j)));
					y = getPosY(getPositionObject(getObjectIObjset(set, j)));
					setElementXYMap(getMapRpg(rpg), x, y, 6);
				}
				
			}
		}
		// for(j=0;j<rpgSdl->rpg->nbMstr;j++){
		// 	if(isAcceptedNpc(getNpcIRpg(rpgSdl->rpg, i))){
		// 		if(getIdMap(rpgSdl->rpg->map) == rpgSdl->rpg->monsters[j]->idRoom){
		// 			if(isAcceptedNpc(getNpcIRpg(rpgSdl->rpg->monsters[j], i))){
		// 				x = getPosX(rpg->monsters[j]->pos);
		// 				y = getPosY(rpg->monsters[j]->pos);
		// 				setElementXYMap(rpg->map, x, y, 7);
		// 			}
		// 		}
		// 	}
		// }
		// for(j=0;j<)
	}
}

void dialogueTxt(Rpg * rpg, NPC * npc){
	int a;
	// printf("%s\n", getDialogNpc(npc));
	if(talkToNpc(rpg, npc))
		printf("%s\n", getDialogNpc(npc));
	else {
		printf("%s", getDialogNpc(npc));
		printf("Will you accept the quest ? \n");
		a = inputKeyboardRpgTxt();
		switch (a){
			case YES:
			acceptQuest(rpg, npc);
			drawRpgTxt(rpg);
			printf("%s\n", getDialogNpc(npc));
			break;
			case NO:
			break;
			default:
			printf("%d\n", a);
			break;
		}
	}	
}

void launchRpgTxt(Rpg * rpg){
	int go, action, i;
	go = 1;
	drawRpgTxt(rpg);
	int k, j;
	while(go){
		action = inputKeyboardRpgTxt();
		checkQuests(rpg);
		switch(action){
			case MOVE_DOWNWARD :
				movePlayerOnRpg(rpg, DOWN);
			break;

			case MOVE_UPWARD :
				movePlayerOnRpg(rpg, UP);
			break;

			case MOVE_LEFT :
				movePlayerOnRpg(rpg, LEFT);
			break;

			case MOVE_RIGHT :
				movePlayerOnRpg(rpg, RIGHT);
			break;

			case TALK:
			for(i=0;i<getNbNpcRpg(rpg);i++){
					if(getNbSquares(getPositionCharacter(getCharacterRpg(rpg)), getPositionNpc(getNpcIRpg(rpg, i))) == 0)
						dialogueTxt(rpg, getNpcIRpg(rpg, i));
				}
			break;

			case DIARY:
				drawDiaryTxt(rpg);
			break;

			case PICK:
					pickUpObject(rpg, &k, &j);
			break;

			case -2:
				go =0;
			break;

			default:
			break;
		}	
		drawRpgTxt(rpg)	;
	}
}