//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This header file defines a deck, and contains the constructor and a load method.
//It also has a reseed and shuffle method that work together to shuffle the deck based
//on pseudo random numbers.

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include "card.h"
#include "hand.h"
#include "rwfuncs.h"
#include <iostream>


class Deck {
	friend std::ostream & operator<< (std::ostream & os, const Deck & deck);
public:
	Deck(char * fileName);
	Deck();
	void add_card(const Card &);
	void load(char * fileName);
	void shuffle();
	void reseed();
	std::vector<Card> getDeckVector() const;
	int size() const;
	void dealFirstCard();
	void refresh();
private:
	std::vector<Card> deckVector_;
};

#endif