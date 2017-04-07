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
 * @title 			Graphics Functions
 * @date			2017-03-06 (YYYY-MM-DD)
 * @fversion		3.1.1
 * @description 	This File include functions to enable graphics on the screen
 * =============================================================================
 */
#include "info.h"

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_TTF.h>
#include <string>
#include <iostream>

#include ".\h\graphics.h"
#include ".\h\main.h"
#include ".\h\board.h"

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH  = 640;

SDL_Window*  mainWindow					=  NULL;
SDL_Surface* mainWinSurface				=  NULL;
SDL_Renderer* mainWinRenderer			=  NULL;
SDL_Texture* peiceMarkers[PIECES_TOTAL]	= {NULL, NULL};
SDL_Texture* textTexture				=  NULL;
TTF_Font* mainFont						=  NULL;
TTF_Font* legFont						=  NULL;

/* 
	@summary		Initialize SDL, SDL_TTF, and SDL_Image. Then load the images
					and fonts we need
	
	@param			VOID
	@return			VOID
 */
void initGraphics() {
	initSDL();
	loadPiecesIMG();
	loadFont();
}

/* 
	@summary		Initialize SDL, SDL_TTF, and SDL_Image
	
	@param			VOID
	@return			VOID
 */
void initSDL() {
	// Setup SDL and SDL images
	if(SDL_Init(SDL_INIT_VIDEO) < 0) exit(-0x201); // -513
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) exit(-0x202); // -514
	
	// Create our main window
	mainWindow = SDL_CreateWindow(
		"TicTacToe", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN //| SDL_WINDOW_BORDERLESS
	);
	if(mainWindow == NULL) exit(-0x203); // -515
	
	// Get Main Window Surface
	mainWinSurface = SDL_GetWindowSurface(mainWindow);
	
	// Setup Graphics Renderer
	mainWinRenderer = SDL_CreateRenderer (
		mainWindow, 
		-1, 
		SDL_RENDERER_ACCELERATED
	);
	if(mainWinRenderer == NULL) exit(-0x204); // -516
	
	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!( IMG_Init(imgFlags) & imgFlags)) exit(-0x205); // -517
	
	// Initianlize TTF
	if(TTF_Init() == -1) exit(-0x209);
}

/* 
	@summary		Loads all the images we need. The X image and O image
	
	@param			VOID
	@return			VOID
 */
void loadPiecesIMG() {
	peiceMarkers[PIECES_X] = loadIMG("../res/X.png");
	if (peiceMarkers[PIECES_X] == NULL) exit(-0x208); // -520
	
	peiceMarkers[PIECES_O] = loadIMG("../res/O.png");
	if (peiceMarkers[PIECES_O] == NULL) exit(-0x208); // -520
}

/* 
	@summary		Loads a image and optamizes it for the current screen
	
	@param			string: path to image
	@return			SDL_Surface*: The optomized SDL_Surface
 */
SDL_Texture* loadIMG(std::string path) {
	using std::string;
	
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	surface = IMG_Load(path.c_str());
	if(surface == NULL) exit(-0x206); // -518

	//Convert surface to screen format
	texture = SDL_CreateTextureFromSurface(mainWinRenderer, surface);
	if(texture == NULL) exit(-0x207); // -519

	return texture;
}

/* 
	@summary		Loads the font and sets the font sizes
	
	@param			VOID
	@return			VOID
 */
void loadFont() {
	mainFont = TTF_OpenFont("../res/arial.ttf", 45);
	if(mainFont == NULL) exit(-0x20A);
	
	legFont = TTF_OpenFont("../res/arial.ttf", 10);
	if(mainFont == NULL) exit(-0x20B);
}

/* 
	@summary		Displays the current state of the board
	
	@param			VOID
	@return			VOID
 */
