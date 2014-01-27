

//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu
//This is the main function, it makes sure the user puts in the right input and then repeated calls before_round, round, and
//after_round until there are no players left in the game

#include "stdafx.h"
#include "rwfuncs.h"
#include "deck.h"
#include <iostream>
#include <string>
#include "player.h"
#include "game.h"
#include "fivecarddraw.h"
using namespace std;

enum FailState {success, uMes, fileNotOpened, emptyCardVector, unknownErr};

int main(int argc, char* argv[])
{	
	if (argc < 3) {
		usageMessage();
		return uMes;
	}
	try {
		Game::start_game(argv[1]);
		for (int i = 2; i < argc; i++) {
			Game::instance()->add_player(argv[i]);
		}
		while (true){
			Game::instance()->before_round();
			Game::instance()->round();
			Game::instance()->after_round();
		}
	}
	catch (errorStates & e) {
		return e;
	}
	
	return 0;
}

