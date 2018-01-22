#include "stdafx.h"

#include "deck.h"

//default constructor
card::card() {

	value = 0;
	updateRank();
	updateSuit();
	updateName();

}

//constructor with value
card::card(int val) {

	value = val;
	updateRank();
	updateSuit();
	updateName();

}

/**/
//member functions for card
/**/

//
//member functions for updating cards
//

//updates name of card
void card::updateName() {

	std::string rankS;
	switch (rank)
	{
		//sets string for rank of card
	case 1: rankS = "Ace";
		break;
	case 2: rankS = "2";
		break;
	case 3: rankS = "3";
		break;
	case 4: rankS = "4";
		break;
	case 5: rankS = "5";
		break;
	case 6: rankS = "6";
		break;
	case 7: rankS = "7";
		break;
	case 8: rankS = "8";
		break;
	case 9: rankS = "9";
		break;
	case 10: rankS = "10";
		break;
	case 11: rankS = "Jack";
		break;
	case 12: rankS = "Queen";
		break;
	case 13: rankS = "King";
		break;
	case 14: rankS = "Joker";
		break;

	}

	std::string suitS;
	switch (suit) {
		//sets string for suit of card
	case 1: suitS = "diamonds";
		break;
	case 2: suitS = "clubs";
		break;
	case 3: suitS = "hearts";
		break;
	case 4: suitS = "spades";
		break;
	case 5: suitS = "red";
		break;
	case 6: suitS = "black";
		break;

	}

	name = rankS + " of " + suitS;
	//set name if joker
	if (value == 53) name = "Red joker";
	if (value == 54) name = "Black joker";

	return;
}

//updates rank of card
void card::updateRank() {

	float newRank;

	newRank = (float)(value) / 4;
	newRank = ceil(newRank);

	rank = (int)newRank;

	return;
}

//updates suit of card
void card::updateSuit() {

	if (value == (53)) {
		suit = 5;
	}
	else if (value == 54) {
		suit = 6;
	}
	else {

		suit = (value % 4) + 1;

	}

	return;
}


//
//member fuctions for setting variables for cards
//

//sets rank of card
void card::setRank(int newRank) {

	rank = newRank;
	updateName();
	return;
}

//sets value of card
void card::setValue(int newVal) {

	value = newVal;
	updateRank();
	updateSuit();
	updateName();

	return;
}

//sets suit of card
void card::setSuit(int newSuit) {
	suit = newSuit;
	updateName();
	return;
}

//sets name of card
void card::setName(std::string newName) {

	name = newName;
	return;

}

//
//member functions for getting the variables of cards
//

//returns name of card
std::string card::getName() {

	return name;

}

//returns value of card
int card::getValue() {
	//return value of card
	return value;
}

//returns rank of card
int card::getRank() {
	return rank;
}

//returns suit of card
int card::getSuit() {

	return suit;
}




//default constructor of deck
deck::deck() {

	//set up variables
	numOfDecks = 1;
	shuffle();
	return;
}

//deals a card
card deck::dealCard() {

	card ret = crds[deckRemain];

	deckRemain--;

	if (deckRemain < 0) shuffle();

	return ret;

}



//shuffles the deck
void deck::shuffle() {

	srand((unsigned int)time(NULL));

	//card already taken
	int taken[55] = { 0 };

	//deal out cards
	int val = 0;
	for (int ctr = 0; ctr < 54; ++ctr) {

		do {

			val = (std::rand() % 54) + 1;

		} while (taken[val] == 1);

		crds[ctr].setValue(val);
		taken[val] = 1;
		crds[ctr].updateRank();

	}

	deckRemain = 53;
	return;
}


//displays cards in deck
void deck::revealDeck() {

	//display cards

	for (int ctr = 0; ctr < deckRemain + 1; ctr++) {
		std::cout << "card " << ctr + 1 << ": " << crds[ctr].getName() << " (Value: " << crds[ctr].getValue() << ")" << std::endl;
	}
}

//sets value of specified card
void deck::setCardValue(int cardNum, int newVal) {

	crds[cardNum].setValue(newVal);
	return;

}

//returns value of specified card
int deck::getCardValue(int cardNum) {

	return crds[cardNum].getValue();
}

int deck::getNextCardValue() {

	return crds[deckRemain].getValue();

}

std::string deck::getNextCardName() {

	return crds[deckRemain].getName();

}

int deck::getNextCardSuit() {

	return crds[deckRemain].getSuit();

}

int deck::getNextCardRank() {

	return crds[deckRemain].getRank();

}