void displayBoard() {
	// =============  Clear screen  =============
	SDL_SetRenderDrawColor(mainWinRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mainWinRenderer);
	
	// =============  Draw Peices  =============
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			SDL_Rect place = {	
				SCREEN_WIDTH  * j / 3 + 3, // x
				SCREEN_HEIGHT * i / 3 + 3, // y
				SCREEN_WIDTH  * 1/3 - 6, // w
				SCREEN_HEIGHT * 1/3 - 6 // h
			};
			if(board[i][j] == 'X')
				SDL_RenderCopy(
					mainWinRenderer, 
					peiceMarkers[PIECES_X], 
					NULL, 
					&place
				);
			if(board[i][j] == 'O')
				SDL_RenderCopy(
					mainWinRenderer, 
					peiceMarkers[PIECES_O], 
					NULL, 
					&place
				);
		}
	}
	
	// =============  DRAW BACKGROUND  =============
	SDL_Rect vBars[2] = { // vertical bars
		SDL_Rect {
			SCREEN_WIDTH * 1/3 - 3, // x
			0, // y
			6, // w
			SCREEN_HEIGHT // h
		}, 
		
		SDL_Rect {
			SCREEN_WIDTH * 2/3 - 3, 
			0, 
			6, 
			SCREEN_HEIGHT
		}
	};
	
	SDL_Rect hBars[2] = { // horizontal bars
		SDL_Rect {	
			0, 
			SCREEN_HEIGHT * 1/3 - 3, 
			SCREEN_WIDTH, 
			6
		},
		
		SDL_Rect {	
			0, 
			SCREEN_HEIGHT * 2/3 - 3, 
			SCREEN_WIDTH, 
			6
		},
	};
	
	// =============  RENDER  =============
	SDL_SetRenderDrawColor(mainWinRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // color
	SDL_RenderFillRect(mainWinRenderer, &vBars[0]);
	SDL_RenderFillRect(mainWinRenderer, &vBars[1]);
	SDL_RenderFillRect(mainWinRenderer, &hBars[0]);
	SDL_RenderFillRect(mainWinRenderer, &hBars[1]);
	
	// =============  PRESENT  =============
	SDL_RenderPresent(mainWinRenderer);
}

/* 
	@summary		Asks the user to pick a char (X or O)
	
	@param			VOID
	@return			char: the peice the user wants to be
 */
char askChar() {
	// =============  CLEAR SCREEN =============
	SDL_SetRenderDrawColor(mainWinRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mainWinRenderer);
	
	// =============  DISPLAY LEGAL  =============
	displayLegal();
	
	// =============  OUTPUT QUESTION  =============
	// Output text
	SDL_Color textColor = {0xFF, 0xFF, 0xFF}; // White Font
	SDL_Surface* textSurface = TTF_RenderText_Solid( // create Surface for text
		mainFont,
		"Please pick a piece to be:", 
		textColor
	);
	// convert it to texture
	textTexture = SDL_CreateTextureFromSurface(mainWinRenderer, textSurface);
	// get placement
	SDL_Rect textPlace = {
		(SCREEN_WIDTH / 2) - (textSurface->w / 2), 
		(SCREEN_HEIGHT / 4) - (textSurface->h / 2), 
		textSurface->w, 
		textSurface->h
	};	
	// free the memory
	SDL_FreeSurface(textSurface);
	textSurface = NULL;
	// ============= DISPLAY OPTIONS =============
	// Display peices
	SDL_Rect Xpos = {
		40, 
		SCREEN_HEIGHT / 2, 
		SCREEN_WIDTH  * 1/3 - 6,
		SCREEN_HEIGHT * 1/3 - 6
	};
	
	SDL_Rect Opos = {
		SCREEN_WIDTH / 2 + 40, 
		SCREEN_HEIGHT / 2, 
		SCREEN_WIDTH  * 1/3 - 6, 
		SCREEN_HEIGHT * 1/3 - 6
	};
	
	// ============= COPY TO RENDER =============
	SDL_RenderCopy(mainWinRenderer, textTexture, NULL, &textPlace);
	SDL_RenderCopy(mainWinRenderer, peiceMarkers[PIECES_X], NULL, &Xpos);
	SDL_RenderCopy(mainWinRenderer, peiceMarkers[PIECES_O], NULL, &Opos);
	
	// ============= PRESENT =============
	SDL_RenderPresent(mainWinRenderer); // output
	
	
	// ============= WAIT FOR CLICK =============
	SDL_Event gEvent;
	while(true) {
		SDL_PollEvent(&gEvent);
		
		if(gEvent.type == SDL_QUIT) {
			destroy();
			exit(0);
		}
		
		if(gEvent.type == SDL_MOUSEBUTTONUP) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			
			if(
				x > 40 && 
				x < 40 + (SCREEN_WIDTH  * 1/3 - 6) && 
				y > SCREEN_HEIGHT / 2 && 
				y < (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT * 1/3 - 6)
			) return 'X';
			
			if(
				x > SCREEN_WIDTH / 2 + 40 && 
				x < (SCREEN_WIDTH / 2 + 40) + (SCREEN_WIDTH  * 1/3 - 6) &&
				y > SCREEN_HEIGHT / 2 &&
				y < (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT * 1/3 - 6)
			) return 'O';
		}
	}
	return 0;
}

