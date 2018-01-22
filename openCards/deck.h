#pragma once



#include "stdafx.h"

//class "card" provides structure and functions for cards
class card {

private:
	int value;
	std::string name;
	int rank;
	int suit;
	int blackjackVal;

public:

	//default constructor
	card();

	//constructor with value
	card(int val);

	/**/
	//member functions for card
	/**/

	//
	//member functions for updating cards
	//

	//updates name of card
	void updateName();
	

	//updates rank of card
	void updateRank();

	//updates suit of card
	void updateSuit();


	//
	//member fuctions for setting variables for cards
	//

	//sets rank of card
	void setRank(int newRank);

	//sets value of card
	void setValue(int newVal);

	//sets suit of card
	void setSuit(int newSuit);

	//sets name of card
	void setName(std::string newName);

	//
	//member functions for getting the variables of cards
	//

	//returns name of card
	std::string getName();

	//returns value of card
	int getValue();

	//returns rank of card
	int getRank();

	//returns suit of card
	int getSuit();

};

//class "deck" provides structure for array of cards
class deck {

private:

	int numOfDecks;

	card crds[54];

	int deckRemain;

public:
	//default constructor of deck
	deck();

	//deals a card
	card dealCard();



	//shuffles the deck
	void shuffle();


	//displays cards in deck
	void revealDeck();

	//sets value of specified card
	void setCardValue(int cardNum, int newVal);

	//returns value of specified card
	int getCardValue(int cardNum);

	int getNextCardValue();

	std::string getNextCardName();

	int getNextCardSuit();

	int getNextCardRank();

};

