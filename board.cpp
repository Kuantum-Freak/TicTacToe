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
 * @title 			Internal Board
 * @date			2017-03-04 (YYYY-MM-DD)
 * @fversion		1.3.0
 * @description 	This file contains functions to control the internal board
 * =============================================================================
 */
#include "info.h"

#include <iostream>
#include <vector>
using std::vector;

#include ".\h\main.h"
#include ".\h\computerAI.h"

#define LOG(a) if(DEBUG) {std::cout << a << std::endl;} // DEBUGGING

typedef std::vector<std::vector<char> > Board;

Board board;

/* 
	@summary		Intantized the board, sets all the places to a space
	
	@param			VOID
	@return			VOID
 */
void initBoard() {
	board.push_back(vector<char>(3, ' '));
	board.push_back(vector<char>(3, ' '));
	board.push_back(vector<char>(3, ' '));
}

/* 
	@summary		Updates the board with a 'X' or 'O'
	
	@param			int: the place on the board (the numbers goes from the top 
						 row: 0, 1, 2; then the next row:3, 4, 5; etc.)
	@return			VOID
 */
void updateBoard(int choice) {
	if(userTurn) {
		board[choice / 3][choice % 3] = playerPeices[P1PIECE];
	} else {
		board[choice / 3][choice % 3] = playerPeices[P2PIECE];
	}
	currDigest->push_back(choice);
	storeBoard();
	// outputBoards();
}

/* 
	@summary		Checks if the choice is valid or not. Valid means the space
					is empty. (No 'X' or 'O' char there)
	
	@param			int: choice to check
	@return			bool: is it a valid choice or not
 */
bool checkValidChoice(int choice) {
	return  board[choice / 3][choice % 3] == 'X' ||
			board[choice / 3][choice % 3] == 'O';
}

/* 
	@summary		Checks to see if the board is filled up with 'X' or 'O'
					or not
	
	@param			VOID
	@return			bool: if the board is filled or not
 */
bool boardFilled() {
	int counter = 0;
	for(auto &i: board)
		for (auto &j: i)
			if(j == 'X' || j == 'O')
				counter++;
	return counter == 9;
}

/* 
	@summary		Cleans up board so we can play again
	
	@param			VOID
	@return			VOID
 */
void cleanUpBoard() {
	for(auto &i: board)
		for (auto &j: i)
			j = ' ';
}