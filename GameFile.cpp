/**************************************************
Project: Assignment 3 - Mastermind
Author: Cheryl Neoh Yi Ming
Purpose: GameFile Class File
**************************************************/

#include "GameFile.h"
#include "Player.h"
#include "Board.h"

// the main function
void main()
{
	// generate seed
	srand(static_cast<unsigned int>(time(0)));
	// display introductory text from howtoplay.txt
	displayText("howtoplay.txt");
	// display description text from description.txt
	displayText("description.txt");
	// displaying the UI to obtain information from player
	displayUI();
	// play the game
	playGame();
}

// a function thats display texts from a file.
// obtained from labs.
void displayText(string myFileName)
{
	fstream fileToDisplay(myFileName);
	string line;
	if (fileToDisplay.is_open()) {
		while (getline(fileToDisplay, line)) {
			cout << line << endl;
		}
		fileToDisplay.close();
	}
	waitForPlayer();
}

// a function that reads a file line by line and stores each line into a vector.
// obtained for labs and modified.
vector<string> readFile(string myFileName)
{
	fstream fileToRead(myFileName);
	vector<string> words;
	string line;
	while (!fileToRead.eof()) {
		getline(fileToRead, line);
		words.push_back(line);
	}
	fileToRead.close();
	return words;
}

// the function to play the game, this function contains the main loop
void playGame()
{
	// initialise board means a player has entered a room
	board = new Board(player->getRoomLevel());
	player->incrementRoomsEntered();
	// generate hidden code according to codeElements and skillLevel
	hiddenCode = generateHiddenCode();

	// game loop
	while (!gameOver) {
		// display title. 
		cout << string(76, '~') << endl
			<< "\t\t\tMasterMind::Code Room" << endl
			<< string(76, '~') << endl;
		// display help, give up and quit symbols on the top.
		cout << "\t [H] 'help'\t\t[X] 'give up' \t\t[Q] 'quit'" << endl;
		// display the board.
		board->displayBoard();
		// display the codeElements that the player can use to guess the code.
		cout << " Hello, " + player->getName() << endl
			<< " Here are some tips to get you started, the code consists of ";

		// asking player to guess the code and update the board's vector.
		guessHiddenCode();
		board->addPreviousMove(guessedCode);

		// calculate the clue associated with the hidden code and store it in the board's clue vector.
		clueGenerated = getClue(guessedCode, hiddenCode);
		board->addClue(clueGenerated);

		// check if game is over and check if the player can be promoted/demoted if the player succesfully breaks the code.
		checkGameOver();
		if (gameWon || gameOver) {

			// giving feedback to the player.
			if (gameWon) {
				cout << "\n\n Congratuations on guessing the code, Please collect your token and deposit it into the nearest chest." << endl
					<< "\n Here is a summary of the scores collected:" << endl;
			}
			else {
				cout << "\n What a shame..Try again?\n Here is a summary of the scores collected" << endl;
			}

			// calculating score and displaying player's stats
			int round_score = calculateScore(noBlackPegs, noWhitePegs, player->getRoomLevel());
			player->addToScore(round_score);
			displayPlayerStat(*player, round_score);

			// displaying how many more tokens to get for until promotion and how many points till it automatically demotes.
			cout << "\n You need to collect " << to_string(5 - (player->getPlayerToken() % 6)) << " more tokens to be promoted to the next level...\n";
			cout << " You will be instantly demoted if " << to_string(player->getLoseDemotion()% 6) << " reaches 5...\n";

			// promotes the player's skill level if the player has won 5 times.
			if ((5 - player->getPlayerToken() % 6) == 0) {
				char choice = askForLetter("\n Would you like to be promoted to the next level? (Y/N)");
				while (choice != 'Y' && choice != 'N') {
					choice = askForLetter("I don't understand..Would you like to be promoted to the next level? (Y/N)");
				}
				if (choice == 'Y') {
					player->incrementSkillLevel();
				}
			}

			// demotes the player's skill automatically when the player has lost 5 times in a row.
			if (player->getLoseDemotion() % 6 == 5) {
				player->decrementSkillLevel();
			}

		}

		// reset the guessed code and wait for player to respond if player did not guess correctly.
		guessedCode = "";
		if (!gameWon) {
			waitForPlayer();
		}
	}

	// asking if player wants to play again
	char playAgain = askForLetter("\n Do you want to continue to the next room? (Y/N) ");
	while (playAgain != 'Y' && playAgain != 'N') {
		playAgain = askForLetter("Ok..Wait what? Y/N? Would you like to go to a new room? (Y/N) ");
	}

	// reset game parameters
	if (playAgain == 'Y') {
		resetGame();
		waitForPlayer();
		playGame();
	}
	else {
		quit();
	}
}

