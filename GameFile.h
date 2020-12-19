/**************************************************
Project: Assignment 3 - Mastermind
Author: Cheryl Neoh Yi Ming
Purpose: GameFile Header File 
**************************************************/

// inclusion guards
#ifndef GAMEFILE_H
#define GAMEFILE_H

// include statements
#include "Player.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <iterator>
using namespace std;

// Variables
Player* player;
Board* board;
int codeElement;
string hiddenCode;
string clueGenerated;
string guessedCode = "";
int noBlackPegs;
int noWhitePegs;
int noUnusedRow;
bool gameOver = false;
bool gameWon = false;
const char symbols[5] = { '*', '^', '#', '@', '?' };

// Functions
void main();
void displayText(string myFileName);
vector<string> readFile(string myFileName);
void playGame();
string generateHiddenCode();
string getClue(string guessedCode, string hiddenCode);
void displayUI();
int calculateScore(int noBlack, int noWhite, int skillLevel);
void displayPlayerStat(Player player, int roundScore);
string askForString(string question);
int askForNumber(string question, int min, int max);
char askForLetter(string question);
void waitForPlayer();
bool checkGameOver();
void guessHiddenCode();
bool checkLetterForInfo(char character);
void resetGame();
void quit();

#endif 
