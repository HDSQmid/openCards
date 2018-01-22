#include "stdafx.h"

#include "gameIO.h"
#include "games.h"
#include "User.h"
#include "store.h"
#include "data.h"

void menu();

void viewStats();

int checkInputInGame(std::string input, gameConfig * config) {

	int ret = 0;

	//cheat setCardVal sets value of card in specified place
	if (input == "setCardVal") {

		std::string place;

		std::cin >> place;



		if (place == "deck") {

			int num;

			std::cin >> num;

			int newVal;

			std::cin >> newVal;

			cheat.setCardValDeck(config, num, newVal);
			std::cout << "done" << std::endl;

		}

		if (place == "player") {

			int playerNum;

			std::cin >> playerNum;

			int num;

			std::cin >> num;

			int newVal;

			std::cin >> newVal;

			cheat.setCardValPlayer(config->players[playerNum], num, newVal);
			std::cout << "done" << std::endl;
		}

		ret = 1;


	}

	if (input == "revealDeck") {

		cheat.revealDeck(config);

		ret = 1;
	}

	//cheat breakTheBankInGame
	if (input == "breakTheBankInGame") {
		int playerNum;

		int amount;
		std::cin >> playerNum >> amount;
		cheat.breakBankInGame(config->players[playerNum], amount);

		ret = 1;
	}

	//cheat bringMoreMoney
	if (input == "bringMoreMoney") {

		int playerNum;
		std::cin >> playerNum;

		cheat.bringMoreMoney(config->players[playerNum], playerNum);
		ret = 1;
	}

	return ret;
}

int checkInput(std::string input) {

	int ret = 0;

	if (input == "test") {

		std::cout << "AYY LMAO!" << std::endl;

		ret = 1;
	}

	//open menu
	if (input == "menu") {

		menu();

	}

	//start game
	if (input == "startGame") {

		startGame();

		ret = 1;

	}

	//start game from template
	if (input == "loadTemplate") {

		playGame(&(data.loadGameFromDisc()));
		ret = 1;
	}

	//display stats
	if (input == "stats") {

		viewStats();

		ret = 1;

	}

	//quit
	if (input == "quit" || input == "exit") {

		data.save();
		exit(0);

	}

	//open shop
	if (input == "shop") {

		shop.enter();

		ret = 1;

	}

	//save data
	if (input == "save") {

		data.save();

		ret = 1;

	}



	//
	//cheats
	//


	//cheat cheat is a fake
	if (input == "cheat") {

		std::cout << "Did you really think it would be that simple?" << std::endl;
		cheat.testCheat();

		ret = 1;

	}



	//cheat breakTheBank adds money to players bank
	if (input == "breakTheBank") {
		int amount;
		std::cin >> amount;
		cheat.breakTheBank(amount);

		ret = 1;

	}

	//cheat resetBadLuck
	if (input == "resetBadLuck") {
		cheat.resetBadLuck();

		ret = 1;

	}

	//cheat stealItem
	if (input == "steal") {

		std::string str;

		std::cin >> str;

		cheat.stealItem(str);

		ret = 1;

	}

	return ret;

}

//funtion for recieving imput
std::string getInput(gameConfig * config) {

	std::string input;

	while (1 == 1) {

		std::cout << usr.getName() << ">> ";
		std::cin.clear();
		std::cin >> input;

		int cont1 = checkInput(input);
		int cont2 = checkInputInGame(input, config);

		if (cont1 || cont2) continue;

		//back up data before returning
		data.quickSave();

		return input;

	}



}
std::string getInput() {

	std::string input;

	while (1 == 1) {
		std::cout << usr.getName() << ">> ";
		std::cin.clear();
		std::cin >> input;

		int cont1 = checkInput(input);
		if (cont1) continue;

		//back up data before returning
		data.quickSave();

		return input;

	}



}



//function to test if player was caught cheating
void cheats::testCheat() {


	int r = std::rand() % 100;

	if (usr.getBadLuck() > r) {

		std::cout << "you were caught cheating" << std::endl;

		//add bad luck to losses in statistics
		int bdLk = usr.getBadLuck();
		usr.addLoss(bdLk);

		//steal money from the user
		usr.subtractMoney(bdLk * 100);

		//halve bad luck
		usr.halveBadLuck();


	}

	usr.addBadLuck();

	data.quickSave();

	return;

}

//cheat to set the value of a card in the deck
void cheats::setCardValDeck(gameConfig * setup, int num, int newVal) {

	setup->dck.setCardValue(num, newVal);
	testCheat();
}

//cheat to set the value of a card in a player's hand
void cheats::setCardValPlayer(player * plyr, int num, int newVal) {

	plyr->setCardValue(num, newVal);
	testCheat();
}

//cheat to steal money and put it into your slush fund
void cheats::breakTheBank(int amount) {

	usr.addMoney(amount);
	testCheat();
	usr.addBadLuck(amount / 100);

}

//cheat to steal money and put it into your in-game funds
void cheats::breakBankInGame(player * plyr, int amount) {

	plyr->addMoney(amount);
	testCheat();
	usr.addBadLuck(amount / 100);

}

//cheat to reset bad luck
void cheats::resetBadLuck() {

	int bl = usr.getBadLuck();
	usr.subtractMoney(bl * 1000);
	usr.setBadLuck(0);

}

//cheat to reveal deck
void cheats::revealDeck(gameConfig * setup) {

	setup->dck.revealDeck();
	testCheat();

}

//steal item from shop
void cheats::stealItem(std::string item) {

	shop.setOwn(item, 1);
	testCheat();
	usr.addBadLuck(shop.getPrice(item));

}

//cheat to bring more money into the game
void cheats::bringMoreMoney(player * plyr, int playerNum) {

	plyr[playerNum].addMoney(usr.bringMoney());

}



void addBreak() {

	std::cout << "\n";
	return;

}

void addBreak(int amount) {

	std::string out = "";

	for (int ctr = 0; ctr < amount; ctr++) {

		out += "\n";

	}

	std::cout << out;

	return;

}



cheats cheat;