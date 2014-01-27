

//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu



#include "stdafx.h"
#include "hand.h"
#include <iostream>

//Default constructor
Hand::Hand()
	: handVector_(), handRank_() {}

//Copy constructor
Hand::Hand(const Hand & hand)
	: handVector_(hand.handVector_), handRank_(hand.handRank_){
		this->sortHand();
}

//Constructor that uses a vector of cards.
Hand::Hand(vector<Card> & handVector)
	: handVector_(handVector), handRank_() {this->sortHand();}

//Assignment operator checks for self assignment first, and then sets the hands member variables equal to the other hand's member variables.
Hand & Hand::operator= (const Hand & hand)
{
	if (this != &hand){
		handVector_ = hand.handVector_;
		handRank_ = hand.handRank_;
		return *this;
	}
	else{
		return *this;
	}
}

//This [] operator returns the card at handVector_[i], and throws -1 if i is out of bounds
Card & Hand::operator[] (size_t i)
{
	if (i>=0 && i<handVector_.size()) {
		return handVector_[i];
	}
	else {
		std::cout << "Hand[] was passed an out of bounds index" << std::endl;
		throw -1;
	}
}

//This erases the card at handVector_[i], and throws -1 if i is out of bounds
void Hand::remove_card(size_t i) {
	if (i>=0 && i<handVector_.size()) {
		handVector_.erase(handVector_.begin()+i);
	}
	else {
		//std::cout << "Hand::remove_card(size_ t) was passed an out of bounds index" << std::endl;
		throw -1;
	}
}

//Equivalence operator returns true iff exactly the same sequence of cards appear in both hands
bool Hand::operator== (const Hand & hand)
{
	bool tf = true;
	if (hand.size() != this->size()) {
		return false;
	}
	else {
		this->sortHand();
		int i = 0;
		while (tf==true && i < hand.size()) {
			if (this->handVector_[i] == hand.handVector_[i]){
				i++;
			}
			else {
				tf = false;
			}
		}
	}
	return tf;
}

//This method uses the first card from the hand to determine whether the hand is less than (lexicagraphically than the other hand.
//This works because hands are automatically sorted by cards when they are constructed.
bool Hand::operator< (const Hand & hand2) const
{
	if (this->size()==0 || hand2.size()==0) {
		std::cout << "Error, Hand's < operator was used with an empty hand type" << std::endl;
		return false;
	}
	else {
		return (handVector_[0] < hand2.handVector_[0]);
	}
}

//This insertion operator sends the hand as card definition strings to the specified output stream, and returns a reference to an output stream
std::ostream & operator<< (std::ostream & hos, const Hand & hand) 
{

	hos << hand.asString() << std::endl;
	return hos;
}

//This insertion operator removes the first card from the deck,
//inserts it into the hand, and then sorts the hand
void operator<< (Hand & hand, Deck & deck)
{
	Card card = deck.getDeckVector()[0];
	deck.dealFirstCard();
	hand.handVector_.push_back(card);
	//hand.sortHand();
}


//Returns the size of the hand
int Hand::size() const
{
	return handVector_.size();
}

//This returns a string of card definitions separated by spaces for each card in the hand. It uses Card's toString() method to do this
std::string Hand::asString() const
{
	std::string str = "";
	for (int i = 0; i < this->size(); i++)
	{
		str += toString(this->handVector_[i]) + " ";
	}
	return str;
}

//This sorts the hand, which is necessary for finding the hand's rank.
void Hand::sortHand()
{
	sort(handVector_.begin(), handVector_.end());
}

//This method returns true iff hand1 ranks higher in poker than hand2
bool poker_rank(const Hand & hand1, const Hand & hand2)
{
	if (hand1.size()!=5 || hand2.size()!=5) {
		std::cout << "Error: hands not of size 5 do not have a rank" << std::endl;
		throw -1;
	}
	HandRank hr1 = handEval(hand1);
	HandRank hr2 = handEval(hand2);
	if (hr1 != hr2) {
		return (hr1>hr2);
	}
	//High card wins with these four hand ranks:
	if (hr1==noRank || hr1==straightF || hr1==straight || hr1==flus) {
		return (hand2.handVector_.back() < hand1.handVector_.back());
	}

	if (hr1==onePair) {
		int i = 0;
		while (!(hand1.handVector_[i].rank_ == hand1.handVector_[i+1].rank_)) {
			i++;
		}
		Card pCard1 = hand1.handVector_[i+1];
		int j = 0;
		while (!(hand2.handVector_[j].rank_ == hand2.handVector_[j+1].rank_)) {
			j++;
		}
		Card pCard2 = hand2.handVector_[j+1];
		return (pCard2 < pCard1);
	}

	if (hr1 == fourKind) {
		int i = 0;
		while (!(hand1.handVector_[i].rank_ == hand1.handVector_[i+1].rank_)) {
			i++;
		}
		Card pCard1 = hand1.handVector_[i+3];
		int j = 0;
		while (!(hand2.handVector_[j].rank_ == hand2.handVector_[j+1].rank_)) {
			j++;
		}
		Card pCard2 = hand2.handVector_[j+3];
		return (pCard2 < pCard1);
	}

	if (hr1 == twoPair) {
		int i = hand1.size()-1;
		while (!(hand1.handVector_[i].rank_ == hand1.handVector_[i-1].rank_)) {
			i--;
		}
		Card pCard1 = hand1.handVector_[i];
		int j = hand2.size()-1;
		while (!(hand2.handVector_[j].rank_ == hand2.handVector_[j-1].rank_)) {
			j--;
		}
		Card pCard2 = hand2.handVector_[j];
		return (pCard2 < pCard1);
	}

	if (hr1==fullHouse || hr1==threeKind) {
		int i = 0;
		while (!(hand1.handVector_[i].rank_ == hand2.handVector_[i+2].rank_)) {
			i++;
		}
		Card pCard1 = hand1.handVector_[i+2];
		int j = 0;
		while (!(hand2.handVector_[j].rank_ == hand2.handVector_[j+2].rank_)) {
			j++;
		}
		Card pCard2 = hand2.handVector_[j+2];
		return (pCard2 < pCard1);
	}
	else {
		return false;
	}
}

