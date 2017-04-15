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

#ifndef GAME_FUNC_H_
#define GAME_FUNC_H_


/// @summary		Finds out if a player has won or not or the board is full
/// @return			bool | If a player has won or the board is full then true
bool playerWin();

/// @summary		Changes the turn
void changeTurn();

/// @summary		Gets the Winner
/// @return			string: containing the winner
std::string getWinner();

/// @summary		checks if there is a '3 in a row' of a specified char, used \
					in various functions to find out the winner
/// @param			char: to check if its 3 in a row
/// @return			bool: if char occurs 3 in a row
bool win(const char CHAR);

#endif