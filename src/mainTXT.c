#include "fightTxt.h"
#include "rpgTxt.h"
int main(int argc, char const *argv[]){
	srand(time(NULL));

   	// Fight* fight = fightCreateTxt("data/Init/Fight/fight1.init");
    // launchFightTxt(fight);
   	// fightDestroy(&fight);
    // exit(0);


	Rpg* rpg = loadRpgFromFile("data/Init/rpg.init");
	launchRpgTxt(rpg);
	rpgDestroy(&rpg);
	exit(0);
}


