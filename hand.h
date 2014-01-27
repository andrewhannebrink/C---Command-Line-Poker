//This file also declares a function for printing which rank the hand is.

#ifndef HAND_H
#define HAND_H

#include <vector>
#include <algorithm>
#include "card.h"
#include <string>
#include "deck.h"
using namespace std;

class Deck;

enum HandRank {noRank, onePair, twoPair, threeKind, straight, flus, fullHouse, fourKind, straightF};
enum PairStatus{none, uno, dos, tres, quatro, full}; //uno = one pair, dos = two pair, tres = three ofkind...

class Hand
{
	friend std::ostream & operator<< (std::ostream & hos, const Hand & hand);
	friend void operator<< (Hand & hand, Deck & deck);
	friend HandRank handEval(const Hand & h);
	friend void printHandRanks(const vector<Card> & v);
	friend bool poker_rank(const Hand & hand1, const Hand & hand2);
public:
	Hand();
	Hand(const Hand & hand);
	Hand(vector<Card> & handVector);
	Hand & operator= (const Hand & hand);
	bool operator== (const Hand & hand);
	bool operator< (const Hand &) const;

	HandRank handRank_;
	int size() const;
	void sortHand();
	std::string asString() const;
	std::vector<Card> getHandVector();
	Card & operator[] (size_t);
	void remove_card(size_t);

private:
	vector<Card> handVector_;
	
};


#endif