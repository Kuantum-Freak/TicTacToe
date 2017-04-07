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

void initBoard();

void updateBoard(int choice);

bool checkValidChoice(int choice);

bool boardFilled();

void cleanUpBoard();

#endif