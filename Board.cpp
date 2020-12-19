/**************************************************
Project: Assignment 3 - Mastermind
Author: Cheryl Neoh Yi Ming
Purpose: Board Class File
**************************************************/

#include "Board.h"

// constructor for the Board class, that sets up the initial values of variables 
// sets up the size of the board according to the skill level ( Room difficulty chosen )
Board::Board(int skillLevel)
{
	noRowsUsed = 0;
	getboardSize(skillLevel);
}

// deconstructor for the Board class
Board::~Board(){}

// function to add the player's guessed code into the vector where all the previous guessed codes were
void Board::addPreviousMove(string move)
{
	previousMove.push_back(move);
	incrementRowsUsed();
}

// function to add the clue's computed into a vector where all the previous guessed code's clues are.
void Board::addClue(string clue)
{
	associatedClue.push_back(clue);
}

// function to display the board using ASCII art, where the boxes store the guessed code's each character
// and the empty space beside the boxes store the clues computed for each guessed code.
void Board::displayBoard()
{
	// displaying the first row which is the where the Hidden Code is.
	cout << "." << string(noCol * 6 + 13, '~') << ".\n"
		<< drawBoxes(string(noCol,' '), "Hidden Code") << endl
		<< "." << string(noCol * 6 + 13, '~') << ".\n";

	// displaying the rows that the player guessed
	for (int num = 0; num < previousMove.size(); num++) {
		cout << drawBoxes(previousMove[num], associatedClue[num]) << endl;
		cout << "." << string(noCol * 6 + 13, '~') << ".\n";
	}
}

// getter function to get the number of rounds that the player has guessed.
int Board::getNoRowsUsed()
{
	return noRowsUsed;
}

// a function to initialise the board according the skillLevel ( Room Level),
// Beginner has ( 10 rows x 4 columns )
// Intermediate has ( 12 rows x 4 columns )
// Advanced has (14 rows x 6 columns )
void Board::getboardSize(int skillLevel)
{
	switch (skillLevel) {
	case 0: // board size 4
		noRow = 10;
		noCol = 4;
		break;
	case 1: // board size 5
		noRow = 12;
		noCol = 5;
		break;
	case 2: // boars size 6
		noRow = 14;
		noCol = 6;
		break;
	}
}

// a private function ( helper function ), used by displayBoard function, it takes one
// guessed code and it's associated clue and puts it in a formatted string, which
// represents a box
// taken from lecture slides and modified
string Board::drawBoxes(string guessed,string clue)
{
 	stringstream board;
	string boxTop = "";
	string boxMid = "";
	string boxBot = "";
	int space = (13 - clue.length()) / 2;
	for (char& c : guessed) {
		boxTop += " .---.";
		boxMid += " | " + string(1,c) + " |";
		boxBot += " '---'";
	}
	board << "|" << boxTop << string(13,' ') << "|" <<endl 
		<< "|" << boxMid << string(space, ' ') << clue << string(space, ' ') << "|" << endl
		<< "|" << boxBot << string(13, ' ') << "|" ;
	return board.str();
}

// function to increment to number of rounds that has already happend
// or the number of rows.
void Board::incrementRowsUsed()
{
	noRowsUsed++;
}

// a getter function to get the number of columns of the board
int Board::getCol()
{
	return noCol;
}

// a getter function to get the number of rows of the board
int Board::getRow()
{
	return noRow;
}