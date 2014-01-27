//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This header file declares the player struct. Players have a name, hand, win number, loss number, and a constructor that takes a name.

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "hand.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "math.h"
#include <algorithm>
#include "sidepot.h"

struct Player {
	friend std::ostream & operator<< (std::ostream &, const Player &);
	friend bool player_poker_rank(Player *, Player *);
	friend bool stud_player_poker_rank(Player *, Player *);
	friend bool lowstud_player_poker_rank(Player *, Player *);
public:
	std::string playerName_;
	Hand playerHand_;
	unsigned int wins_;
	unsigned int losses_;
	Player(char*);
	unsigned int chips_;
	unsigned int chipsBet_;
	bool inRound_;
	SidePot sidePot_;
	Hand bestHand_;
	
};

#endif