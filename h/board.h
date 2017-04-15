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
 * @date			2017-03-04 (YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

extern std::vector<std::vector<char> > board;

/// @summary		Intantized the board, sets all the places to a space
void initBoard();

/// @summary		Updates the board with a 'X' or 'O'
/// @param			int: the place on the board (the numbers goes from the top \
						 row: 0, 1, 2; then the next row:3, 4, 5; etc.)
void updateBoard(int choice);

/// @summary		Checks if the choice is valid or not. Valid means the space is empty. (No 'X' or 'O' char there)	
/// @param			int: choice to check
/// @return			bool: is it a valid choice or not
bool checkValidChoice(int choice);
/// @summary		Checks to see if the board is filled up with 'X' or 'O'	or not
/// @return			bool: if the board is filled or not
bool boardFilled();

/// @summary		Cleans up board so we can play again	
void cleanUpBoard();

#endif