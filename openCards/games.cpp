#include "stdafx.h"

#include "games.h"
#include "player.h"
#include "store.h"


void game::play(gameConfig * setup) {

	return;

}


//function for playing the st clare's gambling syndicate game
void unknown::play(gameConfig * setup) {

	std::cout << "Unknown" << std::endl;

	if (setup->numPlayers > 2) {

		std::cout << "can't have more than 2 players in this game" << std::endl;
		return;

	}
	int winnings = 0;

	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		winnings += setup->players[ctr]->bet(ctr, winnings, *setup);

	}





	//loops for dealing cards to players
	for (int outer = 0; outer < setup->numPlayers; outer++) {

		//deal to players
		for (int inner = 0; inner < 3; inner++) {


			card temp = setup->dck.dealCard();

			setup->players[outer]->recieveCard(temp);

		}
	}

	//loop for printing cards of each player
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		setup->players[ctr]->printCards();
		setup->players[ctr]->unknown_chooseOrder(*setup);

	}








	//determine winners in each lane
	std::cout << "checking cards...\n";
	int score = 0;
	for (int ctr = 0; ctr < 3; ctr++) {

		std::cout << "testing " << setup->players[0]->getName() << "'s " << setup->players[0]->getCardName(ctr) << " against " << setup->players[1]->getName() << "'s " << setup->players[1]->getCardName(ctr) << std::endl;

		//if player 0's card is joker
		if (setup->players[0]->getCardRank(ctr) == 14) {

			//if player 1's card is an ace -- jokers only beat aces
			if (setup->players[1]->getCardRank(ctr) == 1) {
				score++;
				std::cout << setup->players[0]->getName() << "'s card won" << std::endl;
			}
			else {
				score--;
				std::cout << setup->players[1]->getName() << "'s card won" << std::endl;
			}

		}

		//if player 1's card is joker
		else {
			if (setup->players[1]->getCardRank(ctr) == 14) {

				//if player 0's card is an ace -- jokers only beat aces
				if (setup->players[0]->getCardRank(ctr) == 1) {
					score--;
					std::cout << setup->players[1]->getName() << "'s card won" << std::endl;
				}
				else {
					score++;
					std::cout << setup->players[0]->getName() << "'s card won" << std::endl;
				}

			}

			else {

				if (setup->players[0]->getCardRank(ctr) == 1) {

					score++;
					std::cout << setup->players[0]->getName() << "'s card won" << std::endl;

				}

				else {

					if (setup->players[1]->getCardRank(ctr) == 1) {

						score--;
						std::cout << setup->players[1]->getName() << "'s card won" << std::endl;

					}

					else {

						//if player's card rank is greater than bot's card, win
						if (setup->players[0]->getCardRank(ctr) > setup->players[1]->getCardRank(ctr)) {

							score++;
							std::cout << setup->players[0]->getName() << "'s card won" << std::endl;


						}
						else {
							score--;
							std::cout << setup->players[1]->getName() << "'s card won" << std::endl;
						}

					}

				}

			}

		}
	}


	if (score > 0) {
		std::cout << setup->players[0]->getName() << " (Player " << 1 << ") won" << std::endl;
		setup->players[0]->addMoney(winnings);
		setup->players[0]->addWin();
		setup->players[1]->addLoss();

	}
	else {
		std::cout << setup->players[1]->getName() << " (Player " << 2 << ") won" << std::endl;
		setup->players[1]->addMoney(winnings);
		setup->players[1]->addWin();
		setup->players[0]->addLoss();
	}

	return;
}



