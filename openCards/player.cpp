//class "player" provides structure for user while in game
#include "stdafx.h"

#include "player.h"


//
//player
//

	//default constructor
	player::player() {
		ID = -1;
		numCards = 0;
		inHand = 0;
		name = "null";

	}

	//remove player from game
	void player::eliminate(int place) {
		std::cout << name << " was eliminated from the game because they ran out of money, giving them a placing of " << place << std::endl;
		eliminated = 1;

	}

	int player::isEliminated() {

		return eliminated;

	}

	//for dealing cards to player
	void player::recieveCard(card newCrd) {

		cards[inHand] = newCrd;
		inHand++;

		if (inHand > numCards) numCards = inHand;

		return;
	}

	//for returning cards to deck
	void player::clearHand() {

		inHand = 0;
		return;

	}

	

	//
	//setters for cards
	//

	//for setting name of card
	void player::setCardName(int num, std::string newName) {

		cards[num].setName(newName);
		return;

	}

	//for temporarily setting rank of card
	void player::setCardRank(int num, int newRank) {

		cards[num].setRank(newRank);
		return;

	}

	//for temporarily setting suit of card
	void player::setCardSuit(int num, int newSuit) {

		cards[num].setSuit(newSuit);
		return;

	}

	//for permanently changing card value
	void player::setCardValue(int num, int newVal) {

		cards[num].setValue(newVal);
		return;

	}

	//
	//getters for cards
	//

	//for returning name of card to application
	std::string player::getCardName(int num) {

		return cards[num].getName();

	}

	//for returning rank of card to application
	int player::getCardRank(int num) {

		return cards[num].getRank();

	}

	//for returning suit of card to application
	int player::getCardSuit(int num) {

		return cards[num].getSuit();

	}

	//for returning value of card to application
	int player::getCardValue(int num) {

		return cards[num].getValue();

	}

	//function to return type of player as integer
	int player::getPlayerID() {

		return ID;

	}

	std::string player::getName() {

		return name;

	}

	//function to return type of player as string
	std::string player::getPlayerTypeS() {

		std::string typeS;

		if (ID == 0) typeS = "Player";
		if (ID == 1) typeS = "Online Player";
		if (ID >= 2) typeS = "Bot";

		return typeS;

	}

	//returns score of player
	int player::getScore() {

		return score;

	}

	//returns amount in bank of plaer
	long long int player::getMoney() {

		return bank;

	}

	//
	//adders
	//

	void player::addBadLuck(int amount) {

		return;

	}

	void player::addMoney(int amount) {

		bank += amount;

	}

	void player::addWin() {

		return;

	}

	void player::addLoss() {

		return;

	}
	
	//
	//prototypes for derived classes
	//

	void player::unknown_chooseOrder(gameConfig game) {

		return;

	}
	
	//revelas hand of player
	void player::revealHand() {

		//loop for printing card values
		for (int ctr = 0; ctr < inHand; ctr++) {

			//print name of card
			std::cout << ctr + 1 << ": " << cards[ctr].getName() << std::endl;

		}
		return;

	}

	void player::printCards() {

		return;

	}

	int player::bet(int numBets, int currentWinnings, gameConfig game) {

		return 50;

	}

	void player::bringMoney() {

		bank += 1000;


	}

	void player::returnMoney() {

		bank = 0;


	}

	void player::addBonusMoney(int amount) {

		bank += amount;
		return;

	}

	//decides if player will hit
	int player::blackjack_willHit(gameConfig game) {

		return 0;

	}

	//gets sum. counts aces as one and jokers as one
	int player::blackJack_getSum() {

		int sum = 0;
		int aceCt = 0;
		int jokerCt = 0;
		for (int ctr = 0; ctr < inHand; ctr++) {

			switch (cards[ctr].getRank()) {

				//ace or joker
			case 1:
			case 14:
				sum++;
				break;

			case 11:
			case 12:
			case 13:
				sum += 10;

				break;

			default:
				sum += cards[ctr].getRank();
				break;

			}

		}



		return sum;


	}

	//gets sum. asks for values
	int player::blackJack_getSum(int arg, gameConfig game) {

		int sum = 0;
		int aceCt = 0;
		int jokerCt = 0;
		for (int ctr = 0; ctr < inHand; ctr++) {

			switch (cards[ctr].getRank()) {

				//ace or joker
			case 1:
			case 14:
				sum++;
				break;

			case 11:
			case 12:
			case 13:
				sum += 10;

				break;

			default:
				sum += cards[ctr].getRank();
				break;

			}

		}



		return sum;


	}

	//chooses value for aces: 1 or 11
	int player::blackjack_aceChooseVal(int sum, gameConfig game) {

		int ret;

		if (sum + 11 > 21) {

			ret = 1;

		}
		else {

			ret = 11;

		}

		return ret;

	}

	//chooses value for jokers: 1 to 11
	int player::blackjack_jokerChooseVal(int sum, gameConfig game) {

		int ret;

		if (21 - sum < 11) {

			ret = 21 - sum;

		}
		else {

			ret = 1;

		}

		return ret;
	}


