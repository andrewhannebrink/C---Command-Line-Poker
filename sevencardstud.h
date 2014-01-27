//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This header file declares the SevenCardStud class, which is an inherited class from Game

#ifndef SEVENCARDSTUD_H
#define SEVENCARDSTUD_H
#include "game.h"

class SevenCardStud : public Game {
public:
	SevenCardStud();
	virtual int before_turn(Player &) ;
	virtual int turn(Player &) ;
	virtual int after_turn(Player &) ;
	virtual int before_round() ;
	virtual int round() ;
	virtual int after_round() ;
protected:
	size_t dealerPos_;
	Deck discardDeck_;

};

#endif