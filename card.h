//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This struct header file defines a card and how to rank individual cards with the < operator.

#ifndef CARD_H
#define CARD_H
#include <string>

enum Suit { clubs, diamonds, hearts, spades };
enum Rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };

class Card
{
public:
	Card();	//Empty constructor
	Card(Rank rank, Suit suit); //Parameterized constructor
	Rank rank_;
	Suit suit_;
	bool operator< (const Card &) const;
	bool operator== (const Card & card) const;
	bool faceDown_;
};

std::string toString(const Card card);

#endif