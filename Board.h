/**************************************************
Project: Assignment 3 - Mastermind
Author: Cheryl Neoh Yi Ming
Purpose: Board Header File
**************************************************/

// inclusion guards
#ifndef BOARD_H
#define BOARD_H

// include statements
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// class declaration
class Board {

public:
	// Constructor
	Board(int skillLevel);
	// Destructor
	~Board();
	// Functions
	void addPreviousMove(string move);
	void addClue(string clue);
	void displayBoard();
	int getNoRowsUsed();
	void getboardSize(int skillLevel);
	void incrementRowsUsed();
	// Getter functions
	int getCol();
	int getRow();

private:
	// Variables
	vector <string> previousMove;
	vector <string> associatedClue;
	int noRow;
	int noCol;
	int noRowsUsed;
	// Helper function
	string drawBoxes(string guessed, string clue);
};

#endif 