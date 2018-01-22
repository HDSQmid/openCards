#pragma once





#include "stdafx.h"

#include "User.h"
#include "data.h"


struct product {

	bool owns;
	int price;
	std::string name;
	std::string type;



};

class store {

private:

	product nullObj;

	product * all[200];

	product * players[100];
	product user;
	product gupps;
	product larry;
	product richard;
	product charlie;

	product * games[100];
	product blackjack;
	product unknown;

	product * getObj(std::string test);


	int buy(product * cart);

	void filter(std::string type);

	void inventory();

public:

	//constructor
	store();

	//function to check if client owns a product
	int owns(std::string test);

	//function to check ownership and buy if player doesnt own
	int ownsBuy(std::string test);


	void setOwn(std::string cart, int val);

	void enter();

	int getPrice(std::string name);

};

extern store shop;