//
//User
//
	
	//default constructor
	playerUser::playerUser() {
		ID = 2;
		card *cardalloc = new card[54];
		cards = cardalloc;
		numCards = 54;
		inHand = 0;
		name = usr.getName();
		isUser = 1;

	}

	//
	//functions for game unknown
	//

	//function to print the cards that the user has drawn
	void playerUser::printCards() {

		//loop for printing card values
		std::cout << "Your cards are:\n";
		for (int ctr = 0; ctr < inHand; ctr++) {

			//print name of card
			std::cout << ctr + 1 << ": " << cards[ctr].getName() << std::endl;

		}
		return;
	}

	//function choose order gets order in which cards are placed
	void playerUser::unknown_chooseOrder(gameConfig game) {


		card *temp = new card[3];


		//prompt user
		std::cout << "choose the order of cards (eg. '1 2 3')" << std::endl;

		int taken[3] = { 0 };

		for (int ctr = 0; ctr < 3; ctr++) {
			int order;
			std::string imput;
			int test;
			do {

				imput = getInput( &game);

				std::stringstream str(imput);
				str >> test;

				if (test > 3 && test < 1) {

					std::cout << "bad imput" << std::endl;
					imput = "";

				}

				else {



					if (taken[test] == 1) {

						std::cout << "this number is already taken" << std::endl;
						imput = "";

					}

					else {



						std::stringstream str(imput);
						str >> order;
					}
				}
			} while ((test > 3 && test < 1) || (taken[test] == 1));
			temp[ctr].setValue(getCardValue(order - 1));

		}

		for (int ctr = 0; ctr < 3; ctr++) {
			int newVal = temp[ctr].getValue();
			setCardValue(ctr, newVal);
		}

	}

	int playerUser::bet(int numBets, int currentWinnings, gameConfig game) {
		int amount;
		std::string in;
		std::cout << "How much would you like to bet?" << std::endl;
		std::cout << "You have " << bank << " available in game" << std::endl;

		if (numBets) {

			if (currentWinnings / numBets <= bank) {

				std::cout << "you must bet at least " << currentWinnings / numBets << std::endl;


				do {

					in = getInput(&game);
					std::stringstream str(in);
					str >> amount;
					if (amount < currentWinnings / numBets || amount > bank) {

						std::cout << "bad value" << std::endl;
						str.clear();


					}
					else break;
				} while (1 == 1);
			}
			else {

				std::cout << "You must bet " << bank << std::endl;
				do {

					in = getInput(&game);
					std::stringstream str(in);
					str >> amount;
					if (amount != bank) {

						std::cout << "bad value" << std::endl;
						str.clear();


					}
					else break;
				} while (1 == 1);

			}


		}

		else {

			do {

				in = getInput(&game);
				std::stringstream str(in);
				str >> amount;
				if (amount < 1 || amount > bank) {

					std::cout << "bad value" << std::endl;
					str.clear();


				}

				else break;

			} while (1 == 1);

		}



		bank -= amount;
		return amount;

	}

	void playerUser::bringMoney() {

		bank += usr.bringMoney();

	}

	void playerUser::addWin() {

		score++;
		usr.addWin();

	}

	void playerUser::addLoss() {

		usr.addLoss();
		return;

	}

	void playerUser::returnMoney() {

		usr.addMoney(bank);
		bank = 0;
		return;

	}

	void playerUser::addBonusMoney(int amount) {

		usr.addMoney(amount);
		return;

	}

	int playerUser::blackjack_willHit(gameConfig game) {
		std::cout << "(h)it or (s)it?" << std::endl;
		while (1 == 1) {

			std::string in = getInput(&game);
			char ch;
			std::stringstream str(in);
			str >> ch;

			if (ch == 'h') return 1;

			if (ch == 's') return 0;

			std::cout << "bad value" << std::endl;

		}
	}

	int playerUser::blackjack_aceChooseVal(int sum, gameConfig game) {

		std::cout << "will your ace be counted as 1 or 11?" << std::endl;

		while (1 == 1) {

			std::string in = getInput(&game);
			int val;
			std::stringstream str(in);
			str >> val;

			if (val == 1) return 1;

			if (val == 11) return 11;

			std::cout << "bad value" << std::endl;

		}

	}

	int playerUser::blackjack_jokerChooseVal(int sum, gameConfig game) {

		std::cout << "what value will your joker be counted as? any integer between 1 and 11" << std::endl;
		int val;
		while (1 == 1) {

			std::string in = getInput(&game);

			std::stringstream str(in);
			str >> val;

			if (val >= 1 || val <= 11) break;



			std::cout << "bad value" << std::endl;

		}

		return val;

	}


