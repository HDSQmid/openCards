// openCards
//this program is basically cards: computer against humanity.
//it boasts a whopping two games so far, but has quite a few personas to play against. I plan on expanding it

#define VERSION_NUM "Alpha 10"
#define VERSION_BUILD_DATE "22nd January 2018"

#include "stdafx.h"

#include "deck.h"
#include "User.h"
#include "player.h"
#include "games.h"
#include "data.h"
#include "store.h"
#include "gameIO.h"



//starts application. will eventually load data from files
void startApplication(int nNumberofArgs, char*pszArgs[]) {


	srand((unsigned int)time(NULL));

	if (nNumberofArgs == 1) {
		std::cout << "Starting Application..." << std::endl;
		data.load();
	}

	else {

		data.rescue();

		//load data normally 
		data.load();

	}


	return;
}

int main(int nNumberofArgs, char*pszArgs[])
{
	startApplication(nNumberofArgs, pszArgs);

	while (1 == 1) {

		menu();
	}

	std::cout << "lel how tf did you get here" << std::endl;

	system("PAUSE");
    return 0;
}

