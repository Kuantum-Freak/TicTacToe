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

#include ".\h\computerAI.h"
#include ".\h\main.h"
#include ".\h\board.h"

typedef std::vector<std::vector<char> > Board; // type board
typedef std::vector<uint8_t> Digest;

struct Game { // stores a game, the boards and the winner of that game
	vector<Board> boards;
	char winner;
	Digest digest;
	char firstPlayer;
};

struct AnalysisData {
	unsigned gameNumber;
	char winner;
	char firstPlayer;
	
	int points;
	int rPoints;
};

vector<Game> runs; // stores all the runs we have played

Game* currGame; // pointer to the current game
Digest* currDigest; // pointer to the current digest

void initAI() {
	loadDataFromFiles();
	computeDigests();
}

void addRun() {
	Game g;
	runs.push_back(g);
	
	currGame = &runs[runs.size() - 1];
	currDigest = &currGame->digest;
}

int computerAI() {
	return analyzeBoards();
}

int analyzeBoards() {
	CLEAR_TERMINAL;
	
	// ============= OUTPUT DIGESTS =============
	for(unsigned i = 0; i < runs.size() - 1; ++i) {
		LOG(i << ": ");
		for(unsigned j = 0; j < runs[i].digest.size(); ++j)
			LOG((int)runs[i].digest[j]);
		LOG(endl);
		/*/
		LOG(i << "R: ");
		for(unsigned j = 0; j < runs[i].digest.size(); ++j)
			LOG((runs[i].digest[j] + 8) + (8 - (runs[i].digest[j] + 8)) - (runs[i].digest[j] % 3) - (runs[i].digest[j] / 3));
		LOG(endl);
		//*/
	}
	LOGL("Current Digest: ");
	for(uint8_t &i: *currDigest)
		LOG((int)i);
	LOG(endl);
	
	// ============= FIND MATCHING DATA =============
	vector<AnalysisData> matchingPositions;
	
	for(unsigned i = 0; i < runs.size() - 1; ++i) {
		Digest &tmpDigest = runs[i].digest;
		for(unsigned j = 0; j < currDigest->size(); ++j) {
			if((*currDigest)[j] != tmpDigest[j])
				break;
			if(j == currDigest->size() - 1) {
				matchingPositions.push_back(
					AnalysisData {
						i,
						runs[i].winner,
						runs[i].firstPlayer
					}
				);
			}
		}
	}
	
	// ============= COUNT REOCCURENCES =============
	for(unsigned i = 0; i < matchingPositions.size(); ++i) {
		for(unsigned j = i + 1; j < matchingPositions.size(); ++j) {
			if(matchingPositions[i].gameNumber == matchingPositions[j].gameNumber) {
				matchingPositions[i].points++;
				matchingPositions[j].points++;
			}
		}
	}
	
	/*/ ======== ROTATION ===========
		for(unsigned i = 0; i < runs.size() - 1; ++i) {
		Digest* tmpDigest = &(runs[i].digest);
		for(unsigned j = 0; j < currDigest->size(); ++j) {
			int cdNum = (*tmpDigest)[j];
			int cdNumR = (cdNum + 8) + (8 - (cdNum + 8)) - (cdNum % 3);
			if((*currDigest)[j] != cdNumR)
				break;
			if(j == currDigest->size() - 1) {
				matchingPositions.push_back(
					AnalysisData {
						i,
						runs[i].winner,
						runs[i].firstPlayer
					}
				);
			}
		}
	}
	//*/
	
	if(matchingPositions.size() != 0)
		for(auto &i: matchingPositions) {
			LOGL("Found match in Game: " << i.gameNumber << ". W: " << i.winner << ". FP: " << i.firstPlayer << ". P: " << i.points);
		}
	else
		LOGL("No matches found");
	
	// find possibility of best option
	vector<int> possibleHits(9, 0);
	
	/* 
		Get the game from gameNumber, then get digest from that game. Get the
		number at next choice affter current digest size (next hit possible)
		that digest is a possibleChoice on the board then add a point to it. 
	*/
	for(auto &i: matchingPositions) {
		// Finds the possiblities
		possibleHits[
			runs[i.gameNumber].digest[currDigest->size()]
		]++;
	}
	
	for(unsigned i = 0; i < possibleHits.size(); ++i) {
		LOGL(i << " place has " << possibleHits[i] << " points");
	}
	
	// hit there

	LOGL("Randomizing")
	return (rand() % 9);
}

void storeBoard() {
	currGame->boards.push_back(board);
}

void outputBoards() {
	CLEAR_TERMINAL;
	
	for(auto &i: runs) { // i is a Game
		cout << "NEXT GAME: \n";
		for(auto &j: i.boards) { // j is a Board
			cout << "Next board:" << endl;
			for(auto &k: j) { // k is a row
				for(auto &l: k) // l is the char
					cout << l;
				cout << endl;
			}
			cout << "----------------" << endl;
		}
		cout << "======================\n";
	}
}

