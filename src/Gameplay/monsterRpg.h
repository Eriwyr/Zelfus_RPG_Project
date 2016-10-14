#ifndef MONSTERRPG_H
#define MONSTERRPG_H

#include "Fight.h"
#include "OS.h"

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
 * @struct MonsterRpg
 * @brief contain everything to manage the monsters which appears in the rpg
 */
typedef struct{
	int id;
	Fight * fight;
	int idRoom;
	Position * pos;
} MonsterRpg;

void monsterRpgInit(MonsterRpg * monsterRpg);
MonsterRpg* monsterRpgCreate();
void setPositionMonsterRpg(MonsterRpg* monsterRpg, int x, int y);
Position* getPositionMonsterRpg(const MonsterRpg* monsterRpg);
Fight* getFightMonsterRpg(const MonsterRpg* monsterRpg);
MonsterRpg* loadMonsterRpgFromFile(char* fileName, Character* player);
void monsterRpgDestroy(MonsterRpg ** monsterRpg);
int getIdMonsterRpg(const MonsterRpg* monsterRpg);
void setIdMonsterRpg(MonsterRpg* monsterRpg, const int id);
void saveMonsterRpgOnFile(MonsterRpg* monsterRpg, char* fileName);
int getRoomIdMonsterRpg(const MonsterRpg* monsterRpg);
#endif 