#ifndef HUDSDL_H
#define HUDSDL_H

#include "Character.h"
#include "Position.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


/**
 * @struct HudSdl
 * @brief contains everything needed to display the HUD
 */
typedef struct {
	char *life; /**< The life of the character */
	char *mp; /**< The number of movement points the character has */
	char *ap; /**< The number of action points the character has */
	char **lifeMonster; /**< Array of char* to store every life of every monsters	 */
	Position **posMonsters; /**< Array of link to Positions for every monsters */
	SDL_Texture* hudSprite; /**< The texture of the HUD */
	TTF_Font *font; /**< The font used to display the text */
	SDL_Texture* spellBarSprite; /**< The sprite of the spellBar */
	SDL_Texture* mpText; /**< The texture for the mp txt */
	SDL_Texture* apText; /**< The texture for the ap txt */
	SDL_Texture* lifeText; /**< The texture for the life txt */
	SDL_Texture* lifeMonsterText; /**< The texture for the life of the monsters */
	int nbMstr; /**< The number of monsters */
}HudSdl;

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Initialise the sprites of the hud
 *
 * @param[in,out]     hudSdl    The hudSdl
 * @param[in,out]     renderer  The renderer
 */
void initHudSprite(HudSdl * hudSdl, SDL_Renderer * renderer);

/**
 * @brief      Free the hudSdl
 *
 * @param[in,out]     hudSdl  The hud sdl to free.
 */
void hudSdlFree(HudSdl * hudSdl);

/**
 * @brief      Initialise the hudSdl
 *
 * @param[in,out]     hudSdl    The hud sdl
 * @param[in,out]     renderer  The renderer
 */
void hudSdlInit(HudSdl *hudSdl, SDL_Renderer * renderer);

/**
 * @brief      Create a HudSdl in the heap.
 *
 * @param[in,out]     renderer  The renderer
 *
 * @return     The hudSdl created
 */
HudSdl* hudSdlCreate(SDL_Renderer * renderer);

/**
 * @brief      Destory the hudSdl when created by hudSdlCreate
 *
 * @param[in,out]     hudSdl  The hud sdl
 */
void hudSdlDestroy(HudSdl ** hudSdl);

/**
 * @brief      Convert a int to a char
 *
 * @param[in,out]     CharNumber  The char where the number will be stored
 * @param[in]  number      The number to convert.
 */
void convertIntToChar(char* CharNumber , int number);

/**
 * @brief      Display the hud on the renderer
 *
 * @param[in,out]     hudSdl    The hud sdl
 * @param[in,out]     renderer  The renderer
 */
void drawHud(HudSdl* hudSdl, SDL_Renderer* renderer);

/**
 * @brief      unit testing of the Hud
 */
void hudSdlTest();

#endif