//function for playing blackjack
void blackjack::play(gameConfig * setup) {

	std::cout << "Blackjack" << std::endl;

	int winnings = 0;

	//get bets
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		winnings += setup->players[ctr]->bet(ctr, winnings, *setup);

	}

	std::cout << "\n\n";

	//loops for dealing cards to players
	for (int outer = 0; outer < setup->numPlayers; outer++) {

		//deal to players
		for (int inner = 0; inner < 2; inner++) {


			card temp = setup->dck.dealCard();

			setup->players[outer]->recieveCard(temp);

		}
		setup->players[outer]->printCards();
	}

	std::cout << "\n\n";

	//hit or sit
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		if (setup->players[ctr]->blackjack_willHit(*setup)) {
			card temp = setup->dck.dealCard();
			setup->players[ctr]->recieveCard(temp);
			setup->players[ctr]->printCards();

			if (setup->players[ctr]->blackJack_getSum() > 21) {

				std::cout << setup->players[ctr]->getName() << " (Player " << ctr + 1 << ") went bust with a score of " << setup->players[ctr]->blackJack_getSum() << std::endl;

			}
			else ctr--;
			continue;
		}

		//get more bets


		winnings += setup->players[ctr]->bet(ctr, winnings, *setup);



	}

	//decide winner
	int *winner = new int[setup->numPlayers];
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		winner[ctr] = 0;

	}

	std::cout << "\n\n";

	int bestScore = 0;
	int numWinners = 0;
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		int sumTemp = setup->players[ctr]->blackJack_getSum(0, *setup);

		std::cout << "\n\n";

		//check if player went bust
		if (sumTemp > 21) {

			std::cout << setup->players[ctr]->getName() << " (Player " << ctr + 1 << ") went bust with a score of " << sumTemp << " and the cards:" << std::endl;
			setup->players[ctr]->revealHand();
			continue;

		}

		std::cout << setup->players[ctr]->getName() << " (Player " << ctr + 1 << ") scored " << sumTemp << " with the cards:" << std::endl;
		setup->players[ctr]->revealHand();

		if (sumTemp > bestScore) {

			for (int inner = 0; inner < ctr; inner++) {

				winner[inner] = 0;

			}
			winner[ctr] = 1;
			numWinners = 1;
			bestScore = sumTemp;
		}
		else {

			if (sumTemp == bestScore) {

				winner[ctr] = 1;
				numWinners++;

			}

		}

	}

	std::cout << "\n\n";

	if (numWinners > 1) std::cout << "Winners are:" << std::endl;
	else std::cout << "Winner is:" << std::endl;
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		if (winner[ctr]) {
			std::cout << setup->players[ctr]->getName() << " (Player " << ctr + 1 << ")" << std::endl;
			setup->players[ctr]->addWin();
			setup->players[ctr]->addMoney(winnings / numWinners);
		}

		else {

			setup->players[ctr]->addLoss();

		}
	}

	std::cout << "\n\n";

	
	return;
}


//function for playing the games
void playGame(gameConfig * setup) {

	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		setup->players[ctr]->bringMoney();

	}

	//launch the games
	for (int ctr = 0; ctr < setup->numGames; ctr++) {

		std::cout << "starting game " << ctr + 1 << ": ";
		setup->gamesPtr[ctr]->play(setup);

		//eliminate players
		int numEliminations = 0;
		for (int inner = 0; inner < setup->numPlayers; inner++) {

			setup->players[inner]->clearHand();
			if (setup->players[inner]->getMoney() <= 0) {

				setup->players[inner]->eliminate(setup->numPlayers);
				numEliminations++;

			}

		}

		setup->numPlayers -= numEliminations;
		if (setup->numPlayers == 1) {
			std::cout << "Only one player left in game. Exiting to main menu" << std::endl;
			break;

		}



	}

	//check for winners
	int placing1 = -1;
	int placing2 = -1;
	int placing3 = -1;
	int highhestWinCt = -1;
	for (int ctr = 0; ctr < setup->initialNumPlayers; ctr++) {
		std::cout << setup->players[ctr]->getName() << " (Player " << ctr + 1 << ") won " << setup->players[ctr]->getScore() << " times" << std::endl;
		setup->players[ctr]->returnMoney();
		if (setup->players[ctr]->getScore() > highhestWinCt) {

			placing3 = placing2;
			placing2 = placing1;
			placing1 = ctr;
			highhestWinCt = setup->players[ctr]->getScore();

		}

	}

	//give bonus money to players remaining
	for (int ctr = 0; ctr < setup->numPlayers; ctr++) {

		if (!setup->players[ctr]->isEliminated()) {

			setup->players[ctr]->addBonusMoney(100 * setup->initialNumPlayers / setup->numPlayers);

		}

	}


	if (placing1 != -1) {
		setup->players[placing1]->addBonusMoney(100);
		std::cout << "1st Place: " << setup->players[placing1]->getName() << " (Player " << placing1 + 1 << ")" << std::endl;
	}
	if (placing2 != -1 && setup->numPlayers > 2) {
		setup->players[placing2]->addBonusMoney(50);
		std::cout << "2nd Place: " << setup->players[placing2]->getName() << " (Player " << placing2 + 1 << ")" << std::endl;
	}
	if (placing3 != -1 && setup->numPlayers > 3) {
		setup->players[placing3]->addBonusMoney(50);
		std::cout << "3rd Place: " << setup->players[placing3]->getName() << " (Player " << placing3 + 1 << ")" << std::endl;
	}

	return;
}

