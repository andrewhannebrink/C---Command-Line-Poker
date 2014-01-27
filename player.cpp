//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This file defines the player struct declared in player.h

#include "stdafx.h"
#include "player.h"

Player::Player(char * name)
	:playerName_((string) name), wins_(0), losses_(0), chips_(20), chipsBet_(0), playerHand_(Hand())
{

	//Try to open the file with the player's name and record.
	//I'm assuming that the format for the file is "NAME" (whitespace) "Win int" (white space) "loss int."
	string fileName = playerName_+".txt";
	ifstream ifs;
	ifs.open(fileName);
	std::vector<string> sv; //this will hold the file contents
	if (ifs.is_open())
	{
		unsigned int n = 0;			//n will keep track of how many items have been read from the file (name, wins, losses, chips)
		while(ifs.good())
		{
			string line, word;
			getline(ifs, line);
			
			//Take note of empty lines and keep reading file
			if (line.empty()){
				line = "emptyline";
			}
			//remove spaces from the end of the line to get rid of the last card duplicate problem I've been having.
			while ((line.back()== ' '||line.back()=='	') && line.size()>1) {
				line = line.substr(0, line.size()-1);
			}
			if (line == " "||line=="	"){
				line = "emptyline";
			}

			istringstream iss (line);

			//read from the file as long as there is more left or we have read as many elements as we should
			while( iss.good() && n<=5)
			{
				iss >> word;
				//dont count the emptyline identifier string as an element, start the while loop again, and dont add to n
				if (word!="emptyline") {
					sv.push_back(word);
					n++;
				}
			}
		}
		
		ifs.close();
	}
	
	
	//Now lets go through the string vector "sv" and get the name, wins and losses out of of it.
	if (sv.size()!=4) {
		std::cout << "the file: " <<fileName<<" was not read correctly. It should have a player name, a win number, a loss number, and a chips count, all separated by some white space." << std::endl;
		std::cout << "so, "<<fileName<<"'s file was created automatically and can be found in the current directory" << std::endl;
		wins_=0;
		losses_=0;
		playerName_=name;
	}
	else {

		for (int j=0; j<sv.size(); j++) {
			if (j==0) {
				playerName_=sv[j];
			}
			//case where we read wins or losses
			if (j==1||j==2||j==3) {
				bool good = true;
					for (int i = 0; i < sv[j].size(); i++) {
						if (sv[j].substr(i,1).compare("0")==1 && sv[j].substr(i,1).compare("1")==1 && sv[j].substr(i,1).compare("2")==1 && sv[j].substr(i,1).compare("3")==1 &&
							sv[j].substr(i,1).compare("4")==1 && sv[j].substr(i,1).compare("5")==1 && sv[j].substr(i,1).compare("6")==1 && sv[j].substr(i,1).compare("7")==1 &&
							sv[j].substr(i,1).compare("8")==1 && sv[j].substr(i,1).compare("9")==1)
						{
							good = false;
						}
					}
					if (good==false) {
						std::cout << "could not open player file: " <<fileName<<", invalid win, loss, or chip number" << std::endl;
						break;
					}
					
					//This segment makes the number string into an int
					else {
						
						unsigned int digitSpot=0;
						unsigned int numero = 0; //this will be the number of wins or losses or chips depending on the value of n
						for (int i = sv[j].size()-1; i>=0; i--) {
							if (sv[j].substr(i,1).compare("0")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*0;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("1")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*1;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("2")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*2;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("3")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*3;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("4")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*4;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("5")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*5;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("6")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*6;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("7")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*7;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("8")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*8;
								digitSpot++;
							}
							if (sv[j].substr(i,1).compare("9")==0) {
								numero = numero + pow(10.0,(int)digitSpot)*9;
								digitSpot++;
							}
						}
						if (j==1) {
							wins_=numero;
						}
						if (j==2) {
							losses_=numero;
						}
						if (j==3) {
							chips_=numero;
						}

					}
				}
			}
		}
}

//This prints out a player, their wins, and their losses to a specified ostream
std::ostream & operator<< (std::ostream & os, const Player & player)
{
	os << "Player Name: " <<player.playerName_<<", Wins: "<<player.wins_<<", Losses:"<<player.losses_<<", Chips: "<<player.chips_<<std::endl;
	return os;
}

//This function is for sorting player pointers by their hands' poker ranks
bool player_poker_rank(Player * p1, Player * p2) {
	p1->playerHand_.sortHand();
	p2->playerHand_.sortHand();
	return poker_rank(p1->playerHand_, p2->playerHand_);
}

bool stud_player_poker_rank(Player * p1, Player * p2) {
	p1->playerHand_.sortHand();
	p2->playerHand_.sortHand();
	return poker_rank(p1->bestHand_, p2->bestHand_);
}

bool lowstud_player_poker_rank(Player * p1, Player * p2) {
	p1->playerHand_.sortHand();
	p2->playerHand_.sortHand();
	return poker_rank(p2->bestHand_, p1->bestHand_);
}