//
//Gupps
//

	//default constructor
	playerGupps::playerGupps() {
		ID = 0;
		card *cardalloc = new card[54];
		cards = cardalloc;
		numCards = 54;
		inHand = 0;
		name = "Mr. Gupps";

	}

	//function to print cards in hand does nothing for bot
	void playerGupps::printCards() {

		return;
	}

	//function to bet money in game
	int playerGupps::bet(int numBets, int currentWinnings, gameConfig game) {
		int amount;


		//if first bet has already been made
		if (numBets) {

			//if player has more money than average bet amount
			if (currentWinnings / numBets <= bank / 2 + 1) {

				//if 
				if (bank / 2 + 1 < 500 || bank < 500) {

					amount = (int)bank / 2 + 1;

				}

				else amount = 500;

			}
			//if player has less money than average bet amount they must bet all their money
			else {


				amount = (int)bank;

			}


		}
		//if player is making first bet
		else {

			if (bank / 2 < 500 || bank < 500) {

				amount = (int)bank / 2;

			}

			else amount = 500;

		}



		bank -= amount;
		return amount;

	}

	void playerGupps::bringMoney() {

		bank += 500;

	}

	int playerGupps::blackjack_willHit(gameConfig game) {

		if (blackJack_getSum() < 18 || blackJack_getSum() < 20) return 1;

		else return 0;

	}

	int playerGupps::blackjack_aceChooseVal(int sum, gameConfig game) {

		int ret;

		if (sum + 11 > 23) {

			ret = 1;

		}
		else {

			ret = 11;

		}

		return ret;

	}

	int playerGupps::blackjack_jokerChooseVal(int sum, gameConfig game) {

		int ret;

		if (23 - sum < 11) {

			ret = 23 - sum;

		}
		else {

			ret = 1;

		}

		return ret;
	}


