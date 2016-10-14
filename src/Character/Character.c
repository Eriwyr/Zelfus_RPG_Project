#include "Character.h"

void characterInit(Character * player){
	int i;

	player->id=0;
	player->name = strdup("player");
	player->lifePoints = 15;
	player->weapon = weaponCreate("basic sword", 5, 0, 0, 0, 1, 0);
	player->stuffs = malloc(4*sizeof(Stuff*));
	for(i=0;i<4;i++){
		player->stuffs[i] = stuffCreate("basic stuff", 1, 2, 3, 0);
	}
	player->spellBar = spellBarCreate();
	player->strength = 12;
	player->intelligence = 10;
	player->wisdom = 11;
	player->diary = diaryCreate();
	player->money = 0;
	player->level = 1;
	player->xp = 0;
	player->pos = malloc(sizeof(Position));
	setPosX(player->pos, 0);
	setPosY(player->pos, 0);

}

Character* characterCreate(){
	Character * player;
	player = malloc(sizeof(Character));

	characterInit(player);

	return player;
}

void characterFree(Character * player){
	int i;
	if(player->name!=NULL){
		free(player->name);
	}
	player->name = NULL;
	
	for(i=0;i<4;i++){
		stuffDestroy(&player->stuffs[i]);
	}
	free(player->stuffs);
	weaponDestroy(&player->weapon);
	diaryDestroy(&player->diary); 
	spellBarDestroy(&player->spellBar);
	free(player->pos);
}

void characterDestroy(Character ** player){
	characterFree(*player);
	free(*player);
	*player = NULL;
}

char* getNameCharacter(const Character* player){
	return player->name;
}

void setIdCharacter(Character* player, int id){
	player->id =id;
}

int getIdCharacter(const Character* player){
	return player->id;

}
void setNameCharacter(Character* player, char* name){
	free(player->name);
	player->name = strdup(name);
}


int getLifePointsCharacter(const Character* player){
	return player->lifePoints;
}

void setLifePointsCharacter(Character* player, int lifePoints){
	player->lifePoints = lifePoints;
}


Weapon* getWeaponCharacter(const Character* player){
	return player->weapon;
}

void setWeaponCharacter(Character* player, Weapon* weapon){
	weaponDestroy(&player->weapon);
	player->weapon = weapon;
}


Stuff** getSutffsCharacter(const Character* player){
	return player->stuffs;
}

Stuff* getStuffICharacter(const Character* player, int i){
	assert(i>=0);
	assert(i<4);
	return player->stuffs[i];
}

void setSutffICharacter(Character* player, Stuff* stuffs, int i){
	stuffDestroy(&player->stuffs[i]);
	player->stuffs[i] = stuffs;
}


SpellBar* getSpellBarCharacter(const Character* player){
	return player->spellBar;
}

void setSpellBarCharacter(Character* player, SpellBar* spellBar){
	spellBarDestroy(&player->spellBar);
	player->spellBar = spellBar;
}


int getStrengthCharacter(const Character* player){
	return player->strength;
}

void setStrengthCharacter(Character* player, int strength){
	player->strength = strength;
}


int getIntelligenceCharacter(const Character* player){
	return player->intelligence;
}

void setIntelligenceCharacter(Character* player, int intelligence){
	player->intelligence = intelligence;
}


int getWisdomCharacter(const Character* player){
	return player->wisdom;
}

void setWisdomCharacter(Character* player, int wisdom){
	player->wisdom = wisdom;
}


QuestDiary* getDiaryCharacter(const Character* player){
	return player->diary;
}

void setDiaryCharacter(Character* player, QuestDiary* diary){
	diaryDestroy(&player->diary);
	player->diary = diary;
}


int getMoneyCharacter(const Character* player){
	return player->money;
}

void setMoneyCharacter(Character* player, int money){
	player->money = money;
}


int getLevelCharacter(const Character* player){
	return player->level;
}

void setLevelCharacter(Character* player, int level){
	player->level = level;
}


Position* getPositionCharacter(const Character* player){
	return player->pos;
}

