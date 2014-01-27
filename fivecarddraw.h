//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This header file declares the FiveCardDraw class, which is an inherited class from Game

#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H
#include "game.h"

class FiveCardDraw : public Game {
public:
	FiveCardDraw();
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
