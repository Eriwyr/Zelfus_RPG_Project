#ifndef MONSTERSDL_H
#define MONSTERSDL_H

#define TIME_BETWEEN_2_FRAMES_MONSTER 8

#define MONSTER_WIDTH 32
#define MONSTER_HEIGTH 32

#include "Monster.h"
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * @struct MonsterSdl
 * @brief contain everything to display monsters
 */
typedef struct {
	int heightSprite; /**< the height of the sprite*/
	int widthSprite; /**< the width of the sprite */
	int frameNumber; /**< the frame number */
	int frameTimer; /**< the frame timer */
	int frameMax; /**< the frame maximum */
	int direction; /**< the direction of the monster */
	Position * currentPos; /**< the current position of the monster ( pix ) */
	int isIdle; /**< Boolean to see if the monster is moving */
	int id; /**< Id of the monster */

	SDL_Texture* monsterSpriteSheet;
}MonsterSdl;

/**
 * @brief      initialise the sprites of the monster
 *
 * @param      mosnterSdl  The mosnter sdl
 * @param      renderer    The renderer
 */
void initMonsterSprites(MonsterSdl * mosnterSdl, SDL_Renderer * renderer);


SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Display the monster on the renderer
 *
 * @param      monsterSdl  The monster sdl
 * @param      renderer    The renderer
 */
void drawMonster(MonsterSdl *monsterSdl, SDL_Renderer * renderer);

/**
 * @brief      Free memory of the monstersdl
 *
 * @param      monsterSdl  The monster sdl
 */
void monsterSdlFree(MonsterSdl * monsterSdl);

/**
 * @brief      Initialise the monsterSdl
 *
 * @param      monsterSdl  The monster sdl
 * @param      pos         The position
 * @param      renderer    The renderer
 */
void monsterSdlInit(MonsterSdl *monsterSdl, Position * pos, SDL_Renderer * renderer);

/**
 * @brief      Initialise the monsterSdl in the heap
 *
 * @param      pos       The position
 * @param      renderer  The renderer
 *
 * @return     The monsterSdl initialised
 */
MonsterSdl* monsterSdlCreate(Position * pos, SDL_Renderer * renderer);

/**
 * @brief      DEstroy a monsterSdl and free memory
 *
 * @param      monsterSdl  The monster sdl
 */
void monsterSdlDestroy(MonsterSdl ** monsterSdl);

/**
 * @brief      Gets the identifier of the monster sdl.
 *
 * @param[in]  monsterSdl  The monster sdl
 *
 * @return     The identifier monster sdl.
 */
int getIdMonsterSdl(const MonsterSdl* monsterSdl);

/**
 * @brief      Sets the identifier of the monster sdl.
 *
 * @param      monsterSdl  The monster sdl
 * @param[in]  id          The identifier
 */
void setIdMonsterSdl(MonsterSdl* monsterSdl, const int id);

/**
 * @brief      Gets the xpix monster sdl.
 *
 * @param[in]  monsterSdl  The monster sdl
 *
 * @return     The xpix monster sdl.
 */
int getXpixMonsterSdl(const MonsterSdl* monsterSdl);

/**
 * @brief      Gets the ypix monster sdl.
 *
 * @param[in]  monsterSdl  The monster sdl
 *
 * @return     The ypix monster sdl.
 */
int getYpixMonsterSdl(const MonsterSdl* monsterSdl);

/**
 * @brief      Gets the current position monster sdl.
 *
 * @param[in]  monsterSdl  The monster sdl
 *
 * @return     The current position monster sdl.
 */
Position* getCurrentPosMonsterSdl(const MonsterSdl* monsterSdl);

/**
 * @brief      Gets the direction monster sdl.
 *
 * @param      monsterSdl  The monster sdl
 *
 * @return     The direction monster sdl.
 */
int* getDirectionMonsterSdl(MonsterSdl* monsterSdl);

/**
 * @brief      Sets the boolean isIdle monster sdl.
 *
 * @param      monsterSdl  The monster sdl
 * @param[in]  idle        The idle
 */
void setIsIdleMonsterSdl(MonsterSdl * monsterSdl, int idle)	;

/**
 * @brief      unit testing
 */
void monsterSdlTest();

#endif