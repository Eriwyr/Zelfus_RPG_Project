#ifndef OBJECTSDL_H
#define OBJECTSDL_H





#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Position.h"
#include "QuestObject.h"

#define WIDTH_OBJECT 48
#define HEIGHT_OBJECT 48

/**
 * @struct ObjectSdl
 * @brief contains everything needed to display an object
 */

typedef struct{

	int id; /**< The index of the ObjectSdl */
	int heightSprite; /**< The height of the sprite */
	int widthSprite; /**< The width of the sprite */
	Position * currentPos; /**< the current position of the object */
	int display; /**< Boolean to see if we display the object or not */
	SDL_Texture* objectSprite; /**< The sprite of the object */
 
}ObjectSdl;

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Initialise the sprites of the object
 *
 * @param      objectSdl  The object sdl
 * @param      renderer   The renderer
 */
void initObjectSprite(ObjectSdl * objectSdl, SDL_Renderer * renderer);

/**
 * @brief      Initialise an objectSdl
 *
 * @param      objectSdl  The object sdl
 * @param      object     The object
 * @param      renderer   The renderer
 */
void objectSdlInit(ObjectSdl *objectSdl, QuestObject* object, SDL_Renderer * renderer);

/**
 * @brief      Create an objectsdl in the Heap
 *
 * @param      object    The object
 * @param      renderer  The renderer
 *
 * @return     The objectSdl created
 */
ObjectSdl* objectSdlCreate(QuestObject* object, SDL_Renderer * renderer);

/**
 * @brief      display the object on the renderer
 *
 * @param      objectSdl  The object sdl
 * @param      renderer   The renderer
 */
void drawObject(ObjectSdl* objectSdl, SDL_Renderer* renderer);

/**
 * @brief      Free memory
 * @param      objectSdl  The object sdl
 */
void objectSdlFree(ObjectSdl * objectSdl);

/**
 * @brief      Sets the display object sdl.
 *
 * @param      objectSdl  The object sdl
 * @param[in]  value      The value
 */
void setDisplayObjectSdl(ObjectSdl * objectSdl, int value);

/**
 * @brief      Gets the display object sdl.
 *
 * @param[in]  objectSdl  The object sdl
 *
 * @return     The display object sdl.
 */
int getDisplayObjectSdl(const ObjectSdl * objectSdl);	

/**
 * @brief      Destroy an objectSdl 
 *
 * @param      objectSdl  The object sdl
 */
void objectSdlDestroy(ObjectSdl ** objectSdl);

/**
 * @brief      unit testing of objectsdl
 */
void objectSdlTest();

#endif