//This is a getter method for handVector_
std::vector<Card> Hand::getHandVector()
{
	return handVector_;
}

//This method evaluates the hand's rank
HandRank handEval(const Hand & h)
{
	bool flushStatus=false;
	bool straightStatus=false;
	PairStatus pairStatus=none;

	
	
	//check if were dealing with a straight or a flush
	if (h.handVector_[0].suit_==h.handVector_[1].suit_  &&  h.handVector_[0].suit_==h.handVector_[2].suit_  &&  h.handVector_[0].suit_==h.handVector_[3].suit_  &&  
		h.handVector_[0].suit_==h.handVector_[4].suit_)
	{
		flushStatus=true;
	}
	if (h.handVector_[0].rank_==h.handVector_[1].rank_-1  &&  h.handVector_[1].rank_==h.handVector_[2].rank_-1  &&  h.handVector_[2].rank_==h.handVector_[3].rank_-1 &&
		h.handVector_[3].rank_==h.handVector_[4].rank_-1)
	{
		straightStatus=true;
	}

	//if were not dealing with a straight or a flush, lets check if there are some pairs of cards
	if (flushStatus==false && straightStatus==false)
	{
		//The following code will return a vector p whos ith value returns the number of duplicate ranks of that card in the ith position of of the
		//sorted hand, given that position i is the first occurrence of that rank. Then p gets sorted, so if p[4] = 4, its a 4 of a kind,
		//if p[4]=3 and p[3]=1, its a three of a kind, if p[4]=3 and p[3]=2, its a fullhouse, etc...
		vector<int> p(5);
		for (int i=0;i<5;i++){p[i]=1;}
		int i = 0;
		int j = 1;
		while (j<5)
		{
			if (h.handVector_[i].rank_==h.handVector_[j].rank_){			
				p[i]++;
				j++;
			}
			else{
				i=j;
				j++;
			}
		}
		sort(p.begin(),p.end());

		if (p[4]==4){
			pairStatus=quatro;
		}
		if (p[4]==3 && p[3]==2){
			pairStatus=full;
		}
		if (p[4]==3 && p[3]==1){
			pairStatus =tres;
		}
		if (p[4]==2 && p[3]==2){
			pairStatus=dos;
		}
		if (p[4]==2 && p[3]==1){
			pairStatus=uno;
		}
		if (p[4]==1){
			pairStatus=none;
		}
	}

	if (straightStatus==true && flushStatus==true){
		return straightF;
	}
	if (straightStatus==true && flushStatus==false){
		return straight;
	}
	if (straightStatus==false && flushStatus==true){
		return flus;
	}
	if (pairStatus==uno){
		return onePair;
	}
	if (pairStatus==dos){
		return twoPair;
	}
	if (pairStatus==tres){
		return threeKind;
	}
	if (pairStatus==full){
		return fullHouse;
	}
	if (pairStatus==quatro){
		return fourKind;
	}
	else {
		return noRank;
	}
}

void printHandRanks(const vector<Card> & v)
{
	int n = v.size()/5;
	for (int i = 0; i<n; i++)
	{
		vector<Card> c(5);
		copy(v.begin()+(i*5),v.begin()+(i*5+5), c.begin());
		Hand tempHand = Hand(c);
		HandRank hr = handEval(tempHand);
		if (hr==noRank){cout<<"Hand has no rank."<<endl;}
		if (hr==twoPair){cout<<"Hand is a two pair."<<endl;}
		if (hr==onePair){cout<<"Hand is a single pair."<<endl;}
		if (hr==threeKind){cout<<"Hand is a three of a kind."<<endl;}
		if (hr==fullHouse){cout<<"Hand is a full house."<<endl;}
		if (hr==fourKind){cout<<"Hand is a four of a kind."<<endl;}
		if (hr==straight){cout<<"Hand is a straight."<<endl;}
		if (hr==straightF){cout<<"Hand is a straight flush."<<endl;}
		if (hr==flus){cout<<"Hand is a flush."<<endl;}
	}
}