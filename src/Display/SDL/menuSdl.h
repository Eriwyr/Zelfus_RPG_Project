#ifndef MENUSDL_H
#define MENUSDL_H

#include <stdio.h>
#include "fightSdl.h"
#include "rpgSdl.h"

#define MAX_BUTTON 4 // number of button in the menu
#define HEIGHT_SCREEN 700
#define WIDTH_SCREEN 1344

/**
 * @struct MenuSdl
 * @brief Contains everything that is needed to display the menu
 */
 typedef struct
 {	
 	SDL_Window * screen; /**< The window on which to display the menuSprite */
	SDL_Renderer * renderer;/**<  The renderer*/
 	
 	SDL_Texture* menuSprite; /**< The sprite of the menu (background) */
 	SDL_Texture* continueTrueSprite; /**< The sprite of the button continue when activated */
 	SDL_Texture* newGameTrueSprite; /**< The sprite of the button new game when activated*/
 	SDL_Texture* creditTrueSprite; /**< The sprite of the button credit when activated */
 	SDL_Texture* quitTrueSprite; /**< The sprite of the button quit when activated */
 	SDL_Texture* keyTrueSprite; /**< The sprite of the button key when activated */

 	SDL_Texture* continueFalseSprite; /**< The sprite of the button continue when not activated */
 	SDL_Texture* newGameFalseSprite; /**<  The sprite of the button new game when not activated*/
 	SDL_Texture* creditFalseSprite; /**< The sprite of the button credit when not activated */
 	SDL_Texture* quitFalseSprite; /**< The sprite of the button quit when not activated */
 	SDL_Texture* keyFalseSprite; /**<  he sprite of the button key when not activated*/

 	SDL_Texture* commandSprite; /**< The spirte of the commands */
 	SDL_Texture* creditSprite; /**< The sprite of the credit */

 	int* tabButton; /**< Array of int to see what  */
 	int currentIndex; /**< The current option activated */
 	int option; /**< A value to display the credits/commads */
 
 }MenuSdl;


enum {CONTINUE, NEW, OPTION, EXIT};

/**
 * @brief      loop of the menu (allow to come back to the menu when exiting)
 *
 * @param[in,out]     screen    The screen
 * @param[in,out]     renderer  The renderer
 */
void menu(SDL_Window * screen, SDL_Renderer * renderer);

/**
 * @brief      Initialise the menu
 *
 * @param[in,out]     menuSdl   THe menuSdl
 * @param[in,out]     screen    The screen
 * @param[in,out]     renderer  The renderer
 */
void menuSdlInit(MenuSdl *menuSdl, SDL_Window * screen, SDL_Renderer * renderer);

/**
 * @brief      Launch the rpg or the fight
 *
 * @param[in,out]     screen    The screen
 * @param[in,out]     renderer  The renderer
 */
void game(SDL_Window * screen, SDL_Renderer * renderer);

/**
 * @brief    Main loop of the menu ( allow to select )
 *
 * @param[in,out]     menuSdl  The menu sdl
 *
 * @return     Which option selected
 */
int launchMenu(MenuSdl* menuSdl);

/**
 * @brief      The function to get the key pressed in the menu
 *
 * @param[in]  event  The event
 *
 * @return     The action corresponding to the key
 */
int inputKeyboardMenu(SDL_Event event);

/**
 * @brief      Erase the saveing file and call game
 *
 * @param[in,out]     screen    The screen
 * @param[in,out]     renderer  The renderer
 */
void newGame(SDL_Window * screen, SDL_Renderer * renderer);

#endif