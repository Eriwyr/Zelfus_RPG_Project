#ifndef REWARDSDL_H
#define REWARDSDL_H


#include "Position.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH_REWARD 844
#define HEIGHT_REWARD 640

/**
 * @struct RewardSdl
 * @brief contain everything that we want to display after fight
 */
typedef struct {
	int heightSprite, widthSprite;
	int id, xPix, yPix;
	char* xp;
	char* money;
	SDL_Texture* rewardWinSprite;
	SDL_Texture* rewardLooseSprite;
	SDL_Texture* xpText;
	SDL_Texture* moneyText;
	TTF_Font* font; 

}RewardSdl;

void rewardSdlInit(RewardSdl *rewardSdl, SDL_Renderer * renderer);
void drawReward(RewardSdl* rewardSdl,int issue, SDL_Renderer* renderer);
SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

void initRewardSprite(RewardSdl * rewardSdl, SDL_Renderer * renderer);

void rewardSdlFree(RewardSdl * rewardSdl);

void rewardSdlInit(RewardSdl *rewardSdl, SDL_Renderer * renderer);

RewardSdl* rewardSdlCreate(SDL_Renderer * renderer);

void rewardSdlDestroy(RewardSdl ** rewardSdl);

void drawReward(RewardSdl* rewardSdl,int issue, SDL_Renderer* renderer);

void rewardSdlTest();

#endif