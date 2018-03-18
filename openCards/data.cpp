#include "stdafx.h"

#include "data.h"
#include "store.h"
#include "games.h"

void welcome();

	//private

//save player data

const std::string currentDateTime() {
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(p);
	char str[26];
	ctime_s(str, sizeof str, &t);
	return str;
}

//stats
void dataIO::savePlayerStats() {

	//writes data to file
	output.open(PLAYER_STATS_FILE, std::ios::out);
	if (output.is_open()) {


		//            win count                               loss count                            win streak                                best win streak
		output << usr.getWinCt() << " " << usr.getLossCt() << " " << usr.getWinStrk() << " " << usr.getBestWinStrk() << std::endl;
		output << usr.getBank() << std::endl;
		output << usr.getBadLuck() << std::endl;
		output.close();

	}

}
//info
void dataIO::savePlayerInfo() {

	output.open(PLAYER_INFO_FILE, std::ios::out);
	if (output.is_open()) {

		//load player's name
		output << usr.getName();


		input.close();
	}


}
//store
void dataIO::saveStoreData() {

	//writes data to file
	output.open(STORE_DATA_FILE, std::ios::out);
	if (output.is_open()) {

		output << shop.owns("Blackjack") << " " << shop.owns("Unknown") << std::endl;
		output << shop.owns("Mr Gupps") << " " << shop.owns("Larry") << " " << shop.owns("Richard") << std::endl;


		output.close();
	}

}

//load player data

//stats
void dataIO::loadPlayerStats() {


	long long int num;


	//reads in data from file
	input.open(PLAYER_STATS_FILE, std::ios::in);
	if (input.is_open()) {





		input >> num;
		usr.setWinCt((int)num);
		input >> num;
		usr.setLossCt((int)num);
		input >> num;
		usr.setWinStrk((int)num);
		input >> num;
		usr.setBestWinStrk((int)num);


		input >> num;
		usr.setBank(num);

		input >> num;
		usr.setBadLuck((int)num);


		input.close();

	}

	else {

		std::cout << "Error opening file: " << PLAYER_STATS_FILE << std::endl;
		rescue();

	}

	return;
}
//info
void dataIO::loadPlayerInfo() {

	std::string str;

	//reads in data from file
	input.open(PLAYER_INFO_FILE, std::ios::in);
	if (input.is_open()) {

		//load player's name
		std::getline(input, str);
		usr.setName(str);

		input.close();
	}

	else {

		std::cout << "Error opening file: " << PLAYER_INFO_FILE << std::endl;
		rescue();

	}

}
//store
void dataIO::loadStoreData() {

	int num;


	//reads in data from file
	input.open(STORE_DATA_FILE, std::ios::in);
	if (input.is_open()) {

		input >> num;
		shop.setOwn("Blackjack", num);
		input >> num;
		shop.setOwn("Unknown", num);
		input >> num;

		shop.setOwn("Mr Gupps", num);
		input >> num;
		shop.setOwn("Larry", num);
		input >> num;
		shop.setOwn("Richard", num);


		input.close();

	}

	else {

		std::cout << "Error opening file: " << STORE_DATA_FILE << std::endl;
		rescue();

	}

	return;

}

//delete all files
void dataIO::deleteFiles() {

	try {
		remove(PLAYER_INFO_FILE);
	}
	catch (...) {



	}
	try {
		remove(STORE_DATA_FILE);
	}
	catch (...) {



	}
	try {
		remove(PLAYER_STATS_FILE);
	}
	catch (...) {



	}
	try {
		remove(LOG_FILE);
	}
	catch (...) {



	}

	return;

}

int dataIO::testFiles() {

	//reads in data from file
	input.open(PLAYER_STATS_FILE, std::ios::in);
	if (input.is_open()) {
		input.close();

		input.open(PLAYER_INFO_FILE, std::ios::in);
		if (input.is_open()) {
			input.close();

			input.open(STORE_DATA_FILE, std::ios::in);
			if (input.is_open()) {
				input.close();
				return 1;
			}

		}

	}
	return 0;
}

	//public

