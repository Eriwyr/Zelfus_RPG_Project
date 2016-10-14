#ifndef MAPSDL_H
#define MAPSDL_H


#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Map.h"
#include "Fight.h"
#include "mapSdl.h"
#include "characSdl.h"
#include <math.h>



 

#define TILE_SIZE 64

/**
 * @struct MapSdl
 * @brief Contains evrything tpo display the map
 */
typedef struct{
 
	SDL_Texture *background; /**< The background of the map */
	SDL_Texture *mapTileset; /**< The tileSet of the map */
	int beginx; /**< The starting x coordonate of the map */
	int beginy; /**< The starting y coordonate of the map */
	int maxX; /**< The maximum x coordonate of the map */
	int maxY; /**< The maximum y coordonate of the map */

 
} MapSdl;


/**
 * @brief      Initialise the mapSdl
 *
 * @param[in,out]     mapSdl      The map sdl
 * @param[in,out]     mapTileset  The map tileset
 * @param[in,out]     renderer    The renderer
 */
void mapSdlInit(MapSdl* mapSdl, char* mapTileset, SDL_Renderer* renderer);

/**
 * @brief      Create a mapSdl in the heap
 *
 * @param[in,out]     mapTileset  The map tileset
 * @param[in,out]     renderer    The renderer
 *
 * @return     The mapSdl created
 */
MapSdl* mapSdlCreate(char* mapTileset, SDL_Renderer * renderer);

/**
 * @brief      Gets the background of the mapSdl.
 *
 * @param[in,out]     mapSdl  The map sdl
 *
 * @return     The background.
 */
SDL_Texture *getBackground(MapSdl* mapSdl);

/**
 * @brief      free the mapSdl
 *
 * @param[in,out]     mapSdl  The map sdl to free
 */
void mapSdlFree(MapSdl* mapSdl);

/**
 * @brief      Destroy the mapSdl when initialised by mapSdlCreate
 *
 * @param[in,out]     mapSdl  The map sdl
 */
void mapSdlDestroy(MapSdl ** mapSdl);

SDL_Texture *loadImage(char *name, SDL_Renderer* renderer);

/**
 * @brief      Display an image on the renderer
 *
 * @param[in,out]     image     The image to display
 * @param[in]  x         the x coordoante 
 * @param[in]  y         the y coordonate
 * @param[in,out]     renderer  The renderer
 */
void drawImage(SDL_Texture *image, int x, int y, SDL_Renderer* renderer);

/**
 * @brief      Display the map on the renderer
 *
 * @param[in,out]     mapSdl    The mapSdl
 * @param[in,out]     renderer  The renderer
*/
void drawMap(MapSdl* mapSdl, Map* map1, SDL_Renderer *renderer);

/**
 * @brief      unit testing
 */
void mapSdlTest();
#endif
