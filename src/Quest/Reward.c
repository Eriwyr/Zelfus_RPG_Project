#include "Reward.h"


void rewardInit(Reward * reward, int money, int xp){
	reward->money = money;
	reward->xp = xp;
	
}

void rewardFree(Reward * reward){

	reward->money = 0;
	reward->xp = 0;
}

Reward* rewardCreate(int money, int xp){
	Reward * reward;
	reward = malloc(sizeof(Reward));

	rewardInit(reward, money, xp);
	return reward;
}

void rewardDestroy(Reward ** reward){
	rewardFree(*reward);
	free(*reward);
	*reward = NULL;
}



int getMoneyReward(const Reward * reward){
	return reward->money;
}
int getXpReward(const Reward * reward){
	return reward->xp;
}


void rewardTest(){
	Reward reward;
	Reward * pReward;

	printf("==== Tests of Reward ====\n");

	printf("Initalisation using rewardInit()... ");
	rewardInit(&reward, 50, 120);
	assert(reward.money == 50);
	assert(reward.xp == 120);
	printf("Ok.\n");

	printf("Initalisation using rewardCreate()... ");
	pReward = rewardCreate(13, 58);
	assert(pReward->money == 13);
	assert(pReward->xp == 58);
	printf("Ok.\n");

	

	printf("Freeing reward... ");
	rewardFree(&reward);
	printf("Ok.\n");

	printf("Freeing pReward... ");
	rewardDestroy(&pReward);
	assert(pReward == NULL);
	printf("Ok.\n");

	printf("==== The tests went well ====\n\n");
}