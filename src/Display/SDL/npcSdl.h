#ifndef NPCSDL_H
#define NPCSDL_H


#define TIME_BETWEEN_2_FRAMES_NPC 6
 
#define NPC_WIDTH 32
#define NPC_HEIGTH 32
 
#define NPC_SPEED 1000

#include "Fight.h"
#include "NPC.h"
#include "dialogSdl.h"
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "objectSdl.h"
/**
 * @strcut NpcSdl
 * @brief contain everything to display NPC
 */
typedef struct {
	int heightSprite; /**< The height of the sprite */
	int widthSprite; /**< The width of the sprite */
	int frameNumber; /**< The number of frame */
	int frameTimer; /**< The time of the frame */
	int frameMax; /**< The frame maximum */
	int direction; /**< The direvtion of the npc */
	int id; /**< The id of the npc */
	Position* currentPos; /**< The current position of the npc */
	SDL_Texture* npcSpriteSheet; /**< The sprite sheet of the npcs */
	ObjectSdl ** objectSdl; /**< Array of link to objectSdl */
	int nbObj; /**< The number of objects */
	int size; /**< The size  */
	DialogSdl* dialogSdl; /**< The dialog of the npc */
	int displayDialog; /**< Boolean to see i we display the dialog */
	int isIdle; /**< Boolean to see if npc is movin*/
	int isTalking; /**< Boolean to check if we are talking or not */

}NpcSdl;

/**
 * @brief      Initialise the sprites of the npc
 *
 * @param      npcSdl    The npc sdl
 * @param      renderer  The renderer
 */
void initNpcSprites(NpcSdl * npcSdl, SDL_Renderer* renderer);

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Display everything of the npc on the renderer
 *
 * @param      npcSdl    The npc sdl
 * @param      renderer  The renderer
 */
void drawNpc(NpcSdl *npcSdl, SDL_Renderer * renderer);

/**
 * @brief      Free memory
 *
 * @param      npcSdl  The npc sdl
 */
void npcSdlFree(NpcSdl * npcSdl);

/**
 * @brief      Initialise the npcSdl
 *
 * @param      npcSdl    The npc sdl
 * @param      npc       The npc
 * @param      renderer  The renderer
 */
void npcSdlInit(NpcSdl *npcSdl, NPC * npc, SDL_Renderer *renderer);

/**
 * @brief      Create a npcSdl in the heap
 *
 * @param      npc       The npc
 * @param      renderer  The renderer
 *
 * @return     The npcSdl created.
 */
NpcSdl* npcSdlCreate(NPC * npc, SDL_Renderer * renderer);

/**
 * @brief      Destroy npcSdl and free memory
 *
 * @param      npcSdl  The npc sdl
 */
void npcSdlDestroy(NpcSdl ** npcSdl);

/**
 * @brief      Gets the dialog npc sdl.
 *
 * @param[in]  npcSdl  The npc sdl
 *
 * @return     The dialog npc sdl.
 */
DialogSdl* getDialogNpcSdl(const NpcSdl* npcSdl);

/**
 * @brief      Gets the current position npc sdl.
 *
 * @param[in]  npcSdl  The npc sdl
 *
 * @return     The current position npc sdl.
 */
Position* getCurrentPosNpcSdl(const NpcSdl* npcSdl);

/**
 * @brief      Sets the isTalking bool of the npc sdl.
 *
 * @param      npcSdl  The npc sdl
 * @param[in]  value   The value
 */
void setIsTalkingNpcSdl(NpcSdl* npcSdl, int value);

/**
 * @brief      Sets the display dialog npc sdl.
 *
 * @param      npcSdl  The npc sdl
 * @param[in]  value   The value
 */
void setDisplayDialogNpcSdl(NpcSdl* npcSdl, int value);

/**
 * @brief      Removes an objectSdl form the  npc sdl.
 *
 * @param      npcSdl  The npc sdl
 * @param[in]  ind     The ind
 */
void removeObjectSdlNpcSdl(NpcSdl * npcSdl, int ind);

/**
 * @brief      Unit testing
 */
void npcSdlTest();


/**
 * @brief      Sets the is idle npc sdl.
 *
 * @param      npcSdl  The npc sdl
 * @param[in]  value   The value
 */
void setIsIdleNpcSdl(NpcSdl* npcSdl, int value);

/**
 * @brief      Gets the direction npc sdl.
 *
 * @param      npcSdl  The npc sdl
 *
 * @return     The direction npc sdl.
 */
int* getDirectionNpcSdl(NpcSdl* npcSdl);

/**
 * @brief      Gets the Ith objectsdl of npc sdl.
 *
 * @param      npcSdl  The npc sdl
 * @param[in]  i       The index
 *
 * @return     The object sdl i npc sdl.
 */
ObjectSdl* getObjectSdlINpcSdl(NpcSdl* npcSdl, int i);

/**
 * @brief      Gets the nbObject npc sdl.
 *
 * @param[in]  npcSdl  The npc sdl
 *
 * @return     The nb object npc sdl.
 */
int getNbObjNpcSdl(const NpcSdl* npcSdl);
#endif