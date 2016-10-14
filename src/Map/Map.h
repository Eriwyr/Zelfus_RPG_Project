#ifndef MAP_H
#define MAP_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Character.h"

#define NB_NOT_ALLOWED 10
#define MAX_MAP_X 21
#define MAX_MAP_Y 11

/**
 * @struct Map
 * @brief Contain the array of the map.
 */

typedef struct{
	int height; /**< The height of the map. */
	int width; /**< The width of the map. */
	int ** array; /**< 2D array of int */
	int id; /**< The id of the map */
}Map;


/**
 * @fn mapInit(Map * map, int height, int width);
 * @brief initialisation of a map       
 * @param[in,out]     map    	a map 
 * @param[in]  height  	height of the map
 * @param[in]  width   	width of the map
 * @return none
 */
void mapInit(Map * map, int height, int width);

/**
 * @fn mapFree(Map* map); 
 * @brief      Free a map
 * @param[in,out]     map   a map
 * @return none
 */
void mapFree(Map* map);

/**
 *@fn mapCreate(int height, int width);
 * @brief      Create a map 
 *
 * @param[in]  height  The height of the map
 * @param[in]  width   The width of the map
 * @return     return a pointer to a map
 */
Map* mapCreate(int height, int width);

int getIdMap(const Map* map);

/**
 * @brief      Destroy a map 
 *
 * @param[in,out]     map  map to destroy
 * @return none
 */
void mapDestroy(Map** map);

/**
 * @fn getHeightMap(Map* map);
 * @brief      get height of a map
 *
 * @param[in,out]     map   a map
 *
 * @return     an integer of the height of the map
 */
int getHeightMap(Map* map);

/**
 * @fn getWidthMap(Map* map);
 * @brief      get the width of a ma
 *
 * @param[in,out]     map   a map
 *
 * @return     an integer of the width of the map
 */
int getWidthMap(Map* map);

/**
 * @brief      set the element of coordonate x y to element 
 *
 * @param[in,out]      map      pointer to map
 * @param[in]  x        the coodonate x.
 * @param[in]  y        the coordonate y.
 * @param[in]  element  the element ( player, monster, wall ect..)
 */
void setElementXYMap(Map * map, int x, int y, int element);

/**
 * @brief      return the element at the position x y
 *
 * @param[in]  map   pointer to map
 * @param[in]  x     the coordonate x.
 * @param[in]  y     the coordonate y.
 *
 * @return     l'element x y.
 */
int getElementXYMap(const Map* map, int x, int y);


/**
 * @brief      Load a map from a file
 *
 * @param[in,out]     map       the map to store the data loaded.
 * @param[in,out]     fileName  the name of the file to open.
 */
Map* loadMapFromFile(char* fileName);

/**
 * @brief      move a character on a map
 *
 * @param[in,out]     player     the character to move.
 * @param[in,out]     map        the map on which the character will move
 * @param[in]  direction  the direction in which the character will move.
 *
 * @return     a boolean to see if the movement was succesful.
 */
int movePlayerOnMap(Character * player, Map * map, int direction);

/**
 * @brief      Determine if a tile is allowed to walk on.
 *
 * @param[in,out]     map   pointer to Map.
 * @param[in]  x     the x coordonate of the tile.
 * @param[in]  y     the y coordonate of the tile.
 *
 * @return     A boolean to see if the tile is allowed.
 */
int isAllowedTile(Map * map, int x, int y);


/**
 * @brief      Unit testing of the Map.
 */
void mapTest();


#endif