void setPositionCharacter(Character* player,int x, int y){
	setPosX(player->pos, x);
	setPosY(player->pos, y);
}


int getXpCharacter(const Character* player){
	return player->xp;
}

void setXpCharacter(Character* player, const int xp){
	if(player->level == 100)
		player->xp = xp;
	else 
		if(player->xp >= amountToNewLevel(player->level)){
			player->xp -=  amountToNewLevel(player->level);
			levelUp(player); 

		}
}

Character* loadCharacterFromFile(char* fileName){
	FILE* file;
	Character * player; 
	char name[CHAR_SIZE_MAX];
	int weaponId, stuffId, i;
	char weaponIdTxt[10], stuffIdTxt[10];
	char weaponFile[CHAR_SIZE_MAX], stuffFile[CHAR_SIZE_MAX];
	char *nameP;
	Position pos;


	#ifdef WINDOWS_OS
		strreplace(fileName, '/', '\\');
	#endif
	
	file = fopen(fileName, "r");
	assert(file != NULL);

	player=characterCreate();

	fscanf(file, "name:");
	fgets(name, CHAR_SIZE_MAX, file);
	nameP = strdup(name);
	strremoveEOL(nameP);
	setNameCharacter(player, nameP);
	fscanf(file, "lifePoints:%d\n", &player->lifePoints);
	fscanf(file, "strength:%d\n", &player->strength);
	fscanf(file, "intelligence:%d\n", &player->intelligence);
	fscanf(file, "wisdom:%d\n", &player->wisdom);
	fscanf(file, "money:%d\n", &player->money);
	fscanf(file, "level:%d\n", &player->level);
	fscanf(file, "xp:%d\n", &player->xp);
	fscanf(file, "x:%d  y:%d\n", &pos.x, &pos.y);
	setPositionCharacter(player, pos.x, pos.y);
	fscanf(file, "weaponId:%d\n", &weaponId);
	sprintf(weaponIdTxt, "%d", weaponId);

	if(exist("data/Save/load.load")){
		strcpy(weaponFile, "data/Init/Weapon/weapon");
		strcat(weaponFile, weaponIdTxt);
		strcat(weaponFile, ".init");
	} else {
		strcpy(weaponFile, "data/Init/Weapon/weapon");
		strcat(weaponFile, weaponIdTxt);
		strcat(weaponFile, ".init");
	}
	
	setWeaponCharacter(player, loadWeaponFromFile(weaponFile));

	if(exist("data/Save/load.load")){
		setDiaryCharacter(player, loadQuestDiaryFromFile("data/Save/Character/questDiary.save"));
		setSpellBarCharacter(player, loadSpellBarFromFile("data/Save/Character/spellBar.save"));
	} else {
		setDiaryCharacter(player, loadQuestDiaryFromFile("data/Init/Character/questDiary.init"));
		setSpellBarCharacter(player, loadSpellBarFromFile("data/Init/Character/spellBar.init"));
	}
	

	fscanf(file, "Stuffs:\n");
	for(i=0;i<4;i++){
		fscanf(file, "id:%d", &stuffId);
		sprintf(stuffIdTxt, "%d", stuffId);
		strcpy(stuffFile, "data/Init/Stuff/stuff");
		strcat(stuffFile, stuffIdTxt);
		strcat(stuffFile, ".init");
		setSutffICharacter(player, loadStuffFromFile(stuffFile), i);
	}

	free(nameP);
	fclose(file);
	return player;
}

void saveCharacterOnFile(Character * player, char* fileName){
	FILE* file;
	int i;


	#ifdef WINDOWS_OS
		strreplace(fileName, "/", "\\");
	#endif

	file = fopen(fileName, "w+");
	assert(file != NULL);

	fprintf(file, "name:%s\n", player->name);
	fprintf(file, "lifePoints:%d\n", player->lifePoints);
	fprintf(file, "strength:%d\n", player->strength);
	fprintf(file, "intelligence:%d\n", player->intelligence);
	fprintf(file, "wisdom:%d\n", player->wisdom);
	fprintf(file, "money:%d\n", player->money);
	fprintf(file, "level:%d\n", player->level);
	fprintf(file, "xp:%d\n", player->xp);
	fprintf(file, "x:%d  y:%d\n", getPosX(player->pos), getPosY(player->pos));
	fprintf(file, "weaponId:%d\n", getIdWeapon(player->weapon));
	fprintf(file, "\n");

	fprintf(file, "Stuffs:");
	for(i=0;i<4;i++){
		fprintf(file, "\nid:%d", getIdStuff(player->stuffs[i]));
	}
	
	saveQuestDiaryOnFile(player->diary, "data/Save/Character/questDiary.save");
	saveSpellBarOnFile(player->spellBar, "data/Save/Character/spellBar.save");
	fclose(file);
}

