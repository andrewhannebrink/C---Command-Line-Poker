//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This file defines a card as declared by card.h
#include "stdafx.h"
#include "card.h"



Card::Card()
	: rank_(), suit_(), faceDown_(false) {}

Card::Card(Rank rank, Suit suit)
	: rank_(rank), suit_(suit), faceDown_(false) {}

bool
Card::operator< (const Card & card2) const
{
	return ((rank_ < card2.rank_) || (rank_==card2.rank_ && suit_<card2.suit_));
}

bool Card::operator== (const Card & card) const
{
	if (card.rank_ == this->rank_ && card.suit_ == this->suit_) {
		return true;
	}
	else {
		return false;
	}
}

//This turns a card into a card definition string. This method is used by the << operator declared in the deck.h header file.
std::string toString(const Card card)
{
	Rank rank = card.rank_;
	Suit suit = card.suit_;
	std::string str1;
	std::string str2;

	if (rank == two) {str1 = "2";}
	if (rank == three) {str1 = "3";}
	if (rank == four) {str1 = "4";}
	if (rank == five) {str1 = "5";}
	if (rank == six) {str1 = "6";}
	if (rank == seven) {str1 = "7";}
	if (rank == eight) {str1 = "8";}
	if (rank == nine) {str1 = "9";}
	if (rank == ten) {str1 = "10";}
	if (rank == jack) {str1 = "j";}
	if (rank == queen) {str1 = "q";}
	if (rank == king) {str1 = "k";}
	if (rank == ace) {str1 = "a";}

	if (suit == clubs) {str2 = "C";}
	if (suit == diamonds) {str2 = "D";}
	if (suit == hearts) {str2 = "H";}
	if (suit == spades) {str2 = "S";}

	std::string cardStr = str1 + str2;
	return cardStr;
}