#include "Character.h"
#include "Fight.h"
#include "NPC.h"
#include "AI.h"
#include "Map.h"
#include "Rpg.h"
#include "characSdl.h"
#include "dialogSdl.h"
#include "hudSdl.h"
#include "mapSdl.h"
#include "menuSdl.h"
#include "monsterSdl.h"
#include "npcSdl.h"
#include "objectSdl.h"
#include "questDiarySdl.h"
#include "rewardSdl.h"
#include "spellSdl.h"
#include <time.h>

int main(int argc, char const *argv[]){	

	spellSdlTest();
	rewardSdlTest();
	questDiarySdlTest();
	objectSdlTest();
	npcSdlTest();
	monsterSdlTest();
	mapSdlTest();
	dialogSdlTest();
	characSdlTest();
	hudSdlTest();

	characterTest();
	hordeTest();
	monsterTest();
	npcTest();
	fightTest();
	mapTest();
	positionTest();
	objsetTest();
	objectiveTest();
	questTest();
	diaryTest();
	questObjectTest();
	rewardTest();
	spellTest();
	spellBarTest();
	stuffTest();
	weaponTest();
	strTest();
	rpgTest();
	



	return 0;
}