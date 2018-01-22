#include "stdafx.h"

#include "store.h"

std::string getInput();

//constructor
store::store() {

	//null object
	nullObj.name = "null";
	nullObj.owns = 0;
	nullObj.price = -1;

	for (int ctr = 0; ctr < 200; ctr++) {

		all[ctr] = &nullObj;

	}
	for (int ctr = 0; ctr < 100; ctr++) {

		players[ctr] = &nullObj;

	}
	for (int ctr = 0; ctr < 100; ctr++) {

		games[ctr] = &nullObj;

	}

	//create structures for players and add to arrays
	user.owns = 1;
	user.price = 0;
	user.name = "user";
	players[0] = &user;
	all[0] = &user;

	gupps.owns = 0;
	gupps.price = 500;
	gupps.name = "Mr Gupps";
	players[1] = &gupps;
	all[1] = &gupps;

	larry.owns = 0;
	larry.price = 1000;
	larry.name = "Larry";
	players[2] = &larry;
	all[2] = &larry;

	richard.owns = 0;
	richard.price = 5000;
	richard.name = "Richard";
	players[3] = &richard;
	all[3] = &richard;

	charlie.owns = 0;
	charlie.price = 50000;
	charlie.name = "Charlie";
	players[10] = &charlie;
	all[10] = &charlie;


	//create structures for games

	blackjack.owns = 0;
	blackjack.price = 500;
	blackjack.name = "Blackjack";
	games[0] = &blackjack;
	all[100] = &blackjack;

	unknown.owns = 0;
	unknown.price = 1500;
	unknown.name = "Unknown";
	games[1] = &unknown;
	all[101] = &unknown;


}

//gets location of product from string
product * store::getObj(std::string test) {

	product * temp = &nullObj;

	if (test == "Unknown") temp = &unknown;
	if (test == "Blackjack") temp = &blackjack;

	if (test == "Mr Gupps") temp = &gupps;
	if (test == "Larry") temp = &larry;
	if (test == "Richard") temp = &richard;
	if (test == "Charlie") temp = &charlie;

	if (test == "user") temp = &user;

	return temp;

}

//buys an item from the store
int store::buy(product * cart) {

	if (cart->owns) return 1;

	std::cout << "Are you sure you want to buy " << cart->name << " for " << cart->price << " Cashies? (y/n)" << std::endl;

	char ch;
	std::string str = getInput();
	std::stringstream(str) >> ch;
	int ret = 0;
	if (ch == 'y') {

		if (usr.getBank() >= cart->price) {

			cart->owns = 1;
			usr.subtractMoney(cart->price);
			std::cout << "Success! New bank value: " << usr.getBank() << " Cashies" << std::endl;
			ret = 1;
			data.save();
		}

		else {

			std::cout << "You don't have enough money to complete this purchase. You only have " << usr.getBank() << " Cashies." << std::endl;

		}

	}

	return ret;
}

//filters the store for specific items
void store::filter(std::string type) {

	while (1 == 1) {
		//print game modes
		if (type == "game") {

			std::cout << "These games are available" << std::endl;

			for (int ctr = 0; ctr < 100; ctr++) {

				if (games[ctr]->name == "null") break;
				if (games[ctr]->owns) continue;

				std::cout << ctr + 1 << ": " << games[ctr]->name << " - price: " << games[ctr]->price << std::endl;

			}

		}

		//print players
		if (type == "player") {

			std::cout << "These players are available" << std::endl;

			for (int ctr = 0; ctr < 100; ctr++) {

				if (players[ctr]->name == "null") break;
				if (players[ctr]->owns) continue;

				std::cout << ctr + 1 << ": " << players[ctr]->name << " - price: " << players[ctr]->price << std::endl;

			}

		}

		//print all
		if (type == "all") {

			std::cout << "These products are available" << std::endl;

			for (int ctr = 0; ctr < 200; ctr++) {

				if (all[ctr]->name == "null") continue;
				if (all[ctr]->owns) continue;

				std::cout << ctr + 1 << ": " << all[ctr]->name << " - price: " << all[ctr]->price << std::endl;

			}

		}

		std::cout << "Enter the number of the item you would like to buy or type 'x' to return to the storefront" << std::endl;
		do {
			int id;
			std::string str = getInput();
			if (str == "x") return;

			std::stringstream temp(str);

			temp >> id;

			if (type == "game") {

				if (id > 100 || id < 1) {

					std::cout << "bad value. try again." << std::endl;
					continue;
				}

				buy(games[id - 1]);

			}

			if (type == "player") {

				if (id > 100 || id < 1) {

					std::cout << "bad value. try again." << std::endl;
					continue;
				}

				buy(players[id - 1]);

			}

			if (type == "all") {

				if (id > 200 || id < 1) {

					std::cout << "bad value. try again." << std::endl;
					continue;
				}

				buy(all[id - 1]);

			}


		} while (1 == 0);
	}


	return;

}

//displays all items that the client owns
void store::inventory() {

	std::cout << "You own these items" << std::endl;

	for (int ctr = 0; ctr < 200; ctr++) {

		if (all[ctr]->owns == 0) continue;

		std::cout << ctr + 1 << ": " << all[ctr]->name << std::endl;

	}



}

//function to check if client owns a product
int store::owns(std::string test) {

	product * temp = getObj(test);

	if (temp == &nullObj) return 0;

	if (temp->owns) return 1;
	else return 0;

}

//function to check whether client owns a product and buy it if they dont
int store::ownsBuy(std::string test) {

	product * temp = getObj(test);

	if (temp == &nullObj) return 0;

	if (temp->owns) return 1;

	else {

		std::cout << "You do not own " << temp->name << ". Would you like to buy it for " << temp->price << " Cashies? (y / n)" << std::endl;

		char ch;
		std::string str = getInput();
		std::stringstream(str) >> ch;
		int ret = 0;
		if (ch == 'y') {
			ret = buy(temp);
		}

		return ret;

	}

};

//set whether the client owns a product
void store::setOwn(std::string cart, int val) {

	product * temp = getObj(cart);

	temp->owns = val;

	return;

}

//enters the store
void store::enter() {

	std::cout << "Shopping!!!" << std::endl;

	int validChoice;
	char choice;

	while (1 == 1) {

		//display menu
		std::cout << "\n\n";
		std::cout << "Press 1 to view game modes\n";
		std::cout << "Press 2 to view personas\n";
		std::cout << "Press 0 to view all\n";
		std::cout << "Press r to return to the main menu\n";
		std::cout << "Press i to display your inventory\n";

		std::string temp = getInput();
		std::stringstream str(temp);
		str >> choice;

		do {

			switch (choice) {

			case '1':
				filter("game");
				validChoice = 1;
				break;

			case '2':
				filter("player");
				validChoice = 1;
				break;

			case '0':
				filter("all");
				validChoice = 1;
				break;

			case 'r':
				return;

			case 'i':
				inventory();
				validChoice = 1;
				break;

			default:
				std::cout << "invalid choice. Try again" << std::endl;
				validChoice = 0;
				std::cin >> choice;

			}
			//go to start if choice is invalid
			if (!validChoice) continue;



		} while (1 == 0);
	}
}

int store::getPrice(std::string name) {

	product * temp = getObj(name);

	return temp->price;

}


store shop;