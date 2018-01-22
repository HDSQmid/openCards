#pragma once



#include "stdafx.h"

#include "deck.h"

#include "gameIO.h"

class player;
class deck;	
class gameConfig;
class store;

//class game contains variables and methods all games use
 class game {

public:
	virtual void play(gameConfig * setup);

};


 //unknown (gambling syndicate game)
 class unknown : public game {



 public:
	 //function for playing the st clare's gambling syndicate game
	 void play(gameConfig * setup);

 };


 //blackjack game
 class blackjack : public game {

 public:

	 //function for playing blackjack
	 void play(gameConfig * setup);

 };


//class gameConfig configurates game
class gameConfig {
public:
	int numGames;
	int * gameType;
	int numPlayers;
	int initialNumPlayers;
	int * playerID;

	deck dck;

	player ** players;

	game ** gamesPtr;

};

void playGame(gameConfig * setup);

gameConfig setupGame();

void startGame();

