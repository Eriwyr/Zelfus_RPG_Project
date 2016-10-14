#ifndef DIALOGSDL_H
#define DIALOGSDL_H





#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Position.h"

#define WIDTH_DIALOG 320
#define HEIGHT_DIALOG 128


/**
 * @struct DialogSdl
 * @brief Contains everything needed to display the dialog
 */
typedef struct {
	int heightSprite; /**< The height of the sprite */
	int widthSprite; /**< The width of the sprite */
	SDL_Texture* dialogSprite; /**< The sprite of the dialog */
	SDL_Texture* dialogText; /**< The texture for the text */
	TTF_Font* font; /**< The font used to write the text */
}DialogSdl;

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Initialize the sprite of the dialog
 *
 * @param[in,out]     dialogSdl  The dialogSdl
 * @param[in,out]     renderer   The renderer
 */
void initDialogSprite(DialogSdl * dialogSdl, SDL_Renderer * renderer);

/**
 * @brief      Initialise the dialogSdl
 *
 * @param[in,out]     dialogSdl  The dialog sdl
 * @param[in,out]     renderer   The renderer
 */
void dialogSdlInit(DialogSdl *dialogSdl, SDL_Renderer * renderer);

/**
 * @brief      Free the dialogSdl
 *
 * @param[in,out]     dialogSdl  The dialog sdl to free
 */
void dialogSdlFree(DialogSdl * dialogSdl);

/**
 * @brief      Create a dialogSdl in the Heap
 *
 * @param[in,out]     renderer  The renderer
 *
 * @return     the dialogSdl initialised
 */
DialogSdl* dialogSdlCreate(SDL_Renderer * renderer);

/**
 * @brief      Destroy a dialogSdl
 *
 * @param[in,out]     dialogSdl  The dialog sdl
 */
void dialogSdlDestroy(DialogSdl ** dialogSdl);

/**
 * @brief      Display the dialog on the renderer
 *
 * @param[in,out]     dialogSdl  The dialogSdl to dislpay
 * @param[in,out]     dialog     The text
 * @param[in,out]     position   The position
 * @param[in,out]     renderer   The renderer
 */
void drawDialog(DialogSdl* dialogSdl, char* dialog, Position* position,SDL_Renderer* renderer);

/**
 * @brief      Unit testing of DialogSdl
 */
void dialogSdlTest();

#endif