/* 
	@summary		Displays the legal stuff on the opening render
	
	@param			VOID
	@return			VOID
 */
void displayLegal() {
	std::string legal[] = { // array of the legal text (3 lines)
		std::string(
			std::string(R_PROJNAME) +
			std::string(" v") + 
			std::string(R_PVERSION) + 
			std::string(" by ") + 
			std::string(R_AUTHOR)
		), 
		std::string(R_COPYRIGHT), 
		std::string(R_COMMENTS)
	};
	
	SDL_Color legTextColor = {0x80, 0x80, 0x80}; // test color
	
	for(int i = 0; i < 3; ++i) {
		SDL_Surface* legTextSurface = TTF_RenderText_Blended(
			legFont,
			legal[i].c_str(), 
			legTextColor
		);
		textTexture = SDL_CreateTextureFromSurface(
			mainWinRenderer,
			legTextSurface
		);
		SDL_Rect legalPos = {
			(SCREEN_WIDTH / 2) - (legTextSurface->w / 2),
			i * 12, // fontsize: 10, spacing: 4
			legTextSurface->w, 
			legTextSurface->h
		};
		SDL_RenderCopy(mainWinRenderer, textTexture, NULL, &legalPos);
	}
}

/* 
	@summary		Displays the winner and asks if we should play again or exit
	
	@param			string: winner of the game
	@return			bool: if we should play again or not
 */