//fuction for quickly saving
void dataIO::quickSave() {

	savePlayerStats();



}

//fuction for saving all data
void dataIO::save() {

	savePlayerStats();
	saveStoreData();
	savePlayerInfo();


	return;

}

//function from loading data from save
void dataIO::load() {

	if (testFiles()) {

		loadPlayerStats();
		loadStoreData();
		loadPlayerInfo();

	}

	else {

		welcome();

	}


	return;

}

//function to create game setup from template file
gameConfig dataIO::loadGameFromDisc() {

	//reads in data from file
	input.open(DEFAULT_GAME_TEMPLATE_FILE, std::ios::in);
	if (input.is_open()) {

		int inputType = -1;

		int numPlayers = 0;
		int * playerIDs = NULL;

		int numGames = 0;
		int * gameIDs = NULL;

		while (!input.eof()) {
			std::string in;
			int first;
			int last;
			std::getline(input, in);

			//check if input type has changed
			if (in == "player") {

				inputType = 1;
				continue;

			}
			if (in == "game") {

				inputType = 2;
				continue;

			}

			//get next input
			std::stringstream str(in);
			str >> first >> last;

			if (inputType == 1) {

				//reallocate list of players based on number of new players + current number of players
				int * temp = new int[numPlayers + last];

				if (playerIDs != NULL) {
					//copy old list of players to new one
					temp = playerIDs;
				}
				//determine id of new players

				//add new players to list
				for (int ctr = numPlayers; ctr < numPlayers + last; ctr++) {

					temp[ctr] = first;

				}

				//assign new list to pointer
				playerIDs = temp;
				numPlayers += last;

			}

			if (inputType == 2) {

				//reallocate list of games based on number of new games + current number of games
				int * temp = new int[numGames + last];
				if (gameIDs != NULL) {
					//copy old list of games to new one
					temp = gameIDs;
				}
				//determine id of new games

				//add new games to list
				for (int ctr = numGames; ctr < numGames + last; ctr++) {

					temp[ctr] = first;

				}

				//assign new list to pointer
				gameIDs = temp;
				numGames += last;

			}

		}

		input.close();

		gameConfig setup;
		setup.numGames = numGames;
		setup.gameType = gameIDs;
		setup.numPlayers = numPlayers;
		setup.initialNumPlayers = numPlayers;
		setup.playerID = playerIDs;

		game ** tempGames = new game*[setup.numGames];

		//create games
		for (int ctr = 0; ctr < setup.numGames; ctr++) {

			std::string tempS;

			switch (setup.gameType[ctr]) {

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

				switch (setup.gameType[ctr]) {

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

		//create players
		player ** players = new  player*[setup.initialNumPlayers];
		//create players and add to an array of player pointers
		for (int ctr = 0; ctr < setup.numPlayers; ctr++) {

			switch (setup.playerID[ctr]) {

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
				break;

			default:
				std::cout << "Bad Value." << std::endl;

			}



		}

		setup.players = players;

		return setup;


	}
	//else is implied
	std::cout << "Error reading file" << std::endl;
	throw "FileError";

}

//function for deleting game data
int dataIO::rescue() {


	//rescue mode
	std::cout << "Rescue mode activated!" << std::endl;

	std::cout << "Would you like to reset the game and start again? (type \"yes\" to proceed)" << std::endl;

	if (getInput() == "yes") {

		deleteFiles();
		user tempUsr;
		usr = tempUsr;
		store tempStore;
		shop = tempStore;
		std::cout << "You have been successfully rescued!!!" << std::endl;
		
		return 1;

	}

	else {

		std::cout << "We'll just let you drown!" << std::endl;
		
		return 0;

	}

}

void dataIO::log(std::string str) {

	output.open(LOG_FILE, std::iostream::app);
	if (output.is_open()) {

		output << currentDateTime() << "\t" << str << std::endl;

	}
	output.close();
	return;
}

void dataIO::clearLog()
{
	try {
		remove(LOG_FILE);
	}
	catch(...){



	}

	return;


}

dataIO data;