//
//Larry
//

	//default constructor
	playerLarry::playerLarry() {
		ID = 3;
		card *cardalloc = new card[54];
		cards = cardalloc;
		numCards = 54;
		inHand = 0;
		name = "Larry";

	}

	//function to print cards in hand does nothing for bot
	void playerLarry::printCards() {

		return;
	}

	//function to bet money in game
	int playerLarry::bet(int numBets, int currentWinnings, gameConfig game) {
		int amount;


		//if there have already been bets
		if (numBets) {

			//if player has more money in bank than average bet amount
			if (currentWinnings / numBets <= bank / 3 + 1) {


				if (bank / 3 + 1 < 750 || bank < 750) {

					amount = (int)bank / 3 + 1;

				}

				else amount = 750;


			}
			//if player has less money than average bet amount they must bet all their money
			else {


				amount = (int)bank;

			}


		}
		//if player is making the first bet
		else {

			if (bank / 3 < 750 || bank < 750) {

				amount = (int)bank / 3;

			}

			else amount = 750;

		}



		bank -= amount;
		return amount;

	}

	void playerLarry::bringMoney() {

		bank += 500;

	}

	void playerLarry::unknown_chooseOrder(gameConfig game) {

		int tempVals[3];

		tempVals[0] = cards[2].getValue();
		tempVals[1] = cards[0].getValue();
		tempVals[2] = cards[1].getValue();

		for (int ctr = 0; ctr < 3; ctr++) {
			int newVal = tempVals[ctr];
			setCardValue(ctr, newVal);
		}

		return;

	}

	int playerLarry::blackjack_willHit(gameConfig game) {

		if (blackJack_getSum() < 15) return 1;

		else return 0;

	}

	int playerLarry::blackjack_jokerChooseVal(int sum, gameConfig game) {

		int ret;

		if (21 - sum < 11) {

			ret = 21 - sum;

		}
		else {

			ret = 1;

		}

		return ret;
	}


//
//Richard
//

	//default constructor
	playerRichard::playerRichard() {
		ID = 4;
		card *cardalloc = new card[54];
		cards = cardalloc;
		numCards = 54;
		inHand = 0;
		name = "Richard";


	}

	//function to print cards in hand does nothing for bot
	void playerRichard::printCards() {

		return;
	}

	//function to bet money in game
	int playerRichard::bet(int numBets, int currentWinnings, gameConfig game) {
		int amount;


		//if there have been bets
		if (numBets) {

			//if player has more money than the average bet amount
			if (currentWinnings / numBets <= bank / 5 - 1) {


				if (bank / 5 - 1 < 1500 || bank < 1500) {

					amount = (int)bank / 5 - 1;

				}

				else amount = 1500;


			}
			//if player has less money than average bet amount, they must bet all their money
			else {


				amount = (int)bank;

			}


		}
		//if player makes the first bet
		else {

			if (bank / 5 < 1500 || bank < 1500) {

				amount = (int)bank / 5;

			}

			else amount = 1500;

		}



		bank -= amount;
		return amount;

	}

	void playerRichard::bringMoney() {

		bank += 5000;

	}

	void playerRichard::unknown_chooseOrder(gameConfig game) {

		int tempVals[3];

		tempVals[0] = cards[2].getValue();
		tempVals[1] = cards[0].getValue();
		tempVals[2] = cards[1].getValue();

		for (int ctr = 0; ctr < 3; ctr++) {
			int newVal = tempVals[ctr];
			setCardValue(ctr, newVal);
		}

		return;

	}

	int playerRichard::blackjack_willHit(gameConfig game) {

		if (blackJack_getSum() < 15) return 1;

		else return 0;

	}

	int playerRichard::blackjack_jokerChooseVal(int sum, gameConfig game) {

		int ret;

		if (21 - sum < 11) {

			ret = 21 - sum;

		}
		else {

			ret = 1;

		}

		return ret;
	}