// function to ask player to guess the hidden code according to the code element ( difficulty ) that the player
// has picked.
void guessHiddenCode() {
	switch (codeElement) {
	// when the code elements chosen are numbers only.
	case 0:
		cout << ": 0 1 2 3 4 5\n";
		char number;
		for (int num = 0; num < board->getCol(); num++) {
			number = askForLetter(" Guess For Column " + to_string(num + 1) + ": ");
			// checks if the number is a valid number
			while (toascii(number) > 53 || toascii(number) < 48) {
				// checks if the player is asking for 'H', 'X', or 'Q'
				if (checkLetterForInfo(number)) {
					resetGame();
					playGame();
				}
				else {
					number = askForLetter("Invalid number! Guess For Column " + to_string(num + 1) + ": ");
				}
			}
			guessedCode += number;
		}
		break;

	// when the code elements chosen consist of selected symbols only.
	case 1:
		cout << ": * ^ # @ ?\n";
		char guessedSymbol;
		for (int num = 0; num < board->getCol(); num++) {
			guessedSymbol = askForLetter(" Guess For Column " + to_string(num + 1) + ": ");
			// checks if the symbol is a valid symbol
			while (find(begin(symbols), end(symbols), guessedSymbol) == end(symbols)) {
				// checks if the player is asking for 'H', 'X', or 'Q'
				if (checkLetterForInfo(guessedSymbol)) {
					resetGame();
					playGame();
				}
				else {
					guessedSymbol = askForLetter(" Invalid symbol! Guess For Column " + to_string(num + 1) + ": ");
				}
			}
			guessedCode += guessedSymbol;
		}
		break;

	// when the code elements chosen consist of english words.
	case 2:
		cout << "english words.\n";
		guessedCode = askForString("Guessed word : ");
		// checking if the length of the word guessed fits the board
		while (guessedCode.length() != board->getCol()) {
			// checks if the player is asking for 'H', 'X', or 'Q'
			if (guessedCode.length() == 1) {
				char character = guessedCode[0];
				if (checkLetterForInfo(toupper(character))) {
					resetGame();
					playGame();
				}
			}
			else {
				guessedCode = askForString("Too long/short! Guess code : ");
			}
		}
		break;
	}

}

// function to generate the hidden code according the the code elements available
string generateHiddenCode()
{
	string hiddenCode = "";
	int lengthOfCode = board->getCol();
	int randomIndex;
	vector <string> words;
	switch (codeElement) {
	case 0: // the code will consist of numbers from 0-5
		for (int num = 0; num < lengthOfCode; num++) {
			hiddenCode += to_string(rand() % 5 + 1);
		}
		break;
	case 1: // consist of symbols * ^ # @ ?
		for (int num = 0; num < lengthOfCode; num++) {
			int index = rand() % 5;
			hiddenCode += symbols[index];
		}
		break;
	case 2: // consist of proper words
		if (lengthOfCode == 4) {
			words = readFile("length4words.txt");
		}
		else if (lengthOfCode == 5) {
			words = readFile("length5words.txt");
		}
		else {
			words = readFile("length6words.txt");
		}
		randomIndex = rand() % words.size();
		hiddenCode = words[randomIndex];
		break;
	default:
		codeElement = askForNumber("Difficulty", 0, 2);
	}
	return hiddenCode;
}

// function to compute the clues associated to the guessed clue
string getClue(string guessedCode, string hiddenCode){
	int correctPos = 0;    // the number of correct characters at the correct position
	int correctVal = 0;	   // the number of correct characters but not at correct postion
	string clue;
	
	// comparing the hidden code and guessed code
	for (int num = 0; num < board->getCol(); num++) {
		if (find(begin(hiddenCode), end(hiddenCode), guessedCode[num]) != end(hiddenCode)) {
			correctVal++;
		}
		if (hiddenCode[num] == guessedCode[num]) {
			correctPos++;
		}
	}


	clue = string(correctPos, '/') + string(correctVal - correctPos, 'o');
	int space = clue.length() - 1;
	// to separate each clue with a space
	for (int num = 1; num < clue.length(); num = num+2) {
		string first = clue.substr(0, num);
		string last = " " + clue.substr(num, clue.length());
		clue = first + last;
	}

	// winGame condition when the number of correct characters at the correct position is equal to the number of columns of the board.
	if (correctPos == board->getCol()) {
		gameWon = true;
	}

	// updating the total clue pegs
	noBlackPegs = noBlackPegs + correctPos;
	noWhitePegs = noWhitePegs + (correctPos - correctVal);
	return clue;
}

