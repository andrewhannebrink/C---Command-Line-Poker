//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This source file defines the class FiveCardDraw defined in fivecarddraw.h

#include "stdafx.h"
#include "fivecarddraw.h"
#include <sstream>
#include <algorithm>

FiveCardDraw::FiveCardDraw() 
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

//This function asks the user if they want to discard cards and then does it according to their input
int FiveCardDraw::before_turn(Player & player) {
	std::cout << "Name: "<<player.playerName_ << ", Hand: " <<player.playerHand_.asString() << std::endl;
	redo:
	std::cout << "Do you want to discard any cards? (y/n)" << std::endl;
	char a;
	cin >> a;
	while (a!='y' && a!='n') {
		std::cout << "Do you want to discard any cards? Type 'y' for yes and 'n' for no" << std::endl;
		cin >> a;
	} 
	if (a=='n') { 
		std::cout<<"ok, you discarded no cards" <<std::endl;
		return 0;
	}
	if (a=='y') {
		discard:
		std::cout<<"Which card do you want to discard? '1' for first card, '2' for second card, etc. 'f' to finish" <<std::endl;
		char b;
		cin >> b;
		cout<<b<<endl;
		while (b!='1' && b!='2' && b!='3' && b!='4' && b!='5' && b!='f') {
			std::cout << "Which card do you want to discard? '1' for first card, '2' for second card, etc. 'f' to finish" << std::endl;
			cin >> b;
		}
		if (b=='f') {
			std::cout<<"ok, you are done with discarding cards" << std::endl;
			return 0;
		}
		if (b=='1') {
			try {
				if (player.playerHand_.size()>0) {
					discardDeck_.add_card(player.playerHand_[0]);
				}
				player.playerHand_.remove_card(0);
				std::cout<<"Card#"<<b<<" discarded. Your hand is currently this: "<<player.playerHand_.asString() << std::endl<<"Discard more cards? (y/n)" <<std::endl;
				char c;
				cin >> c;
				while (c!='y' && c!='n') {
					std::cout << "Discard more cards? (y/n)" <<std::endl;
					cin >> c;
				} 
				if (c=='n') { 
					std::cout<<"ok, you are done discarding cards" <<std::endl;
					return 0;
				}
				if (c=='y'){ goto discard;}
			}
			catch (int e) {
				std::cout << "You do not have enough cards to remove card#" <<b<<std::endl;
				goto redo;
			}
		}
		if (b=='2') {
			try {
				if (player.playerHand_.size()>1) {
					discardDeck_.add_card(player.playerHand_[1]);
				}
				player.playerHand_.remove_card(1);
				std::cout<<"Card#"<<b<<" discarded. Your hand is currently this: "<<player.playerHand_.asString() << std::endl<<"Discard more cards? (y/n)" <<std::endl;
				char c;
				cin >> c;
				while (c!='y' && c!='n') {
					std::cout << "Discard more cards? (y/n)" <<std::endl;
					cin >> c;
				} 
				if (c=='n') { 
					std::cout<<"ok, you are done discarding cards" <<std::endl;
					return 0;
				}
				if (c=='y'){ goto discard;}
			}
			catch (int e) {
				std::cout << "You do not have enough cards to remove card#" <<b<<std::endl;
				goto redo;
			}
		}
		if (b=='3') {
			try {
				if (player.playerHand_.size()>2) {
					discardDeck_.add_card(player.playerHand_[2]);
				}
				player.playerHand_.remove_card(2);
				std::cout<<"Card#"<<b<<" discarded. Your hand is currently this: "<<player.playerHand_.asString() << std::endl<<"Discard more cards? (y/n)" <<std::endl;
				char c;
				cin >> c;
				while (c!='y' && c!='n') {
					std::cout << "Discard more cards? (y/n)" <<std::endl;
					cin >> c;
				} 
				if (c=='n') { 
					std::cout<<"ok, you are done discarding cards" <<std::endl;
					return 0;
				}
				if (c=='y'){ goto discard;}
			}
			catch (int e) {
				std::cout << "You do not have enough cards to remove card#" <<b<<std::endl;
				goto redo;
			}
		}
		if (b=='4') {
			try {
				if (player.playerHand_.size()>3) {
					discardDeck_.add_card(player.playerHand_[3]);
				}
				player.playerHand_.remove_card(3);
				std::cout<<"Card#"<<b<<" discarded. Your hand is currently this: "<<player.playerHand_.asString() << std::endl<<"Discard more cards? (y/n)" <<std::endl;
				char c;
				cin >> c;
				while (c!='y' && c!='n') {
					std::cout << "Discard more cards? (y/n)" <<std::endl;
					cin >> c;
				} 
				if (c=='n') { 
					std::cout<<"ok, you are done discarding cards" <<std::endl;
					return 0;
				}
				if (c=='y'){ goto discard;}
			}
			catch (int e) {
				std::cout << "You do not have enough cards to remove card#" <<b<<std::endl;
				goto redo;
			}
		}
		if (b=='5') {
			try {
				if (player.playerHand_.size()>4) {
					discardDeck_.add_card(player.playerHand_[4]);
				}
				player.playerHand_.remove_card(4);
				std::cout<<"Card#"<<b<<" discarded. Your hand is currently this: "<<player.playerHand_.asString() << std::endl<<"Discard more cards? (y/n)" <<std::endl;
				char c;
				cin >> c;
				while (c!='y' && c!='n') {
					std::cout << "Discard more cards? (y/n)" <<std::endl;
					cin >> c;
				} 
				if (c=='n') { 
					std::cout<<"ok, you are done discarding cards" <<std::endl;
					return 0;
				}
				if (c=='y'){ goto discard;}
			}
			catch (int e) {
				std::cout << "You do not have enough cards to remove card#" <<b<<std::endl;
				goto redo;
			}
		}
		return 0;
	}
}