int amountToNewLevel(int level){
	int amountXp;
	if(level > 0 && level < 15)
		amountXp = (int) (pow(level, 3) * ((24 + floor((level + 4) / 3 )) / 50));
	if(level >= 16 && level <= 35)
		amountXp = (int) (pow(level, 3) * ((14+level)/50));
	if(level >= 36 && level <= 100)
		amountXp = (int) (pow(level, 3) * ((32 + floor((level/2))) / 50 ));
	if(level > 100)
		return -1;
	return amountXp;
}


void levelUp(Character * player){
	player->level++;
	player->lifePoints++;
	player->strength++;
	player->intelligence++;
	player->wisdom++;
}


int attackMonster(Character * player, Monster * monster){
	int damage, range, distance;
	damage = getDamageWeapon(player->weapon);
	damage += player->strength;
	damage -= getStrengthResMonster(monster);
	range = getRangeWeapon(player->weapon);
	distance = getNbSquares(getPositionCharacter(player), getPositionMonster(monster))+1;
	if(distance <= range){
		setLifePointsMonster(monster, getLifePointsMonster(monster)-damage);
		if(getLifePointsMonster(monster) < 0)
			setLifePointsMonster(monster, 0);
		return 1;
	}
	return 0;	
}

int attackMonsterSpell(Character* player, Monster* monster, Spell* spell){	
	int damage, range;
	damage = getDamageSpell(spell);
	
	damage += player->intelligence;
	damage -= getIntellResMonster(monster);
	range = getRangeSpell(spell);

	if( (getPosX(getPositionCharacter(player)) - getPosX(getPositionMonster(monster)) )<=range || (getPosX(getPositionCharacter(player)) - getPosX(getPositionMonster(monster))) >= -range || (getPosX(getPositionCharacter(player)) - getPosX(getPositionMonster(monster)) )<=range || (getPosY(getPositionCharacter(player)) - getPosY(getPositionMonster(monster)) ) >= -range){

	
	
	setLifePointsMonster(monster, getLifePointsMonster(monster)-damage);
		if(getLifePointsMonster(monster) < 0)
			setLifePointsMonster(monster, 0);
		return 1;
	}
	return 0;
}
void characterTest(){
	Character charac;
	Character *pCharac;
	printf("==== Tests of Character ====\n");
	
	printf("Initializing using characterInit... ");
	characterInit(&charac);
	assert(strcmp(charac.name, "player") == 0);
	assert(sizeof(charac.stuffs) == sizeof(4*sizeof(Stuff*)));
	printf("Ok.\n");
	
	printf("Initializing using characterCreate... ");
	pCharac = characterCreate();
	assert(strcmp(pCharac->name, "player") == 0);
	assert(sizeof(pCharac->stuffs) == sizeof(4*sizeof(Stuff*)));
	printf("Ok.\n");
	
	
	
	printf("Freeing charac... ");
	characterFree(&charac);
	// assert(charac.name == NULL);
	printf("Ok.\n");
	
	printf("Freeing pCharac... ");
	characterDestroy(&pCharac);
	assert(pCharac == NULL);
	printf("Ok.\n");
	

	printf("Test of loadCharacterFromFile()... ");
	Character* player;
	player = loadCharacterFromFile("data/Init/Character/character.init");
	saveCharacterOnFile(player, "data/Init/Character/character1.init");

	characterDestroy(&player);
	printf("Ok.\n");
	

	printf("====The tests went well ====\n\n");
}


