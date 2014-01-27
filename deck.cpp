//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This source file defines the methods and constructors from the deck.h header file

#include "stdafx.h"
#include "deck.h"
#include <ctime>

Deck::Deck(char * fileName) 
	: deckVector_()
{
	reseed();
	try {
		this->load(fileName);
	}
	catch (int & a) {
		std::cout << "Error opening file: " << fileName << std::endl;
		std::cout << "readCardFile returned: " << a << std::endl;
	}
	catch (...) {
		//hukairs
		std::cout << "Unknown error opening file: " << fileName << std::endl;
	}
}

Deck::Deck()
	: deckVector_() {}

void Deck::add_card(const Card & c) {
	deckVector_.push_back(c);
}

void Deck::load(char * fileName) throw (int)
{
	int e = readCardFile(deckVector_ , fileName);
	if (e != 0) {
		throw e;
	}
}

//I use this getter method mostly for debugging purposes.
std::vector<Card> Deck::getDeckVector() const
{
	return deckVector_;
}

//resets pseudo-random number generation based on the current time
void Deck::reseed()
{
	srand(std::time(0));
}

//This method makes a random integer between 1 and 420, and then uses the random_shuffle algorithm
//to shuffle the deck that many times.
void Deck::shuffle()
{
	int r = (rand() % 420) + 1;
	for (int i = 0; i < r; i++)
	{
		random_shuffle (deckVector_.begin(), deckVector_.end());
	}
}

//This returns how many cards are in the deck
int Deck::size() const
{
	return deckVector_.size();
}

// This sends each card defintion of each card in the deck to the specified ostream, and returns the ostream
std::ostream & operator<< (std::ostream & os, const Deck & deck)
{
	for (int i = 0; i < deck.size(); i++)
	{
		os << toString(deck.deckVector_[i]) << std::endl;
	}
	return os;
}

//This method erases an element from the beginning of the deck,
//in preparation to be dealed to a hand
void Deck::dealFirstCard() 
{
	(deckVector_).erase(deckVector_.begin());
}

//This makes all the cards in the deck "face up" for seven card stud.
void Deck::refresh() {
	for (int i = 0; i < deckVector_.size(); i++) {
		deckVector_[i].faceDown_ = false;
	}
}