//This method gives players as many as cards as they need to have 5 cards.
//It first takes from the deck, and then from the discard deck
int FiveCardDraw::turn(Player & p) {
	unsigned int n = 5 - p.playerHand_.size();
	if (deck_.size()>0) {
		while (deck_.size()!=0 && p.playerHand_.size() < 5) {
			if (n>0) {
				for (int i = 0; i < n; i++) {
					p.playerHand_ << (p.playerHand_, deck_);
				}
			}
		}
		return 0;
	}
	unsigned int k = 5 - p.playerHand_.size();
	if (discardDeck_.size()!=0) {
		discardDeck_.shuffle();
		while (discardDeck_.size()!=0 && p.playerHand_.size() < 5) {
			if (k>0) {
				for (int i = 0; i < n; i++) {
					p.playerHand_ << (p.playerHand_, deck_);
				}
			}
		}
		return 0;
	}
	else {
		return -1;
	}
}

//This shows the players name and their hand after the turn
int FiveCardDraw::after_turn(Player & p) {
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
int FiveCardDraw::before_round() {
	pot_ = 0;
	currentBet_ = 0;
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
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < playerpVector_.size(); j++) {
			playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_ << (playerpVector_[(dealtPos+j)%playerpVector_.size()]->playerHand_, deck_);
		}
	}
	//First betting phase
	while (true) {
		for (int i = 0; i < playerpVector_.size(); i++) {
			if ((playerpVector_[(dealtPos+i)%playerpVector_.size()]->inRound_ == true) && (playerpVector_[(dealtPos+i)%playerpVector_.size()]->sidePot_.in_ == false)) {
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
	//Card drawing phase
	for (int k = 0; k < playerpVector_.size(); k++) {
		if ((playerpVector_[(dealtPos+k)%playerpVector_.size()]->inRound_ == true)) {
			before_turn(*playerpVector_[(dealtPos+k)%playerpVector_.size()]);
		}
	}
	//Next betting phase
	std::cout << "Second betting phase beginning." << std::endl;
	currentBet_ = 0;
	for (int i = 0; i < playerpVector_.size(); i++) {
		playerpVector_[i]->chipsBet_ = 0;
	}
	while (true) {
		for (int i = 0; i < playerpVector_.size(); i++) {
			if ((playerpVector_[(dealtPos+i)%playerpVector_.size()]->inRound_ == true) && (playerpVector_[(dealtPos+i)%playerpVector_.size()]->sidePot_.in_ == false)){
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
	std::cout << "The second betting phase is now over." << std::endl;

	return 0;
}

//This function calls each players turn function starting with the player after the dealer
//If any of the functions returns a non-zero value, so does this function and it stops
int FiveCardDraw::round() {
	unsigned int dealtPos = (dealerPos_+1) % playerpVector_.size();
	for (int k = 0; k < playerpVector_.size(); k++) {
		int f = turn(*playerpVector_[(dealtPos+k)%playerpVector_.size()]);
		int u = after_turn(*playerpVector_[(dealtPos+k)%playerpVector_.size()]);
		if (f!=0) {
			return f;
		}
	}
	return 0;
}

//This function sees who won the round, adds wins and losses to the players,
//Moves cards from the players hands and discard deck back into the main deck,
//Removes players from the game if they want to quit,
//and adds players to the game that want to join, and then changes the dealer.

int FiveCardDraw::after_round() {
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
	sort(pvIn.begin(), pvIn.end(), player_poker_rank);
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
		std::cout<<"Hand: "<<pvIn[i]->playerHand_.asString()<<", ";
		HandRank hr = handEval(pvIn[i]->playerHand_);
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
	for (int i = 0; i < 5; i++) {
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
	