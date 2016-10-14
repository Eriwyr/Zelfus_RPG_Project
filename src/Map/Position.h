#ifndef POSITION_H
#define POSITION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/**
*@struct Position
*@brief  define the position of an element on the map
*/
typedef struct {
	int x; /**< The x coordonate */
	int y; /**< The y coordonate */
}Position;

enum Directions {DOWN, LEFT, RIGHT, UP};

/**
*@fn int getPosX(const Position * pos);
*@brief getter of the atributs x.
*@param[in,out]pos : pointer to pos ( is a constant).
*@return : the coordonate x of pos.
*/
int getPosX(const Position * pos);

/**
*@fn int getPosY(const Position * pos);
*@brief getter of the atributs y.
*@param[in,out]pos : pointer to pos ( is a constant).
*@return : the coordonate y of pos.
*/
int getPosY(const Position * pos);

/**
*@fn int setPosX(Position * pos, int x);
*@brief setter of the atributs x.
*@param[in,out]pos : pointer to pos ( is a constant).
*@param[in,out]x : the new coordonate x of pos.
*@return none
*/
void setPosX(Position * pos, int x);

/**
*@fn int setPosY(Position * pos, int y);
*@brief setter of the atributs y.
*@param[in,out]pos : pointer to pos ( is a constant).
*@param[in,out]y : the new coordonate y of pos.
*@return none
*/
void setPosY(Position * pos, int y);

/**
 * @brief      Get the distance betweem to position.
 *
 * @param[in,out]     pos1  The first Position
 * @param[in,out]     pos2  The second Position.
 *
 * @return     the distance between the two positions.
 */
int getDistance(Position * pos1, Position * pos2);

/**
 * @brief      Get the nb squares between to positions.
 *
 * @param[in,out]     pos1  The first Position.
 * @param[in,out]     pos2  The second Position.
 *
 * @return     the nb of squares between the to positions.
 */
int getNbSquares(Position * pos1, Position * pos2);


/**
 * @brief      Unit testing of the Position.
 */
void positionTest();


#endif