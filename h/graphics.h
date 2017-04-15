/* 
 * Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		
 * @title 			
 * @date			2017-03-06 (YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

/// @summary		Initialize SDL, SDL_TTF, and SDL_Image. Then load the images\
					and fonts we need
void initGraphics();

/// @summary		Initialize SDL, SDL_TTF, and SDL_Image
void initSDL();

/// @summary		Loads all the images we need. The X image and O image
void loadPiecesIMG();

/// @summary		Loads a image and optamizes it for the current screen
/// @param			string: path to image
/// @return			SDL_Surface*: The optomized SDL_Surface
SDL_Texture* loadIMG(std::string path);

/// @summary		Loads the font and sets the font sizes

void loadFont();

/// @summary		Displays the current state of the board
void displayBoard();


/// @summary		Asks the user to pick a char (X or O)
/// @return			char: the peice the user wants to be
char askChar();

/// @summary		Displays the legal stuff on the opening render
void displayLegal();

/// @summary		Displays the winner and asks if we should play again or exit
/// @param			string: winner of the game
/// @return			bool: if we should play again or not
bool displayWinner(std::string winner);

/// @summary		Gets Where the user wants to place his piece
/// @return			int: the place where he wants to place his piece
int getUserChoice();

/// @summary		Cleans up the graphics for the next run. Currently does nothing
void cleanUpGraphics();

/// @summary		Deallocates all the surfaces and memory
void destroy();

#endif