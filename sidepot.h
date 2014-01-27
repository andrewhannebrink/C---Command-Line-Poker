//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This declares a class consisting of a boolean and a sidepot size int.
//Each player will have a member variable of this class type, indicating whether
//they are in the sidepot, and what size their potential sidepot winnings are.

#ifndef SIDEPOT_H
#define SIDEPOT_H

class SidePot {
public:
	bool in_;
	unsigned int sidePotChips_;
	SidePot();
};

#endif