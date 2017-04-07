/* 
 * Copyright (c) The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>, February 2017
 * 
 * =============================================================================
 * @author			Aryan Gupta
 * @project			Console Tic Tac Toe
 * @title			Program Info
 * @date			2017-03-04 (YYYY-MM-DD)
 * @fversion		1.0.0
 * @description		This is a game where you verse the computer in Tic Tac Toe
 * =============================================================================
 */

#ifndef _info_h_
#define _info_h_

// =================  PROGRAM  INFO  =================
#define R_PVERSION	       /* Version Number */ "4.1.0"
 
#define R_PROJNAME		     /* Project Name */ "Tic Tac Toe"
#define R_PRGMNAME		     /* Program Name */ "Tic Tac Toe"
#define R_DESCRIPTION	      /* Description */ "This is a game where you verse the computer in Tic Tac Toe"

#define R_AUTHOR		     	   /* Author */ "Aryan Gupta"
#define R_COMPANY		          /* Company */ "The Gupta Empire"
#define R_COPYRIGHT				/* Copyright */ "Copyright (c) The Gupta Empire - All Rights Reserved"
#define R_ORGFILENAME  /* Original File Name */ "main.exe" 
#define R_FVERSION		     /* File Version */ "1.0.0"
#define R_COMMENTS		         /* Comments */ "The Gupta Empire - http://theguptaempire.net"
#define R_LEGALTRDMKS	  /* Legal Tademarks */ "..."
#define R_PRIVATEBUILD	    /* Private Build */ "\0" 
#define R_SPECIALBUILD	    /* Special Build */ "\0"

#define R_MAINICON				/* Main Icon */ "./res/icon.ico" 


// =================  MACROS  =================
// DEBUGGING
#define LOGL(msg) if(DEBUG) {std::cout << msg << std::endl;}
#define LOG(msg) if(DEBUG) {std::cout << msg;}

// CLEAR TERMINAL 
#if defined(__linux__) || defined(linux) || defined(__linux)
	#define CLEAR_TERMINAL if(DEBUG){system("clear");}
#elif defined(_WIN32)
	#define CLEAR_TERMINAL if(DEBUG){system("cls");}
#endif

#endif