// displaying the UI to obtain information from player
void displayUI()
{
	// display title
	cout << string(76, '~') << endl
		<< "\t\t\tMasterMind::Code Room" << endl
		<< string(76, '~') << endl;
	// asking player for details
	string name = askForString("\t\t\t\t Name: ");
	int skillLevel = askForNumber("\t\tRoom Level", 0, 2);
	codeElement = askForNumber("\t\tDifficulty", 0, 2);
	// creating the player object
	player =  new Player(name, skillLevel);
	cout << "\n These are your initial stats :\n";	
	displayPlayerStat(*player, 0);
	// wait for player
	waitForPlayer();
}

// function to calculate the score after the lossing or winning one game
int calculateScore(int noBlack, int noWhite, int skillLevel)
{
	int noUnusedRow = board->getRow() - board->getNoRowsUsed();
	return (noBlackPegs*2) + noWhitePegs + (skillLevel+1)*noUnusedRow;
}

// function to display the player's statistics, it contains the player's name, skill level,
// scores, tokens , etc.
void displayPlayerStat(Player player, int roundScore)
{
	cout << string(50, '~') << endl
		<< "  Name: " << player.getName() << endl
		<< "  Level: ";

	switch (player.getRoomLevel()) {
	case 0:
		cout << "Beginner" << endl;
		break;
	case 1:
		cout << "Intermediate" << endl;
		break;
	case 2:
		cout << "Advanced" << endl;
		break;
	}

	cout << "  Total Rooms Entered: " << player.getRoomsEntered() << endl
		<< "  Tokens obtained: " << player.getPlayerToken() << endl
		<< "  Score: " << roundScore << endl
		<< "  Total: " << player.getScore() << endl
		<< string(50, '~') << endl;
}

// ask user for an input string
string askForString(string question)
{
	string userInput = "";
	while (userInput == "") {
		cout << " " << question;
		getline(cin, userInput);
	}
	return userInput;
}

// ask for a number in between max and min
int askForNumber(string question, int min, int max)
{
	int num = - 9999;
	while (num < min || num > max) {
		cout << question << " ( " << min << " to " << max << " ): ";
		cin >> num;
	}
	return num;
}

// ask for a letter and uppercase it
char askForLetter(string question)
{
	char character = ' ';
	while (character == ' ') {
		cout << question;
		cin >> character;
	}
	return toupper(character);
}

// pause for player and clears the screen
void waitForPlayer()
{
	cout << "\n\t\t\t";
	system("pause");
	system("cls");

}

// checks if the game is over, when there are no more rows left or if the player won the round.
bool checkGameOver()
{
	// when there are no more rows left for the player to guess anymore
	if (board->getNoRowsUsed() == board->getRow()) {
		gameOver = true;
		player->incrementLoseDemotion();
	}
	// when the player succesfully guesses the hidden code
	if (gameWon) {
		gameOver = true;
		player->incrementToken();
		player->resetloseDemotion();
	}
	return gameOver;
}

// checks when the player is guessing, the player inputs a 'H', asking for help or 'X' to give up and play a different board
// or 'Q' to quit the game
bool checkLetterForInfo(char character)
{
	if (character == 'H') {
		system("cls");
		displayText("howtoplay.txt");
	}
	else if (character == 'X') {
		displayPlayerStat(*player, 0);
		char tryAgain = askForLetter("That was unfortunate..Would you like to go to a new room? (Y/N) ");
		while (tryAgain != 'Y' && tryAgain != 'N') {
			tryAgain = askForLetter("Uhh..is that a Y/N? Would you like to go to a new room? (Y/N) ");
		}
		if (tryAgain == 'N') {
			quit();
		}
		waitForPlayer();
		system("cls");
		gameOver = true;
		return true;
	}
	else if (character == 'Q')
	{
		char areYouSure = askForLetter("Do you really want to leave the room? (Y/N) ");
		while (areYouSure != 'Y' && areYouSure != 'N') {
			areYouSure = askForLetter("Uhm..Come again? Do you really want to leave the room? (Y/N) ");
		}
		if (areYouSure == 'Y') {
			quit();
		}
		system("cls");
	}
	system("cls");
	cout << string(76, '~') << endl
		<< "\t\t\tMasterMind::Code Room" << endl
		<< string(76, '~') << endl;
	cout << "\t [H] 'help'\t\t[X] 'give up' \t\t[Q] 'quit'" << endl;
	board->displayBoard();
	return false;
}

// function to reset the game if the player wants to go to the next room.
void resetGame()
{
	guessedCode = "";
	noBlackPegs = 0;
	noWhitePegs = 0;
	gameOver = false;
	gameWon = false;
}

// function to quit the game.
void quit()
{
	cout << "\n I hope you had fun, come again next time! \n"
		 << " The exit door is opened, You may leave.\n\n"
		 << " These are your final stats: \n";
	displayPlayerStat(*player, 0);
	exit(0);
}
