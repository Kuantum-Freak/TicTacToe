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

#ifndef MAIN_H_
#define MAIN_H_

enum playerPiecesEnum {
	P1PIECE,
	P2PIECE, 
	PIECE_TOTAL
};

enum pieces {
	PIECES_X,
	PIECES_O, 
	PIECES_TOTAL
};

extern char playerPeices[PIECE_TOTAL];
extern bool userTurn;

// ==================

int main(int argc, char* argv[]);

void initEverything();

void cleanUpEverything();

#endif