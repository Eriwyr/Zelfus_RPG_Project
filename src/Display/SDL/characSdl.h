#ifndef CHARACSDL_H
#define CHARACSDL_H


#define TIME_BETWEEN_2_FRAMES_PLAYER 6
 
#define PLAYER_WIDTH 32
#define PLAYER_HEIGTH 32
 
#define PLAYER_SPEED 1000

#include "Fight.h"
#include "Monster.h"
#include "Position.h"
#include "spellSdl.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef CHAR_SIZE_MAX
	#define CHAR_SIZE_MAX 500
#endif //CHAR_SIZE_MAX

/**
 * @struct CharacSdl
 * @brief Contains all the necessary to display a character.
 */
typedef struct {
	int heightSprite; /**<The height of the sprite*/
	int widthSprite; /**<The width of the sprite */
	int frameNumber; /**<The number of the frame */
	int frameTimer; /**<The timer of the frame */
	int frameMax; /**< The maximum of the frame */
	int direction; /**< The direction at which the character will look */
	int id; /**< the id of the CharacSdl. */
	int xPix; /**< the x coordonate ( in pixel) */
	int yPix; /**< The y coordonate ( in pixel) */
	int actualAttack; /**< The current attack casted. */
	int isIdle; /**< A boolean to check if the character is walking */
	SDL_Texture* playerSpriteSheet; /**< The spriteSheet of the players */
	SDL_Texture* attack1; /**< The sprite of the first attack. */
	SDL_Texture* attack2; /**< The sprite of the second attack. */
	SDL_Texture* attack3; /**< The sprite of the third attack. */
	Position *currentPos; /**< The current position of the player (in pixel) */

	SpellSdl ** spellSdl; /**< An array of link to SpellSdl. */
	int nbSpell; /**< The number of spells in the array. */

}CharacSdl;

/**
 * @brief      Initialise the spriteSheet of the characSdl
 *
 * @param[in,out]     characSdl  The Pointer.
 * @param[in,out]     renderer   The renderer needed to display.
 */
void initPlayerSprites(CharacSdl * characSdl, SDL_Renderer* renderer);

/**
 * @brief      Load an image into a texture
 *
 * @param[in,out]     name      The name of the file to open
 * @param[in,out]     renderer  The renderer
 *
 * @return     The texture initialised with the image.
 */
SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Function to draw the player
 *
 * @param[in,out]     characSdl  The characSdl to draw
 * @param[in,out]     renderer   The renderer
 */
void drawPlayer(CharacSdl *characSdl, SDL_Renderer * renderer);

/**
 * @brief      Free the characSdl
 *
 * @param[in,out]     characSdl  The characSdl to free.
 */
void characSdlFree(CharacSdl * characSdl);

/**
 * @brief      Initialise the characSdl
 *
 * @param[in,out]     characSdl  The characSdl to initialise
 * @param[in,out]     player     A player to get it's attributs
 * @param[in,out]     renderer   The renderer
 */
void characSdlInit(CharacSdl *characSdl, Character * player, SDL_Renderer *renderer);

/**
 * @brief      Create a characSdl
 *
 * @param[in,out]     player    A player to get it's attributs.
 * @param[in,out]     renderer  The renderer
 *
 * @return     The characSdl created.
 */
CharacSdl* characSdlCreate(Character * player, SDL_Renderer * renderer);

/**
 * @brief      Destroy a characSdl when initialised with characSdlCreate()
 *
 * @param[in,out]     characSdl  The charac sdl
 */
void characSdlDestroy(CharacSdl ** characSdl);

/**
 * @brief      Gets the xPix of the charac sdl.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The xPix of the charac sdl.
 */
int getXpixCharacSdl(const CharacSdl* characSdl);


/**
 * @brief      Gets the yPix of the charac sdl.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The ypix of the charac sdl.
 */
int getYpixCharacSdl(const CharacSdl* characSdl);

/**
 * @brief      Gets the sprite attack 1.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The sprite attack 1.
 */
SDL_Texture* getSpriteAttack1(const CharacSdl* characSdl);

/**
 * @brief      Gets the sprite attack 2.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The sprite attack 2.
 */
SDL_Texture* getSpriteAttack2(const CharacSdl* characSdl);

/**
 * @brief      Gets the sprite attack 3.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The sprite attack 3.
 */
SDL_Texture* getSpriteAttack3(const CharacSdl* characSdl);

/**
 * @brief      Gets the current position of the charac sdl.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The current position charac sdl.
 */
Position* getCurrentPosCharacSdl(const CharacSdl * characSdl);

/**
 * @brief      Gets to go position of the charac sdl.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The to go position charac sdl.
 */
Position* getToGoPosCharacSdl(const CharacSdl * characSdl);

/**
 * @brief      Gets the SpellSdl of the index I from charac sdl.
 *
 * @param[in,out]     characSdl  The charac sdl
 * @param[in]  i          { parameter_description }
 *
 * @return     The spell sdl i from charac sdl.
 */
SpellSdl* getSpellSdlIFromCharacSdl(CharacSdl* characSdl, int i);

/**
 * @brief      Gets boolean isIdl of the charac sdl.
 *
 * @param[in]  characSdl  The charac sdl
 *
 * @return     The boolean isIdle charac sdl.
 */
int getIsIdleCharacSdl(const CharacSdl* characSdl);

/**
 * @brief      Set the boolean isIdle.
 *
 * @param[in,out]     characSdl  The characSdl
 * @param[in]  value      The value to set.
 */
void setIsIdleCharacSdl(CharacSdl* characSdl, int value);

void setcurrentPosCharacSdl(const CharacSdl * characSdl, int x, int y);

/**
 * @brief      Gets the direction of the characSdl.
 *
 * @param[in,out]     characSdl  The characSdl
 *
 * @return     The direction of the charac sdl.
 */
int* getDirectionCharacSdl(CharacSdl* characSdl);

/**
 * @brief      unit Testing of CharacSdl
 */
void characSdlTest();
#endif