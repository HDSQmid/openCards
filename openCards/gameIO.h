#pragma once




#include "stdafx.h"



class card;
class deck;
class player;
class gameConfig;

class tip {

public:

	std::string hint;

	int probability;

	void setup(std::string value, int probability);

};

class tips {

	int numTips;
	int totalProbability;

	tip hint[100];

public:

	std::string getTip();

	tips();

};
extern tips hint;

//class "cheats" provides structure to cheat
class cheats {
public:

	//function to test if player was caught cheating
	void testCheat();

	//cheat to set the value of a card in the deck
	void setCardValDeck(gameConfig * setup, int num, int newVal);

	//cheat to set the value of a card in a player's hand
	void setCardValPlayer(player * plyr, int num, int newVal);

	//cheat to steal money and put it into your slush fund
	void breakTheBank(int amount);

	//cheat to steal money and put it into your in-game funds
	void breakBankInGame(player * plyr, int amount);

	//cheat to reset bad luck
	void resetBadLuck();

	//cheat to reveal deck
	void revealDeck(gameConfig * setup);

	//steal item from shop
	void stealItem(std::string item);

	//cheat to bring more money into the game
	void bringMoreMoney(player * plyr, int playerNum);

};
extern cheats cheat;

int checkInputInGame(std::string input, gameConfig * config);

int checkInput(std::string input);

//funtion for recieving imput
std::string getInput(gameConfig * config);
std::string getInput();

void addBreak();

void addBreak(int amount);


