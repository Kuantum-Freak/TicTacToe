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
 * @fversion		3.1.2
 * @description 	
 * =============================================================================
 */
#include "info.h"

#include <cstdlib>
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <string.h>
#include <stdio.h>
#include <typeinfo>
#include <algorithm>

#include ".\h\computerAI.h"
#include ".\h\main.h"
#include ".\h\board.h"

typedef std::vector<std::vector<char> > Board; // type board

int computerAI() {
	int choice;
	
	vector<int> sums = {0,0,0,0,0,0,0,0,0};
	
	//get
	minimax(true, );
	
	for(auto& t : sums)
		LOG(t << "\t");
	
	auto ans = std::max_element(sums.begin(), sums.end());
	choice = ans - sums.begin();
	
	if(*ans == 0)
		return rand() % 9;
	
	while(!checkValidChoice(choice)) {
		sums.erase(ans);
		ans = std::max_element(sums.begin(), sums.end());
		choice = ans - sums.begin();
	}
	
	return choice;
	//return analyzeBoards();
}

int minimax(bool isComputer, int choice, int depth, Board board) {
	
	char winner = getWin(board);
	if(winner == playerPeices[P2PIECE]) { return depth - 10; }
	if(winner == playerPeices[P2PIECE]) { return 10 - depth; }
	
	if(isComputer) {
		board[choice / 3][choice % 3] = playerPeices[P2PIECE];
	} else {
		board[choice / 3][choice % 3] = playerPeices[P1PIECE];
	}
	
	vector<int> sums(9, 0);
	
	for(int i = 0; i < 9; ++i) {
		if(board[i/3][i%3] == 'X' || board[i/3][i%3] == 'O') { continue; }
		
		sums[i] = minimax(!isComputer, i, depth + 1, board);
	}
	
	vector<int>::iterator ans;
	
	if(isComputer)
		ans = std::max_element(sums.begin(), sums.end());
	else 
		ans = std::min_element(sums.begin(), sums.end());
	
	return *ans;
}


char getWin(Board &board) {
	unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
	
	for(int i = 0; i < 8; ++i) {
		if(    board[wins[i][0] / 3][wins[i][0] % 3] != ' '
			&& board[wins[i][0] / 3][wins[i][0] % 3] ==  board[wins[i][1] / 3][wins[i][1] % 3]
			&& board[wins[i][0] / 3][wins[i][1] % 3] ==  board[wins[i][1] / 3][wins[i][2] % 3]
		) return board[wins[i][0] / 3][wins[i][0] % 3];
	}
	return ' ';
}