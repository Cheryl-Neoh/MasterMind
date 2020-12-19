/**************************************************
Project: Assignment 3 - Mastermind
Author: Cheryl Neoh Yi Ming
Purpose: Player Header File
**************************************************/

// inclusion guards
#ifndef PLAYER_H
#define PLAYER_H

// include statements
#include <string>
#include <iostream>
using namespace std;

// class declaration
class Player {

public:
	// Constructor
	Player(string name, int skillLevel);
	// Destructor
	~Player();
	// Getter Functions
	string getName();
	int getScore();
	int getPlayerToken();
	int getRoomsEntered();
	int getLoseDemotion();
	int getRoomLevel();
	// Functions
	void addToScore(int toAdd);
	void incrementToken();
	void incrementRoomsEntered();
	void incrementSkillLevel();
	void decrementSkillLevel();
	void incrementLoseDemotion();
	void resetloseDemotion();

private:
	// Variables
	string playerName;
	int playerScore;
	int playerToken;
	int roomsEntered;
	int roomLevel;
	int loseDemotion;
	int tokenPromotion;
	// Helper functions
	void checkRoomLevel();
};

#endif 