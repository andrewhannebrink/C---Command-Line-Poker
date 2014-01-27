//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

#include "stdafx.h"
#include "rwfuncs.h"
#include <iostream>
using namespace std;
using namespace std;
#include <fstream>
#include <sstream>


int readCardFile(vector<Card> & cardVector, char* fileName) throw (string)
{
	ifstream ifs;
	ifs.open(fileName);
	if (ifs.is_open())
	{
		while(ifs.good())
		{
			vector<Card> tempCardVector;   //this vector contains the line's valid card strings
			string line, word;
			getline(ifs, line);
				
				//make sure we continue reading the file if there is an empty line
				if (line.empty()){
					line = "emptyline";
				}

				//only read line before the first occurrence of "//" (if "//" occurs)
				// if line is entirely commented out, do not create an empty line.
				unsigned int commentPos = line.find("//");
				if (commentPos == 0){
					line = line[0];
				}
				else{
					if (commentPos <= line.size()){
						line = line.substr(0, commentPos);
					}
				}

				//remove spaces from the end of the line to get rid of the last card duplicate problem I've been having.
				while (line.back()== ' ' && line.size()>1)
				{
					line = line.substr(0, line.size()-1);
				}
				if (line == " "){
					line = "emptyline";
				}
				

				istringstream iss (line);
				
				while( iss.good())
				{
					iss >> word;
					if (word.length()==0) { throw "emptyStr";}
					string wf = word.substr(0,1);     //first character
					string wl = word.substr(1,1);     //second character
				
					//This if statement finds all valid card strings
					if (((word.size() == 2) && 
						( wf.compare("2")==0||wf.compare("3")==0||wf.compare("4")==0||wf.compare("5")==0||wf.compare("6")==0||wf.compare("7")==0||
						wf.compare("8")==0||wf.compare("9")==0||wf.compare("j")==0||wf.compare("J")==0||wf.compare("q")==0||wf.compare("Q")==0||
						wf.compare("k")==0||wf.compare("K")==0||wf.compare("a")==0||wf.compare("A")==0 ) &&
						( wl.compare("D")==0||wl.compare("H")==0||wl.compare("C")==0||wl.compare("S")==0||wl.compare("d")==0||
						wl.compare("h")==0||wl.compare("c")==0||wl.compare("s")==0 )) 
						||
						//This segment checks for valid strings starting with "10"
						( (word.size() == 3) &&
						(wf.compare("1")==0 && wl.compare("0")==0) &&
						(word.substr(2,1).compare("d")==0 || word.substr(2,1).compare("D")==0 || word.substr(2,1).compare("c")==0||
						word.substr(2,1).compare("C")==0||word.substr(2,1).compare("h")==0||word.substr(2,1).compare("H")==0||
						word.substr(2,1).compare("s")==0||word.substr(2,1).compare("S")==0)  )  )

					{
						if (wf.compare("1")==0) {wl = word.substr(2,1);} //changes wl to 3rd character in the case that the valid string starts with "10"
						//cout << word << endl;
						Rank rank;
						Suit suit;
						if (wf.compare("2")==0) {rank = two;}
						if (wf.compare("3")==0) {rank = three;}
						if (wf.compare("4")==0) {rank = four;}
						if (wf.compare("5")==0) {rank = five;}
						if (wf.compare("6")==0) {rank = six;}
						if (wf.compare("7")==0) {rank = seven;}
						if (wf.compare("8")==0) {rank = eight;}
						if (wf.compare("9")==0) {rank = nine;}
						if (wf.compare("1")==0) {rank = ten;}
						if (wf.compare("j")==0||wf.compare("J")==0) {rank = jack;}
						if (wf.compare("q")==0||wf.compare("Q")==0) {rank = queen;}
						if (wf.compare("k")==0||wf.compare("K")==0) {rank = king;}
						if (wf.compare("a")==0||wf.compare("A")==0) {rank = ace;}
					
						if (wl.compare("c")==0||wl.compare("C")==0) {suit = clubs;}
						if (wl.compare("d")==0||wl.compare("D")==0) {suit = diamonds;}
						if (wl.compare("h")==0||wl.compare("H")==0) {suit = hearts;}
						if (wl.compare("s")==0||wl.compare("S")==0) {suit = spades;}

						Card card = Card(rank, suit);
						cardVector.push_back(card);
					}
					//print out invalid card definitions
					else{
						cout << "Invalid card definition ("<<word<<") in file: " << fileName << endl;
					}	
				}
				// push 5 valid card strings into cardVector if the line contains exactly 5 valid card defintion.
				// Also sort the cards by rank in tempCardVector before doing so. Error messages otherwise
				/*if (tempCardVector.size() == 5){
					Hand tempHand = Hand(tempCardVector);
					tempHand.sortHand();
					for (int i = 0; i<5; i++){
						cardVector.push_back(tempHand.handVector_[i]);
					}
				}
				if (tempCardVector.size() > 5){
					cout << "There were "<<tempCardVector.size()<<" in a line from "<<fileName<<", which is too many for a hand"<<endl;
				}
				if (tempCardVector.size() < 5){
					cout << "There were "<<tempCardVector.size()<<" in a line from "<<fileName<<", which is too few for a hand"<<endl;
				}*/
				
		}
		ifs.close();
		return 0;
	}
	else
	{
		cout << "Could not open file: " << fileName << endl;
		return -1;
	}
}

int displayCards(const vector<Card> & cardVector)
{
	if (cardVector.size() == 0)
	{
		cout << "displayCards function in rwfuncs was passed an empty vector of cards" << endl;
		return -2;
	}
	else
	{
		for (unsigned int i = 0; i<cardVector.size(); ++i)
		{
			Rank rank = cardVector[i].rank_;
			Suit suit = cardVector[i].suit_;
			string str1;
			string str2;

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

			string cardStr = str1 + str2;
			cout << cardStr << endl;
		}
		return 0;
	}
}

void usageMessage()
{
	cout << "To use lab5332, please use two or more arguments: 'lab4332' followed by a game name (FiveCardDraw, SevenCardStud, or Razz) and then one or more player names." << endl;
}
