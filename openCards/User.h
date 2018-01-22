#pragma once


#include "stdafx.h"

#include "gameIO.h"

//class "user" provides structure for user while not in game



class user {

private:
	long long int bank; //money in bank
	int badLuck; //increases when you cheat
	int winTotal; //number of times player has won
	int lossTotal; //number of times player has lost
	int winStreak; //current length of winning streak
	int bestWinStreak; //best length of the winning streak
	std::string name; //name of the player


public:
	//construct player
	user();

	//sends money to player's ingame bank
	int bringMoney();

	//steals money from player's bank
		void subtractMoney(int ammount);

	//
	//getters
	//

	//get ammount of bad luck
		int getBadLuck();

	//get ammount in bank
		long long int getBank();

	//get total number of wins
		int getWinCt();

	//get total number of losses
		int getLossCt(); 

	//get current winning streak
		int getWinStrk();
	//gets best winning streak
		int getBestWinStrk();

	//gets name of user
		std::string getName();

	//
	//setters
	//

	//set ammount of bad luck
		void setBadLuck(int amount);

	//set win count
		void setWinCt(int num);

	//set loss count
		void setLossCt(int num);

	//sets win streak
		void setWinStrk(int num);

	//sets best win streak
		void setBestWinStrk(int num);

	//set amount in bank
		void setBank(long long int amount);

	//set name
		void setName(std::string newName);

	//
	//adders
	//

	//adds to bad luck
		void addBadLuck(int ammount = 1);

	//add win adds win to statistics
		void addWin();

	//add loss in statistics
		void addLoss(int amount = 1);

		void addMoney(long long int amount);

	//
	//resetters
	//

	//halves bad luck
		void halveBadLuck();

};
extern user usr;