void writeDataToFile(std::string cWinner) {
	using std::string;
	using std::to_string;
	
	if     (strcmp(cWinner.c_str(), "Player 1 (User)") == 0)
		currGame->winner = playerPeices[P1PIECE];
	else if(strcmp(cWinner.c_str(), "Player 2 (Computer)") == 0)
		currGame->winner = playerPeices[P2PIECE];
	else if(strcmp(cWinner.c_str(), "No one (Tie)") == 0)
		currGame->winner = 'T';
	
	string fileName;
	for(int i = 0;;++i) {
		fileName = string("../dat/") 
				 + string("TTTgame_") 
				 + to_string(i) 
				 + string(".dat");
		if (FILE* testFile = fopen(fileName.c_str(), "r")) {
			fclose(testFile);
		} else 
			break;
	}
	
	FILE* currFile = fopen(fileName.c_str(), "w");
	
	fprintf(currFile, "%c", currGame->winner);
	
	for(auto &i: currGame->boards) { // i is a board
		fprintf(currFile, ":");
		for(auto &j: i) // j is a row
			for(auto &k: j) // k is the char
				fprintf(currFile, "%c", k);
	}
	
	fclose(currFile);
}

void loadDataFromFiles() {
	using std::string;
	using std::to_string;
	
	//LOGL("Reading past plays\n");
	string fileName;
	FILE* currFile;
	for(int i = 0;;++i) {
		fileName = string("../dat/")
				 + string("TTTgame_") 
				 + to_string(i) 
				 + string(".dat");
		
		if ((currFile = fopen(fileName.c_str(), "r"))) {
			fseek(currFile, 0, SEEK_SET); // go to the biginning
			
			//LOGL(fileName << " loading\n");
			Game curLGame; // create new Game to store our data
			
			// get pointer to our curr Board Set
			vector<Board> &curLBoards = curLGame.boards;
			
			// get winner and set it
			curLGame.winner = getc(currFile);
			//LOGL("Winner is " << curLGame.winner);
			
			for(int j = 0;;j++) {
				if(getc(currFile) == EOF) break;
				else fseek(currFile, -1, SEEK_CUR);
				
				if(getc(currFile) == ':') {
					//LOGL("Found a BOARD at " << ftell(currFile));

					//create 3x3 grid for curLBoards
					vector<char> tempRow(3, ' ');
					Board tempBoard(3, tempRow);
					curLBoards.push_back(tempBoard);
					//LOGL("Created a 3x3 Board, ready to be filled")
					
					for(int k = 0; k < 3; ++k)
						for(int l = 0; l < 3; ++l)
							curLBoards[j][k][l] = getc(currFile);
					
					/*LOGL("found compleate board:\n");
					for(int k = 0; k < 3; ++k) { // k is a row
						for(int l = 0; l < 3; ++l) {
							if((*curLBoards)[b][k][l] != ' ')
								LOGL((*curLBoards)[b][k][l]);
							else
								LOGL('*');
						}
						LOGL(endl);
					}
					log(endl);*/
				} else {
					//if the position isnt a EOF or a board, go to the next byte 
					fseek(currFile, 1, SEEK_CUR);
				}
			}
			runs.push_back(curLGame);
		} else break;
	}
}

void computeDigests() {
	for(Game &gDigGame: runs) {
		//LOGL("GET GAME");
		for(unsigned j = 0; j < gDigGame.boards[0].size(); ++j)
			for(unsigned k = 0; k < gDigGame.boards[0][j].size(); ++k) {
				if(gDigGame.boards[0][j][k] == 'X' || gDigGame.boards[0][j][k] == 'O')
					gDigGame.digest.push_back((j * 3) + k);
				if(gDigGame.boards[0][j][k] == 'X')
					gDigGame.firstPlayer = 'X';
				else if(gDigGame.boards[0][j][k] == 'O')
					gDigGame.firstPlayer = 'O';
			}
			
		for(unsigned i = 0; i < gDigGame.boards.size() - 1; ++i) {
			//LOGL("GET 2 BOARDS " << i << " and " << i + 1);
			Board* cmpBoard1 = &(gDigGame.boards[i]);
			Board* cmpBoard2 = &(gDigGame.boards[i + 1]);
			
			for(unsigned j = 0; j < cmpBoard1->size(); ++j)
				for(unsigned k = 0; k < (*cmpBoard1)[j].size(); ++k) {
					//LOGL("COMPARE " << j << ' ' << k);
					if((*cmpBoard1)[j][k] != (*cmpBoard2)[j][k])
						gDigGame.digest.push_back((j * 3) + k);
					//LOGL("COMPARE " << j << ' ' << k);
				}
		}
	}
	/*
	cout << "Digest" << endl;
	for(Game &tGame: runs) {
		for(uint8_t &i: tGame.digest)
			cout << (int)i << ' ';
		cout << endl;
	}
	*/
}
