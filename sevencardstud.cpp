//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This source file defines the class SevenCardStud defined in sevencardstud.h

#include "stdafx.h"
#include "sevencardstud.h"
#include <sstream>
#include <algorithm>

SevenCardStud::SevenCardStud() 
	: dealerPos_(0), discardDeck_()
{
	for (int s = 0; s < 4; s++) {
		for (int r = 0; r < 13; r++) {
			Suit suit = (Suit) s;
			Rank rank = (Rank) r;
			Card c (rank, suit);
			deck_.add_card(c);
		}
	}
}


//This shows the players name and their hand after the turn
int SevenCardStud::after_turn(Player & p) {
	try {
		if (p.inRound_==true) {
			std::cout<<"Name: "<<p.playerName_<<", Hand: "<<p.playerHand_.asString()<<", Chips: " << p.chips_ << std::endl;
		}
		else {
			std::cout<<"Name: "<<p.playerName_<<", Hand: FOLDED, Chips: " << p.chips_ << std::endl;
		}
		return 0;
	}
	catch (...) {
		//hukairs
		return -1;
	}
}

//This method takes a chips from everone and adds it to the pot, and deals five cards to each player before the round, and then calls
//each one of their before_turn methods. It also deals with the betting phases
int SevenCardStud::before_round() {
	pot_ = 0;
	currentBet_ = 0;
	deck_.refresh();
	for (int i = 0; i < playerpVector_.size(); i++) {
		playerpVector_[i]->chips_ = playerpVector_[i]->chips_ - 1;
		pot_++;
		playerpVector_[i]->inRound_ = true;
		playerpVector_[i]->sidePot_.in_ = false;
		playerpVector_[i]->sidePot_.sidePotChips_ = 0;
		playerpVector_[i]->chipsBet_ = 0;
	}
	std::cout << "New round! Each player put a chip in the pot." << std::endl;
	std::cout << "The pot currently has "  << pot_ << " chips." << std::endl;
	deck_.shuffle();
	unsigned int dealtPos = (dealerPos_+1) % playerpVector_.size();
	//First flop. Two face up and one face down
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < playerpVector_.size(); j++) {
			playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_ << (playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_, deck_);
			if (i==2) {
				playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_[i].faceDown_ = true;
			}
		}
	}
	//First betting phase
	while (true) {
		for (int i = 0; i < playerpVector_.size(); i++) {
			if ((playerpVector_[(dealtPos+i)%playerpVector_.size()]->inRound_ == true) && (playerpVector_[(dealtPos+i)%playerpVector_.size()]->sidePot_.in_ == false)) {
				betweenTurnDisplay(*playerpVector_[(dealtPos+i)%playerpVector_.size()]);
				betting_phase(*playerpVector_[(dealtPos+i)%playerpVector_.size()]);
			}
			else {
				continue;
			}
		}
		bool done = true;
		for (int i = 0; i < playerpVector_.size(); i++) {
			if ((playerpVector_[(dealtPos+i)%playerpVector_.size()]->inRound_ == true) && (playerpVector_[(dealtPos+i)%playerpVector_.size()]->chipsBet_ != currentBet_) && (playerpVector_[(dealtPos+i)%playerpVector_.size()]->sidePot_.in_ == false)) {
				done = false;
			}
		}
		if (done == true) {
			break;
		}
	}
	std::cout << "The first betting phase is now over." << std::endl;
	//Second Flop. one card face up
	for (int j = 0; j < playerpVector_.size(); j++) {
			playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_ << (playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_, deck_);
	}
	//Next betting phase
	std::cout << "Second betting phase beginning." << std::endl;
	new_betting_phase(dealtPos);
	std::cout << "The second betting phase is now over." << std::endl;

	//Third Flop. one card face up
	for (int j = 0; j < playerpVector_.size(); j++) {
			playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_ << (playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_, deck_);
	}
	//Next betting phase
	std::cout << "Third betting phase beginning." << std::endl;
	new_betting_phase(dealtPos);
	std::cout << "The third betting phase is now over." << std::endl;
	//Fourth Flop. one card face up
	for (int j = 0; j < playerpVector_.size(); j++) {
			playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_ << (playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_, deck_);
	}
	//Next betting phase
	std::cout << "Fourth betting phase beginning." << std::endl;
	new_betting_phase(dealtPos);
	std::cout << "The fourth betting phase is now over." << std::endl;
	//Fifth and final Flop. one card face up
	for (int j = 0; j < playerpVector_.size(); j++) {
		playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_ << (playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_, deck_);
		playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_[6].faceDown_ = true;
	}
	//Next betting phase
	std::cout << "Fifth betting phase beginning." << std::endl;
	new_betting_phase(dealtPos);
	std::cout << "The fifth betting phase is now over." << std::endl;
	return 0;
}

