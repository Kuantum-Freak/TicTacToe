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

void initGraphics();

void initSDL();

void loadPiecesIMG();

SDL_Texture* loadIMG(std::string path);

void loadFont();


void displayBoard();

char askChar();

void displayLegal();

bool displayWinner(std::string winner);

int getUserChoice();

void cleanUpGraphics();

void destroy();

#endif