#ifndef QUESTDIARYSDL_H
#define QUESTDIARYSDL_H


#include "QuestDiary.h"
#include "Position.h"
#include "hudSdl.h"
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH_DIARY 1344
#define HEIGHT_DIARY 700

/**
 * @struct QuestDiarySdl
 * @brief contains everything needed to display the questDiary
 */
typedef struct {
	int heightSprite; /**< The height of the sprite */
	int widthSprite; /**< The width of the sprite  */
	int id; /**< The id of the quest Diary */
	int xPix; /**< the x cooredonates  (in pixel ) */
	int yPix; /**< The y coordoante ( in pixel) */
	char* quest; /**< Name of the quest */
	char* xp; /**< Amount of xp ( in txt) */
	char* money; /**< amount of money ( in txt ) */
	char* nbMstr; /**< The number of monster ( in txt) */
	char* nbObject; /**< The number of object ( in txt ) */
	SDL_Texture* questDiarySprite; /**< The sprite of the questDiary */
	SDL_Texture* questText; /**< Texture to store text */
	SDL_Texture* xpText; /**< Texture to store text */
	SDL_Texture* moneyText; /**< Texture to store text */
	SDL_Texture* nbMstrText; /**< Texture to store text */
	SDL_Texture* nbObjectText; /**< Texture to store text */
	TTF_Font* font; /**< The font used when displaying text */
}QuestDiarySdl;

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Initialise questDiarySprites
 *
 * @param      questDiarySdl  The question diary sdl
 * @param      renderer       The renderer
 */
void initQuestDiarySprite(QuestDiarySdl * questDiarySdl, SDL_Renderer * renderer);

/**
 * @brief      Free memory
 *
 * @param      questDiarySdl  The question diary sdl
 */
void questDiarySdlFree(QuestDiarySdl * questDiarySdl);

/**
 * @brief      Initialise the questDiarySDl
 *
 * @param      questDiarySdl  The question diary sdl
 * @param      renderer       The renderer
 */
void questDiarySdlInit(QuestDiarySdl *questDiarySdl, SDL_Renderer * renderer);

/**
 * @brief      Create a questDiarySdl in the Heap.
 *
 * @param      renderer  The renderer
 *
 * @return     The questDiarySdl created
 */
QuestDiarySdl* questDiarySdlCreate(SDL_Renderer * renderer);

/**
 * @brief      Destroy the questDiarySdl
 *
 * @param      questDiarySdl  The question diary sdl
 */
void questDiarySdlDestroy(QuestDiarySdl ** questDiarySdl);

/**
 * @brief      convert a int to a char
 *
 * @param      CharNumber  The char to store the number
 * @param[in]  number      The number to convert
 */
void convertIntToChar(char* CharNumber ,int number);

/**
 * @brief      Display everything needed in the renderer
 *
 * @param      questDiarySdl  The question diary sdl
 * @param      questDiary     The question diary
 * @param      renderer       The renderer
 */
void drawQuestDiary(QuestDiarySdl* questDiarySdl,QuestDiary* questDiary, SDL_Renderer* renderer);

/**
 * @brief      Unit testing 
 */
void questDiarySdlTest();

#endif
