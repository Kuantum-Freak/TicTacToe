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
 * @title 			Main
 * @date			2017-03-04 (YYYY-MM-DD)
 * @fversion		2.0.2
 * @description 	This file is the entry point for the Tic Tac Toe game
 * =============================================================================
 */
#include "info.h"
#define _PRINTINFO std::cout << '\n' << R_PROJNAME << " v" << R_PVERSION \
		<< " by " << R_AUTHOR << '\n' << R_COPYRIGHT << '\n' << R_COMMENTS \
		<< "\n\n\n" // Legal and Informational

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <SDL.h>

#include ".\h\main.h"
#include ".\h\graphics.h"
#include ".\h\gameFunc.h"
#include ".\h\board.h"
#include ".\h\computerAI.h"

// enum playerPiecesEnum {P1PIECE, P2PIECE, PIECE_TOTAL};
char playerPeices[PIECE_TOTAL]; // stored the chars for the player and computer
bool userTurn;

int main(int argc, char* argv[]) {
	_PRINTINFO;
	
	using std::cout;
	using std::cin;
	using std::endl;
	
	srand(time(NULL));
	
	initEverything();
	
	playerPeices[P1PIECE] = askChar();
	playerPeices[P2PIECE] = (playerPeices[P1PIECE] == 'X')? 'O':'X';
	std::string winner = "";

	do {
		cleanUpEverything();
		displayBoard();
		do {
			changeTurn();
			if(userTurn) {
				int choice = 0;
				do {
					choice = getUserChoice();
				} while(checkValidChoice(choice));
				updateBoard(choice);
				displayBoard();
			} else {
				int choice = 0;
				do {
					choice = computerAI();
				} while(checkValidChoice(choice));
				updateBoard(choice);
				displayBoard();
			}
		} while(!playerWin());
		winner = getWinner();
		writeDataToFile(winner);
	} while(displayWinner(winner));
	
	destroy();
	return 0;
}

void initEverything() {
	userTurn = rand() % 2 == 0;
	
	initAI();
	initBoard();
	initGraphics();
}

void cleanUpEverything() {
	cleanUpGraphics();
	cleanUpBoard();
	addRun();
}