//function setUpGame sets up and starts game
gameConfig setupGame() {

	std::cout << "setting up game\n";
	gameConfig setup;
	std::string in;
	std::stringstream str;
	std::cout << "How many games?\n";

	do {

		in = getInput();
		str << in;
		str >> setup.numGames;

		//break loop if good value
		if (setup.numGames > 0) {
			break;

		}
		std::cout << "you can't play less than one game!" << std::endl;

	} while (1 == 1);

	int * tempGameTypes = new int[setup.numGames];
	game ** tempGames = new game*[setup.numGames];

	//get game modes
	for (int ctr = 0; ctr < setup.numGames; ctr++) {

		std::cout << "What is the game mode for game " << ctr + 1 << "?" << std::endl;
		std::cout << "1: Black Jack" << std::endl;
		std::cout << "2: Unknown" << std::endl;
		in = getInput();
		str.clear();
		str << in;
		str >> tempGameTypes[ctr];
		std::string tempS;
		switch (tempGameTypes[ctr]) {

		case 1: tempS = "Blackjack";
			break;

		case 2: tempS = "Unknown";
			break;

		default:
			std::cout << "That game mode doesn't exist." << std::endl;
			tempS = "not a game mode";

		}
		//if they don't own the game mode
		if (!(shop.ownsBuy(tempS))) {

			ctr--;
			std::cout << "Enter a new game mode" << std::endl;
			continue;

		}
		else {

			switch (tempGameTypes[ctr]) {

				//blackjack
			case 1: tempGames[ctr] = new blackjack;
				break;

				//unknown
			case 2: tempGames[ctr] = new unknown;
				break;

			default:
				std::cout << "That game mode doesn't exist." << std::endl;
				tempS = "not a game mode";

			}

		}

	}

	setup.gamesPtr = tempGames;



	setup.gameType = tempGameTypes;


	std::cout << "How many players?" << std::endl;

	do {

		str.clear();
		in = getInput();
		str << in;
		str >> setup.initialNumPlayers;


		//break loop if good value
		if (setup.initialNumPlayers > 1) {

			setup.numPlayers = setup.initialNumPlayers;


			break;

		}
		std::cout << "bad value. try again\n";


	} while (1 == 1);
	player ** players = new  player*[setup.initialNumPlayers];
	int * tempPlayerIDs = new int[setup.numPlayers];


	//loop to get player ID
	for (int ctr = 0; ctr < setup.numPlayers; ctr++) {

		std::cout << "who will be player " << ctr + 1 << "?\n";
		std::cout << "0: You (The user)\n";
		std::cout << "2: Mr Gupps\n";
		std::cout << "3: Larry\n";
		std::cout << "4: Richard\n";
		std::cout << "10: Charlie\n";
		str.clear();
		in = getInput();
		str << in;
		str >> tempPlayerIDs[ctr];
		std::string tempS;
		switch (tempPlayerIDs[ctr]) {

		case 0: tempS = "user";
			break;

		case 2: tempS = "Mr Gupps";
			break;

		case 3: tempS = "Larry";
			break;

		case 4: tempS = "Richard";
			break;

		case 10: tempS = "Charlie";
			break;

		default:
			std::cout << "That player doesn't exist." << std::endl;
			tempS = "not a player";

		}
		//if they don't own the game mode
		if (!(shop.ownsBuy(tempS))) {

			ctr--;
			std::cout << "Enter a new player ID" << std::endl;
			continue;

		}


	}


	//create players and add to an array of player pointers
	for (int ctr = 0; ctr < setup.numPlayers; ctr++) {

		switch (tempPlayerIDs[ctr]) {

		case 0:
			players[ctr] = new playerUser;
			break;



		case 2:
			players[ctr] = new playerGupps;
			break;

		case 3:
			players[ctr] = new playerLarry;
			break;

		case 4:
			players[ctr] = new playerRichard;
			break;

		case 10:
			players[ctr] = new playerCharlie;

		default:
			std::cout << "Bad Value." << std::endl;

		}



	}

	setup.players = players;






	return setup;
}

//function for preparing to play games
void startGame() {

	gameConfig config = setupGame();


	playGame(&config);


	return;

}