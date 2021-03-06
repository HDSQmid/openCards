#pragma once


#include "stdafx.h"

#include "User.h"
#include "player.h"

#define PLAYER_STATS_FILE "stats.gdf"
#define LEGACY_PLAYER_STATS_FILE "null.gdf"

#define PLAYER_INFO_FILE "playerInfo.gdf"
#define STORE_DATA_FILE "store.gdf"

#define DEFAULT_GAME_TEMPLATE_FILE "gameConfig.gsf"

#define LOG_FILE "log.txt"

class gameConfig;

const std::string currentDateTime();

class dataIO {

private:
	std::ofstream output;
	std::ifstream input;
	std::ofstream logStream;

	

	//save player data

	//stats
	void savePlayerStats();
	//info
	void savePlayerInfo();
	//store
	void saveStoreData();

	//load player data

	//stats
	void loadPlayerStats();
	//info
	void loadPlayerInfo();
	//store
	void loadStoreData();

	//delete all files
	void deleteFiles();

	//test if files are written to disc
	int testFiles();

public:
	//fuction for quickly saving
	void quickSave();

	//fuction for saving all data
	void save();

	//function from loading data from save
	void load();

	//function to create game setup from template file
	gameConfig loadGameTemplate(std::string fileLoc);

	//function for deleting game data
	int rescue();

	void log(std::string str);

	void clearLog();

};
extern dataIO data;