bool displayWinner(std::string winner) {
	// Concact String
	std::string victoryMsg = winner + std::string(" has won.");
	
	// Set box color and Text color
	SDL_SetRenderDrawColor(mainWinRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Color textColor = {0x00, 0x00, 0xFF};
	
	// ========== display Victory msg ===========
	SDL_Surface* winnerTextSurface = TTF_RenderText_Solid(
		mainFont, 
		victoryMsg.c_str(), 
		textColor
	);
	textTexture = SDL_CreateTextureFromSurface(
		mainWinRenderer, 
		winnerTextSurface
	);
	SDL_Rect winnerTextPos = {	
		(SCREEN_WIDTH / 2) - (winnerTextSurface->w / 2),
		(SCREEN_HEIGHT / 2) - (winnerTextSurface->h / 2), 
		winnerTextSurface->w,
		winnerTextSurface->h
	};
	
	// Draw Victory msg box
	SDL_Rect winnerBox = {
		winnerTextPos.x - 10,
		winnerTextPos.y - 10, 
		winnerTextPos.w + 20,
		winnerTextPos.h + 20
	};
	
	SDL_RenderFillRect(mainWinRenderer, &winnerBox);
	SDL_RenderCopy(mainWinRenderer, textTexture, NULL, &winnerTextPos);
	
	// ========= display Play again text =========
	SDL_Surface* againTextSurface = TTF_RenderText_Solid(
		mainFont, 
		"Play Again?", 
		textColor
	);
	textTexture = SDL_CreateTextureFromSurface(
		mainWinRenderer, 
		againTextSurface
	);
	SDL_Rect againTextPos = { 	
		(SCREEN_WIDTH * 1/4) - (againTextSurface->w / 2),
		(SCREEN_HEIGHT * 3/4) + (againTextSurface->h / 2), 
		againTextSurface->w,
		againTextSurface->h
	};
	// Draw Box
	SDL_Rect againBox = {
		againTextPos.x - 10,
		againTextPos.y - 10, 
		againTextPos.w + 20,
		againTextPos.h + 20
	};
	SDL_RenderFillRect(mainWinRenderer, &againBox);
	SDL_RenderCopy(mainWinRenderer, textTexture, NULL, &againTextPos);
	
	// ============= display Exit text =================
	SDL_Surface* exitTextSurface = TTF_RenderText_Solid(
		mainFont, 
		"Exit", 
		textColor
	);
	textTexture = SDL_CreateTextureFromSurface(
		mainWinRenderer,
		exitTextSurface
	);
	SDL_Rect exitTextPos = {
		(SCREEN_WIDTH * 3/4) - (exitTextSurface->w / 2),
		(SCREEN_HEIGHT * 3/4) + (exitTextSurface->h / 2), 
		exitTextSurface->w,
		exitTextSurface->h
	};
	// Draw Box
	SDL_Rect exitBox = {
		(SCREEN_WIDTH * 3/4) - (againTextSurface->w / 2) - 10,
		exitTextPos.y - 10, 
		againTextPos.w + 20,
		againTextPos.h + 20
	};
	SDL_RenderFillRect(mainWinRenderer, &exitBox);
	SDL_RenderCopy(mainWinRenderer, textTexture, NULL, &exitTextPos);
	
	// ============== Present Render ===================
	SDL_RenderPresent(mainWinRenderer);
	
	// wait for input
	SDL_Event gEvent;
	while(true) {
		while(SDL_PollEvent(&gEvent) != 0) {
			if(gEvent.type == SDL_QUIT) {
				destroy();
				return false;
			}
			
			if(gEvent.type == SDL_MOUSEBUTTONUP) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if(
					x > againBox.x &&
					x < againBox.x + againBox.w &&
					y > againBox.y &&
					y < againBox.y + againBox.h
				) return true;
				
				if(
					x > exitBox.x &&
					x < exitBox.x + exitBox.w &&
					y > exitBox.y &&
					y < exitBox.y + exitBox.h
				) return false;
			}
		}
	}
}

/* 
	@summary		Gets Where the user wants to place his piece
	
	@param			VOID
	@return			int: the place where he wants to place his piece
 */
int getUserChoice() {
	SDL_Event gEvent;
	while(true) {
		while(SDL_PollEvent(&gEvent) != 0) {
			if(gEvent.type == SDL_QUIT) {
				destroy();
				exit(0x001);
			}
			
			if(gEvent.type == SDL_MOUSEBUTTONUP) {
				int x, y;
				SDL_GetMouseState( &x, &y );
				
				int choice = 0;

				if     (y < SCREEN_HEIGHT * 1/3)
					choice = 0;
				else if(y < SCREEN_HEIGHT * 2/3)
					choice = 3;
				else if(y < SCREEN_HEIGHT * 3/3)
					choice = 6;
				
				if     (x < SCREEN_WIDTH * 1/3)
					choice += 0;
				else if(x < SCREEN_WIDTH * 2/3)
					choice += 1;
				else if(x < SCREEN_WIDTH * 3/3)
					choice += 2;
				
				return choice;
				
			}
			// TODO: Highlight when hovering
		}
	}
}

/* 
	@summary		Cleans up the graphics for the next run. Currently does
					nothing
	
	@param			VOID
	@return			VOID
 */
void cleanUpGraphics() {
	
}

/* 
	@summary		Deallocates all the surfaces and memory
	
	@param			VOID
	@return			VOID
 */
void destroy() {
	// Destroy main Renderer
	SDL_DestroyRenderer(mainWinRenderer);
	mainWinRenderer = NULL;
	
	// Destroy peices
	for(auto &i: peiceMarkers) {
		SDL_DestroyTexture(i);
		i = NULL;
	}
	
	// Destroy Text Texture
	SDL_DestroyTexture(textTexture);
	
	// Delete font
	
	// Destroy Window
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;
	
	// Quit subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
