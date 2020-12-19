/**************************************************
Project: Assignment 3 - Mastermind
Author: Cheryl Neoh Yi Ming
Purpose: Player Class File
**************************************************/

#include "Player.h"

// Constructor for our Player class, which initialises the initial variables.
Player::Player(string name, int skillLevel){
	playerName = name;
	playerScore = 0;
	playerToken = 0;
	roomsEntered = 0;
	roomLevel = skillLevel;
	loseDemotion = 0;
	tokenPromotion = 0;
}

// Destructor for our Player Class
Player::~Player(){}

// a getter function that returns the player's name
string Player::getName()
{
	return playerName;
}

// a getter function that returns the player's total accumulated score
int Player::getScore()
{
	return playerScore;
}

// a getter function the returns the number of times the player has broken the code.
// Token represents winning.
int Player::getPlayerToken()
{
	return playerToken;
}

// a getter function the returns the number of rooms that the player has entered,
// including the room that the player has given up on.
int Player::getRoomsEntered()
{
	return roomsEntered;
}

// a getter function that returns the player's chosen skill level or promoted/demoted skill level.
// this determines the board size of a Board object.
int Player::getRoomLevel()
{
	return roomLevel;
}

// a getter function that returns the number of times in a row a player has not managed to break the code.
// does not include the given up rounds.
int Player::getLoseDemotion() {
	return loseDemotion;
}

// a function that takes a score and adds it to the player's current total score.
void Player::addToScore(int toAdd)
{
	playerScore = playerScore + toAdd;
}

// a function to increment when the player succesfully breaks the code.
void Player::incrementToken()
{
	playerToken++;
	tokenPromotion++;
}

// a function to increment the number of rooms entered, when a new board is made.
void Player::incrementRoomsEntered()
{
	roomsEntered++;
}

// a helper function to check if the skill levels are still valid, valid skill levels are only 0, 1, and 2.
// this function makes sure it does become and invalid skill level
void Player::checkRoomLevel()
{
	if (roomLevel > 2) {
		cout << "\n Wow! You have reached the highest level! You A Legend.";
		roomLevel = 2;
	}
	if (roomLevel < 0) {
		cout << "\n Opps! Can't go any lower. You are in the lowest level";
		roomLevel = 0;
	}
}

// a function to promote the player's skill level when the player succesfully breaks the code 5 times.
void Player::incrementSkillLevel() {
	roomLevel++;
	checkRoomLevel();
}

// a function to instantly demote the player's skill level when the player loses 5 times in a row.
void Player::decrementSkillLevel() {
	roomLevel--;
	checkRoomLevel();
}

// a function to increment the number of times a player has lost.
void Player::incrementLoseDemotion()
{
	loseDemotion++;
}

// a function to reset the number of times lost back to 0, when the value reaches 5.
void Player::resetloseDemotion() {
	loseDemotion = 0;
}