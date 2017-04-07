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

#ifndef _COMPUTER_AI_H_
#define _COMPUTER_AI_H_

extern std::vector<uint8_t>* currDigest;

// ====================

void initAI();

void addRun();

int computerAI();

int analyzeBoards();

inline void storeBoard();

void outputBoards();

void writeDataToFile(std::string winner);

void loadDataFromFiles();

void computeDigests();

#endif