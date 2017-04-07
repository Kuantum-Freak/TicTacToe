/* 
 * Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		Tic Tac Toe
 * @title 			Game Functions
 * @date			2017-03-04 (YYYY-MM-DD)
 * @fversion		1.0.8
 * @description 	This file includes functions used during differnt parts of
					the game
 * =============================================================================
 */
#include "info.h"
#include <vector>
#include <stdexcept>
#include <string>

#include ".\h\gameFunc.h"
#include ".\h\main.h"
#include ".\h\board.h"

/* 
	@summary		Finds out if a player has won or not or the board is full
	
	@param			VOID
	@return			bool | If a player has won or the board is full then true
 */
bool playerWin() {
	return  win(playerPeices[P1PIECE]) ||
			win(playerPeices[P2PIECE]) || 
			boardFilled();
}

/* 
	@summary		Changes the turn
	
	@param			VOID
	@return			VOID
 */
void changeTurn() {
	userTurn = !userTurn;
}

/* 
	@summary		Gets the Winner
	
	@param			VOID
	@return			string: containing the winner
 */
std::string getWinner() {
	if(win(playerPeices[P1PIECE]))
		return "Player 1 (User)";
	if(win(playerPeices[P2PIECE]))
		return "Player 2 (Computer)";
	return "No one (Tie)";
}

/* 
	@summary		checks if there is a '3 in a row' of a specified char, used 
					in various functions to find out the winner
	
	@param			char: to check if its 3 in a row
	@return			bool: if char occurs 3 in a row
 */
bool win(const char CHAR) {
	using std::out_of_range;
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			if(board[i][j] == CHAR) {
				// =================================
				int count = 1;
				for(int k = 1; k < 3; ++k) { // UP
					try {
						if(board.at(i - k).at(j) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				count = 1;
				for(int k = 1; k < 3; ++k) { // DOWN
					try {
						if(board.at(i + k).at(j) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				count = 1;
				for(int k = 1; k < 3; ++k) { // LEFT
					try {
						if(board.at(i).at(j - k) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				count = 1;
				for(int k = 1; k < 3; ++k) { // RIGHT
					try {
						if(board.at(i).at(j + k) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				// =================================					
				count = 1;
				for(int k = 1; k < 3; ++k) { // UP & LEFT
					try {
						if(board.at(i - k).at(j - k) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				count = 1;
				for(int k = 1; k < 3; ++k) { // UP & RIGHT
					try {
						if(board.at(i - k).at(j + k) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				count = 1;
				for(int k = 1; k < 3; ++k) { // DOWN & LEFT
					try {
						if(board.at(i + k).at(j - k) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
				count = 1;
				for(int k = 1; k < 3; ++k) { // DOWN & RIGHT
					try {
						if(board.at(i + k).at(j + k) == CHAR)
							count++;
					} catch(out_of_range &e) {}
				}
				if(count == 3)
					return true;
				// =================================
			}
		}
	}
	return false;
}