//This function calls each players turn function starting with the player after the dealer
//If any of the functions returns a non-zero value, so does this function and it stops
int SevenCardStud::round() {
	unsigned int dealtPos = (dealerPos_+1) % playerpVector_.size();
	for (int k = 0; k < playerpVector_.size(); k++) {
		int u = after_turn(*playerpVector_[(dealtPos+k)%playerpVector_.size()]);
	}
	return 0;
}

//This function sees who won the round, adds wins and losses to the players,
//Moves cards from the players hands and discard deck back into the main deck,
//Removes players from the game if they want to quit,
//and adds players to the game that want to join, and then changes the dealer.

int SevenCardStud::after_round() {
	std::cout << "End of round!" << std::endl;
	vector<Player *> pvIn;
	vector<Player *> pvFold;
	for (int i = 0; i < playerpVector_.size(); i++) {
		if (playerpVector_[i]->inRound_ ==true) {
			pvIn.push_back(playerpVector_[i]);
		}
		else {
			pvFold.push_back(playerpVector_[i]);
		}
	}
	//Get the best hand for each player
	for (int i = 0; i < pvIn.size(); i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = (j+1); k < 7; k++) {
				std::vector<Card> tempCardVector;
				if (j==0 && k==1) {
					std::vector<Card> hv (5);
					std::vector<Card> itrVec = pvIn[i]->playerHand_.getHandVector();
					std::copy(itrVec.begin()+2, itrVec.end(), hv.begin());
					Hand woo (hv);
					woo.sortHand();
					pvIn[i]->bestHand_ = woo;
				}
				for (int q = 0; q < 7; q++) {
					if (q==j || q==k) {
						continue;
					}
					else {
						tempCardVector.push_back(pvIn[i]->playerHand_.getHandVector()[q]);
					}
				}
				Hand tempHand (tempCardVector);
				tempHand.sortHand();
				if (poker_rank(tempHand, pvIn[i]->bestHand_)) {
					pvIn[i]->bestHand_ = tempHand;
				}
			}
		}
	}
	sort(pvIn.begin(), pvIn.end(), stud_player_poker_rank);
	pvIn[0]->wins_++;
	if (pvIn[0]->sidePot_.in_ == true) {
		pvIn[0]->chips_ = pvIn[0]->chips_ + pvIn[0]->sidePot_.sidePotChips_;
		std::cout << pvIn[0]->playerName_ << " won " << pvIn[0]->sidePot_.sidePotChips_ << " chips from their sidepot."<<std::endl;
		int i = 1;
		//Award chips to the next best player who doesnt have a sidepot, if they have a sidepot, give them the differences in sidepots,
		//then give the rest of the chips to the next best player, and so on.
		int j = 0;
		while (i < pvIn.size()) {
			if (pvIn[i]->sidePot_.in_ == true) {
				if ((pvIn[i]->sidePot_.sidePotChips_ - pvIn[j]->sidePot_.sidePotChips_) > 0) {
					pvIn[i]->chips_ = pvIn[i]->chips_ + (pvIn[i]->sidePot_.sidePotChips_ - pvIn[j]->sidePot_.sidePotChips_);
					j = i;
					std::cout << pvIn[i]->playerName_ << " won " << (pvIn[i]->sidePot_.sidePotChips_ - pvIn[j]->sidePot_.sidePotChips_) << " chips from their remaining sidepot."<<std::endl;
				}
				i++;
			}
			else {
				if (pot_ - pvIn[j]->sidePot_.sidePotChips_>0){
					pvIn[i]->chips_ = pvIn[i]->chips_ + (pot_ - pvIn[j]->sidePot_.sidePotChips_);
					std::cout << pvIn[i]->playerName_ << " won the remaining " << (pot_ - pvIn[j]->sidePot_.sidePotChips_) << " from the pot." <<std::endl;
				}
				break;
			}
		}
		std::cout << "" << std::endl;
	}
	else {
		pvIn[0]->chips_ = pvIn[0]->chips_ + pot_;
		std::cout << pvIn[0]->playerName_ << " won " << pot_ << " chips."<<std::endl;
	}
	pot_ = 0;
	for (int i=1; i < pvIn.size(); i++) {
		pvIn[i]->losses_++;
	}
	for (int i = 0; i < pvFold.size(); i++) {
		pvFold[i]->losses_++;
	}
	std::cout << "The players ranked in this order this round:"<<std::endl;
	for (int i = 0; i <pvIn.size(); i++) {
		std::cout<<"Name: "<<pvIn[i]->playerName_<<", Wins: "<<pvIn[i]->wins_<<", Losses: "<<pvIn[i]->losses_<<", Chips: "<<pvIn[i]->chips_<<std::endl;
		std::cout<<"Hand: "<<pvIn[i]->playerHand_.asString()<< std::endl;
		std::cout<<pvIn[i]->playerName_<<"'s best hand was: "<<pvIn[i]->bestHand_.asString()<<", ";
		HandRank hr = handEval(pvIn[i]->bestHand_);
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
	for (int i = 0; i < pvFold.size(); i++) {
		std::cout<<"Name: "<<pvFold[i]->playerName_<<", Wins: "<<pvFold[i]->wins_<<", Losses: "<<pvFold[i]->losses_<<", Chips: "<<pvFold[i]->chips_<<std::endl;
		std::cout<<"Hand: "<< "FOLDED." << std::endl;
	}
	//Now lets move all the cards back into the main deck
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < playerpVector_.size(); j++){
			deck_.add_card(playerpVector_[j]->playerHand_[0]);
			playerpVector_[j]->playerHand_.remove_card(0);
		}
	}
	for (int i =0; i < discardDeck_.size(); i++) {
		deck_.add_card(discardDeck_.getDeckVector()[i]);
		discardDeck_.dealFirstCard();
	}

	//Deal with the players that have zero chips - see if they want more chips, or want to quit.
	for (int i = 0; i < playerpVector_.size(); i++) {
		if (playerpVector_[i]->chips_ == 0) {
			std::cout << std::endl;
			std::cout << playerpVector_[i]->playerName_ <<", you have no chips left. Do you want 20 more chips? If not, you will be removed from the game. (y/n)" << std::endl;
			char a;
			cin >> a;
			while (a!='y' && a!='n') {
				std::cout << playerpVector_[i]->playerName_ << ", you have no chips left. Do you want 20 more chips? If not, you will be removed from the game. (y/n)" << std::endl;
				cin >> a;
			}
			if (a=='y') {
				playerpVector_[i]->chips_ = 20;
				std::cout << "Ok, " << playerpVector_[i]->playerName_ << ", you were given 20 more chips." << std::endl;
			}
			if (a=='n') {
				std::cout <<playerpVector_[i]->playerName_<<" was removed from the game"<<std::endl;
				std::ofstream ofs (playerpVector_[i]->playerName_+".txt");
				ofs << playerpVector_[i]->playerName_ <<" "<<playerpVector_[i]->wins_<<" "<<playerpVector_[i]->losses_<<" "<<playerpVector_[i]->chips_<<std::endl;
				ofs.close();
				delete playerpVector_[i];
				playerpVector_.erase(playerpVector_.begin()+i); //erase destroys the element removed, so its a safe way to call delete
				if (playerpVector_.size()==0) {
					std::cout<<"There are no players left. Game Over."<<std::endl;
					throw game_success;
				}
			}
		}
	}


	//See if any players want to leave the game, if so, remove them from the vector and write a file with their name, wins, and losses
	string line;
	while (true) {
        getline(cin, line);
        if (line=="n") {
            break;
        }
		for (int i = 0; i <playerpVector_.size();i++){
			if (line==playerpVector_[i]->playerName_) {
				string tempName = playerpVector_[i]->playerName_;
				std::ofstream ofs (tempName+".txt");
				ofs << tempName <<" "<<playerpVector_[i]->wins_<<" "<<playerpVector_[i]->losses_<<" "<<playerpVector_[i]->chips_<<std::endl;
				ofs.close();
				delete playerpVector_[i];
				playerpVector_.erase(playerpVector_.begin()+i); //erase destroys the element removed, so its a safe way to call delete
				std::cout <<tempName<<" was removed from the game"<<std::endl;
				if (playerpVector_.size()==0) {
					std::cout<<"There are no players left. Game Over."<<std::endl;
					throw game_success;
				}
			}
		}
		std::cout<<"Do any players want to exit the game? If so, enter their name. If not, enter 'n'";
    }
	string line2;
	while (true) {
		add:
		std::cout<<"Do any players want to join the game? If so, enter their name. If not, enter 'n'";
        getline(cin, line2);
        if (line2=="n") {
            break;
        }
		else {
			if (line2!=""){
				Game::add_player(line2);
				std::cout<<line2<<" was added to the game."<<std::endl;
				goto add;
			}
			else {
				goto add;
			}
		}
	}
	dealerPos_= (dealerPos_++) % playerpVector_.size();
	return 0;
}

//These dont get used but I need to define them for the project to compile
int SevenCardStud::before_turn(Player &) {
	return 0;
}
	
int SevenCardStud::turn(Player &) {
	return 0;
}