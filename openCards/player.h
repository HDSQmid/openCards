#pragma once



#include "stdafx.h"

#include "gameIO.h"
#include "deck.h"
#include "User.h"
#include "games.h"


class card;
class user;
class gameConfig;

//class "player" provides structure for user while in game
class player {
protected:

	int isUser = 0;

	int numCards;
	card * cards;
	long long int bank;
	int ID; //0 -player, 1 -online player, 2+ -bots
	int inHand; //number of cards currently in hand
	std::string name;

	int score = 0;
	int eliminated = 0;

public:
	//default constructor
	player();

	//remove player from game
	void eliminate(int place);

	int isEliminated();

	//for dealing cards to player
	void recieveCard(card newCrd);

	//for returning cards to deck
	void clearHand();

	//
	//setters for cards
	//

	//for setting name of card
	void setCardName(int num, std::string newName);

	//for temporarily setting rank of card
	void setCardRank(int num, int newRank);

	//for temporarily setting suit of card
	void setCardSuit(int num, int newSuit);

	//for permanently changing card value
	void setCardValue(int num, int newVal);

	//
	//getters for cards
	//



	//for returning name of card to application
	std::string getCardName(int num);

	//for returning rank of card to application
	int getCardRank(int num);

	//for returning suit of card to application
	int getCardSuit(int num);

	//for returning value of card to application
	int getCardValue(int num);

	//function to return type of player as integer
	int getPlayerID();

	std::string getName();

	//function to return type of player as string
	std::string getPlayerTypeS();

	//returns score of player
	int getScore();

	//returns amount in bank of plaer
	long long int getMoney();

	//
	//adders
	//

	void addBadLuck(int amount);

	void addMoney(int amount);

	virtual void addWin();

	virtual void addLoss();

	//
	//prototypes for derived classes
	//

	//prints cards of player if player is user
	virtual void printCards();

	//revelas hand of player
	void revealHand();

	//chooses the order of cards for the game unknwon
	virtual void unknown_chooseOrder(gameConfig game);

	//gets amount that is betted by player
	virtual int bet(int numBets, int currentWinnings, gameConfig game);

	//brings money into game
	virtual void bringMoney();

	//returns money to user if player is user
	virtual void returnMoney();

	//adds bonus money to player
	virtual void addBonusMoney(int amount);

	//decides if player will hit
	virtual int blackjack_willHit(gameConfig game);

	//gets sum. counts aces as one and jokers as one
	virtual int blackJack_getSum();

	//gets sum. asks for values
	virtual int blackJack_getSum(int arg, gameConfig game);

	//choose value for aces: 1 or 11
	int blackjack_aceChooseVal(int sum, gameConfig game);

	//chooses value for jokers: 1 to 11
	virtual int blackjack_jokerChooseVal(int sum, gameConfig game);

};

//player for client
class playerUser : public player {

public:
	//default constructor
	playerUser();

	//
	//functions for game unknown
	//

	//function to print the cards that the user has drawn
	void printCards();

	//function choose order gets order in which cards are placed
	void unknown_chooseOrder(gameConfig game);

	int bet(int numBets, int currentWinnings, gameConfig game);

	void bringMoney();

	void addWin();

	void addLoss();

	void returnMoney();

	void addBonusMoney(int amount);
	

	virtual int blackjack_willHit(gameConfig game);

	virtual int blackjack_aceChooseVal(int sum, gameConfig game);

	virtual int blackjack_jokerChooseVal(int sum, gameConfig game);


};

//mr gupps
class playerGupps : public player {
public:
	//default constructor
	playerGupps();

	//function to print cards in hand does nothing for bot
	void printCards();

	//function to bet money in game
	int bet(int numBets, int currentWinnings, gameConfig game);

	void bringMoney();

	virtual int blackjack_willHit(gameConfig game);

	virtual int blackjack_aceChooseVal(int sum, gameConfig game);

	virtual int blackjack_jokerChooseVal(int sum, gameConfig game);

};

//larry
class playerLarry : public player {
public:
	//default constructor
	playerLarry();

	//function to print cards in hand does nothing for bot
	void printCards();

	//function to bet money in game
	int bet(int numBets, int currentWinnings, gameConfig game);

	void bringMoney();

	virtual void unknown_chooseOrder(gameConfig game);

	virtual int blackjack_willHit(gameConfig game);

	virtual int blackjack_jokerChooseVal(int sum, gameConfig game);

};

//richard
class playerRichard : public player {
public:
	//default constructor
	playerRichard();

	//function to print cards in hand does nothing for bot
	void printCards();

	//function to bet money in game
	int bet(int numBets, int currentWinnings, gameConfig game);

	void bringMoney();

	virtual void unknown_chooseOrder(gameConfig game);

	virtual int blackjack_willHit(gameConfig game);

	virtual int blackjack_jokerChooseVal(int sum, gameConfig game);

};

//cheating charlie
class playerCharlie : public player {

private:
	int numCheats = 0;

public:
	//default constructor
	playerCharlie();

	//function to print cards in hand does nothing for bot
	void printCards();

	//function to bet money in game
	int bet(int numBets, int currentWinnings, gameConfig game);

	void bringMoney();

	virtual void unknown_chooseOrder(gameConfig game);

	virtual int blackjack_willHit(gameConfig game);

	virtual int blackjack_jokerChooseVal(int sum, gameConfig game);

	//gets sum. counts aces as one and jokers as one
	virtual int blackJack_getSum();

	//gets sum. asks for values
	virtual int blackJack_getSum(int arg, gameConfig game);

	//chooses value for aces: 1 or 11
	virtual int blackjack_aceChooseVal(int sum, gameConfig game);


};

	