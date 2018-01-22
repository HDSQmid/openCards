#include "stdafx.h"

#include "gameIO.h"
#include "games.h"
#include "User.h"
#include "store.h"
#include "data.h"

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

//main menu of game
void menu() {
	int validChoice;
	char choice;

	do {

		//display menu
		std::cout << "\nMain menu:" << std::endl;
		std::cout << "Press 1 to start a game\n";
		std::cout << "Press 2 to view statistics\n";
		std::cout << "Press 3 to open the shop\n";
		std::cout << "Press 4 to view game info\n";
		std::cout << "Press 0 to exit\n";

		std::string temp = getInput();
		std::stringstream str(temp);
		str >> choice;

		do {



			switch (choice) {

			case '1':
				startGame();
				validChoice = 1;
				break;

			case '2':
				viewStats();
				validChoice = 1;
				break;

			case '3':
				shop.enter();
				validChoice = 1;
				break;

			case '4':
				printGameInfo();
				validChoice = 1;
				break;

			case '0':
				data.save();
				exit(0);
				validChoice = 1;
				break;

			case 'd':
				varSizes();
				validChoice = 1;
				break;

			default:
				std::cout << "invalid choice. Try again" << std::endl;
				validChoice = 0;
				std::cin >> choice;

			}
			//go to start if choice is invalid
			if (!validChoice) continue;



		} while (1 == 0);
	} while (1 == 0);

	return;
}

//welcome for first run
void welcome() {

	std::cout << "Welcome to openCards " << VERSION_NUM << std::endl;
	
	std::cout << "What do you want us to call you?" << std::endl;

	std::string name;
	std::getline(std::cin, name);
	usr.setName(name);

	addBreak(2);

	std::cout << "Before you can play, you need to have some people to play against. Let's buy Mr Gupps! \nOh, and take 500 Cashies so that you can actually afford it!" << std::endl;
	usr.addMoney(500);
	addBreak();
	while (!shop.ownsBuy("Mr Gupps")) {

		std::cout << "Just buy it." << std::endl;

	}

	addBreak(2);

	std::cout << "You can't play games without owning the games. Let's buy Blackjack!" << std::endl;
	std::cout << "And because you ~~wasted~~ spent all your money on Mr Gupps, you can't afford it, so take another 500 Cashies" << std::endl;
	usr.addMoney(500);
	addBreak();
	while (!shop.ownsBuy("Blackjack")) {

		std::cout << "Just buy it." << std::endl;

	}
	addBreak(2);
	std::cout << "You're all ready to go!!! \nWelcome, and have fun\n" << std::endl;
	std::cout << "And take another 250 Cashies because I feel nice today" << std::endl;
	usr.addMoney(250);

	addBreak(2);

	data.save();
}

//debug function
void varSizes() {

	std::cout << "Size of card: " << sizeof(card) << std::endl;
	std::cout << "Size of deck: " << sizeof(deck) << std::endl;
	std::cout << "Size of user: " << sizeof(user) << std::endl;
	std::cout << "Size of player: " << sizeof(player) << std::endl;
	std::cout << "Size of gameConfig: " << sizeof(gameConfig) << std::endl;
	std::cout << "Size of dataIO: " << sizeof(dataIO) << std::endl;
	std::cout << "Size of cheats: " << sizeof(cheats) << std::endl;

	std::cout << "Rand() Max: " << RAND_MAX << std::endl;

}

//function to print game info
void printGameInfo() {

	std::cout << "Version " << VERSION_NUM << std::endl;
	std::cout << "Built on " << VERSION_BUILD_DATE << std::endl;
	std::cout << "Open Source Software" << std::endl;

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

//function for printing statistics
void viewStats() {

	std::cout << "\n ***STATISTICS*** \n\n" << std::endl;
	std::cout << "Wins: " << usr.getWinCt() << std::endl;
	std::cout << "Losses: " << usr.getLossCt() << std::endl;
	std::cout << "Winning Streak: " << usr.getWinStrk() << std::endl;
	std::cout << "Best Winning Streak: " << usr.getBestWinStrk() << std::endl;
	std::cout << "Money in bank: " << usr.getBank() << std::endl;
	std::cout << "\n";

}


cheats cheat;