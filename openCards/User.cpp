//user.cpp
//contains the implementation of the class user
//


#include "stdafx.h"


#include "User.h"



	user::user() {

		//sets values
		bank = 0;
		badLuck = 0;
		name = "User";
		winTotal = 0;
		winStreak = 0;
		lossTotal = 0;
	}

	//sends money to player's ingame bank
	int user::bringMoney() {

		int amount;
		std::cout << "enter amount to bring into game" << std::endl;
		std::cout << "you have " << bank << std::endl;
		while (1 == 1) {
			std::string str = getInput();
			std::stringstream stream(str);
			stream >> amount;

			//check if the ammount is good
			if (amount > bank) {
				std::cout << "You can't bring that much! you only have " << bank << std::endl;


			}

			else {
				//check for negitive numbers
				if (amount < 0) {

					std::cout << "You can't bring nothing!" << std::endl;


				}
				else {
					std::cout << "bringing amount of " << amount << " into game" << std::endl;

					bank -= amount;

					std::cout << "new bank value is: " << bank << std::endl;

					return amount;

				}

			}

			std::cout << "try again" << std::endl;

		}

	}

	//steals money from player's bank
	void user::subtractMoney(int ammount) {

		bank -= ammount;

		return;

	}

	//
	//getters
	//

	//get ammount of bad luck
	int user::getBadLuck() {

		return badLuck;

	}

	//get ammount in bank
	long long int user::getBank() {

		return bank;

	}

	//get total number of wins
	int user::getWinCt() {

		return winTotal;

	}

	//get total number of losses
	int user::getLossCt() {

		return lossTotal;

	}

	//get current winning streak
	int user::getWinStrk() {

		return winStreak;

	}

	int user::getBestWinStrk() {

		return bestWinStreak;

	}

	//get name
	std::string user::getName() {

		return name;

	}

	//
	//setters
	//

	//set ammount of bad luck
	void user::setBadLuck(int amount) {

		badLuck = amount;
		return;

	}

	//set win count
	void user::setWinCt(int num) {

		winTotal = num;

	}

	//set loss count
	void user::setLossCt(int num) {

		lossTotal = num;

	}

	//sets win streak
	void user::setWinStrk(int num) {

		winStreak = num;

	}

	//sets best win streak
	void user::setBestWinStrk(int num) {

		bestWinStreak = num;

	}

	//set amount in bank
	void user::setBank(long long int amount) {

		bank = amount;

	}

	//set name
	void user::setName(std::string newName) {

		name = newName;

	}

	//
	//adders
	//

	//adds to bad luck
	void user::addBadLuck(int ammount) {

		badLuck += ammount;

	}

	//add win adds win to statistics
	void user::addWin() {
		winTotal++;
		winStreak++;
		if (winStreak > bestWinStreak) bestWinStreak = winStreak;

	}

	//add loss in statistics
	void user::addLoss(int amount) {

		lossTotal += amount;
		winStreak = 0;

	}

	void user::addMoney(long long int amount) {

		std::cout << "You got: " << amount << " cashies" << std::endl;

		bank += amount;

		std::cout << "New bank value: " << bank <<  " cashies" << std::endl;

	}

	//
	//resetters
	//

	//resets bad luck to 0
	void user::halveBadLuck() {

		badLuck /= 2;
		return;

	}



	user usr;
	