//
//Charlie
//

	//default constructor
	playerCharlie::playerCharlie() {
		ID = 10;
		card *cardalloc = new card[54];
		cards = cardalloc;
		numCards = 54;
		inHand = 0;
		name = "Charlie";

	}

	//function to print cards in hand does nothing for bot
	void playerCharlie::printCards() {

		return;
	}

	//function to bet money in game
	int playerCharlie::bet(int numBets, int currentWinnings, gameConfig game) {
		int amount;


		//if there have been bets
		if (numBets) {

			//if player has more money than the average bet amount
			if (currentWinnings / numBets <= bank / 5 - 1) {


				if (bank / 5 - 1 < 1500 || bank < 1500) {

					amount = (int)bank / 5 - 1;

				}

				else amount = 1500;


			}
			//if player has less money than average bet amount, they must bet all their money
			else {


				amount = (int)bank;

			}


		}
		//if player makes the first bet
		else {

			if (bank / 5 < 1500 || bank < 1500) {

				amount = (int)bank / 5;

			}

			else amount = 1500;

		}


		if (rand() % 10 != 0) {
			bank -= amount;
		}

		return amount;

	}

	void playerCharlie::bringMoney() {

		bank += 10000;

	}

	void playerCharlie::unknown_chooseOrder(gameConfig game) {

		int tempVals[3];

		tempVals[0] = cards[2].getValue();
		tempVals[1] = cards[0].getValue();
		tempVals[2] = cards[1].getValue();

		for (int ctr = 0; ctr < 3; ctr++) {
			int newVal = tempVals[ctr];
			setCardValue(ctr, newVal);
		}

		return;

	}

	int playerCharlie::blackjack_willHit(gameConfig game) {

		if (blackJack_getSum() < 14) return 1;

		else return 0;

	}

	int playerCharlie::blackjack_jokerChooseVal(int sum, gameConfig game) {


		if (rand() % 3 == 0) {

			return 21 - sum;

		}

		int ret;

		if (21 - sum < 11) {

			ret = 21 - sum;

		}
		else {

			ret = 1;

		}

		return ret;


	}

	//gets sum. counts aces as one and jokers as one
	int playerCharlie::blackJack_getSum() {
		int sum = 0;
		int aceCt = 0;
		int jokerCt = 0;
		for (int ctr = 0; ctr < inHand; ctr++) {

			switch (cards[ctr].getRank()) {

				//ace or joker
			case 1:
			case 14:
				sum++;
				break;

			case 11:
			case 12:
			case 13:
				sum += 10;

				break;

			default:
				sum += cards[ctr].getRank();
				break;

			}

		}



		return sum;

	}

	//gets sum. asks for values
	int playerCharlie::blackJack_getSum(int arg, gameConfig game) {
		int sum = 0;
		int aceCt = 0;
		int jokerCt = 0;

		if (rand() % 10 == 0) {

			return 21;

		}

		for (int ctr = 0; ctr < inHand; ctr++) {

			switch (cards[ctr].getRank()) {

				//ace
			case 1:
				aceCt++;
				break;

			case 11:
			case 12:
			case 13:
				sum += 10;
				break;
			case 14:
				jokerCt++;
				break;

			default:
				sum += cards[ctr].getRank();
				break;

			}

		}

		for (int ctr = 0; ctr < aceCt; ctr++) {

			sum += blackjack_aceChooseVal(sum, game);

		}

		for (int ctr = 0; ctr < jokerCt; ctr++) {

			sum += blackjack_jokerChooseVal(sum, game);

		}

		return sum;

	}

	//chooses value for aces: 1 or 11
	int playerCharlie::blackjack_aceChooseVal(int sum, gameConfig game) {


		int ret;


		if (rand() % 5 == 0) {

			if (rand() % 3 == 0) {

				return 21 - sum;

			}



			if (21 - sum < 11) {

				ret = 21 - sum;

			}
			else {

				ret = 1;

			}

			return ret;

		}




		if (sum + 11 > 21) {

			ret = 1;

		}
		else {

			ret = 11;

		}

		return ret;

	}


