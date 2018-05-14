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

	log("Game progress quick saved");

}

//fuction for saving all data
void dataIO::save() {

	savePlayerStats();
	saveStoreData();
	savePlayerInfo();

	log("Game progress saved");

	return;

}

//function from loading data from save
void dataIO::load() {

	if (testFiles()) {

		loadPlayerStats();
		loadStoreData();
		loadPlayerInfo();
		log("Data loaded");
	}

	else {

		welcome();
		log("First run");

	}


	return;

}

//function to create game setup from template file
gameConfig dataIO::loadGameTemplate(std::string fileLoc = DEFAULT_GAME_TEMPLATE_FILE) {

	//reads in data from file
	input.open(fileLoc, std::ios::in);
	if (input.is_open()) {

		data.log("Loading game from template");
		//read file
		//determine 

		input.close();
	}
	else throw std::exception("Error Reading File");


	gameConfig setup;

	//create game config
	return setup;
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
		log("Game data reset");
		return 1;

	}

	else {

		std::cout << "We'll just let you drown!" << std::endl;
		
		return 0;

	}

}

void dataIO::log(std::string str) {

	logStream.open(LOG_FILE, std::iostream::app);
	if (logStream.is_open()) {

		logStream << currentDateTime() << "\t" << str << std::endl;

		logStream.close();

	}

	else throw std::exception("Error adding log");
	
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