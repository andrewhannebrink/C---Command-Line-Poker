//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This header file has functions for reading card text documents, printing valid hands to the screen, and telling the user how to use the program.

#include <string>
using namespace std;
#include <vector>
#include "hand.h"

int readCardFile(vector<Card> & cardVector, char* fileName);

int displayCards( const vector<Card> & cardVector);

void usageMessage();
