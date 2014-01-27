//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This source file defines the functions and constructors declared in the game.h header file
#include "stdafx.h"
#include "game.h"
#include "fivecarddraw.h"
#include "sevencardstud.h"
#include "razz.h"

Game * Game::gamep_=0;

//This default destructor initializes the deck to be empty
Game::Game()
	: deck_() {}


//This destructor iterates through gamep_ and deletes each pointer
Game::~Game() {
	for (int i = 0; i < playerpVector_.size(); i++){
		delete playerpVector_[i];
	}
}

//This returns a copy of what Game's member variable Game * gamep_ is pointing to
Game *Game::instance() {
	if (gamep_==0) {
		std::cout<<"Error with Game::instance(): instance not available exception."<<std::endl;
		throw instance_not_available;
	}
	else{
		Game* game = gamep_;
		return game;
	}
}

//This starts a new game
void Game::start_game(const string s) {
	if (gamep_!=0) {
		std::cout<<"Error with Game::start_game(): game already started excception." <<std::endl;
		throw game_already_started;
	}
	if (s.compare("FiveCardDraw")==1 && s.compare("SevenCardStud")==1 && s.compare("Razz")==1) {
		std::cout<<"Error with Game::start_game(): unknown game exception"<<std::endl;
		throw unknown_game;
	}

	if (s.compare("FiveCardDraw")==0) {
		FiveCardDraw  * fcd = new FiveCardDraw();
		gamep_ = fcd;
		std::cout << "Started a game of five card draw." << std::endl;
	}
	if (s.compare("SevenCardStud")==0) {
		SevenCardStud  * scs = new SevenCardStud();
		gamep_ = scs;
		std::cout << "Started a game of seven card stud." << std::endl;
	}
	if (s.compare("Razz")==0) {
		Razz * razz = new Razz();
		gamep_ = razz;
		std::cout << "Started a game of razz (seven card stud low)." << std::endl;
	}
}

//This function stops the game that is in progress
void Game::stop_game() {
	if (gamep_==0) {
		std::cout<<"Error with Game::stop_game(): no game in progress exception." << std::endl;
		throw no_game_in_progress;
	}
	else {
		delete gamep_;
		gamep_ = 0;
	}
}

//This adds a player to the game
void Game::add_player(const string name) {
	for (int i = 0; i < playerpVector_.size(); i++) 
	{
		if (playerpVector_[i]->playerName_.compare(name)==0) {
			std::cout << "Error in Game::add_player: "<<name<<" is already playing." <<std::endl;
			throw already_playing;
		}
	}
	Player * p = new Player ((char *) name.c_str());
	if (p->chips_ == 0) {
			std::cout << std::endl;
			std::cout << p->playerName_ <<", you have no chips. Do you want 20 more chips? If not, you will not be added to the game. (y/n)" << std::endl;
			char a;
			cin >> a;
			while (a!='y' && a!='n') {
				std::cout << p->playerName_ << ", you have no chips. Do you want 20 more chips? If not, you will be removed from the game. (y/n)" << std::endl;
				cin >> a;
			}
			if (a=='y') {
				p->chips_ = 20;
				playerpVector_.push_back(p);
				std::cout << "Ok, " <<p->playerName_ << ", you were given 20 more chips, and added to the game." << std::endl;
			}
			if (a=='n') {
				std::cout << "Ok, "<<p->playerName_ << ", you were not added to the game." << std::endl;
			}
	}
	else {
		playerpVector_.push_back(p);
	}
}

//This returns a pointer to a player if the player is in the game, but otherwise returns 0.
Player * Game::find_player(const char * & name) {
	for (int i = 0; i < playerpVector_.size(); i++) {
		if (playerpVector_[i]->playerName_.compare((string)name)==0) {
			return playerpVector_[i];
		}
	}
	return 0;
}

//This method is called once per betting phase. It keeps track of the current betting.
int Game::betting_phase(Player & player) {
	std::cout << "Name: "<<player.playerName_ << ", Hand: " <<player.playerHand_.asString() << ", Chips: " << player.chips_ << std::endl;
	if (currentBet_==0) {
		bet:
		std::cout << "Do you want to bet, or check? (b/c)" << std::endl;
		char z;
		cin >> z;
		while (z!='b' && z!='c') {
			std::cout << "Do you want to bet, or check? (b/c)" << std::endl;
			cin >> z;
		}
		if (z=='b') {
			std::cout << "Would you like to bet 1, or 2 chips. You can also hit c to cancel. (1/2/c)" << std::endl;
			char y;
			cin >> y;
			while (y!='1' && y!='2' && y!='c') {
				std::cout << "Would you like to bet 1, or 2 chips. You can also hit c to cancel. (1/2/c)" << std::endl;
				cin >> y;
			}
			if (y=='1' && player.chips_==0) {
				std::cout <<"You do not have enough chips to bet a chip." << std::endl;
				goto bet;
			}
			if (y=='2' && (player.chips_==0||player.chips_==1)) {
				std::cout <<"You do not have enough chips to bet two chips." << std::endl;
				goto bet;
			}
			if (y=='1' && player.chips_>0) {
				player.chips_ = player.chips_ - 1;
				pot_ = pot_ + 1;
				currentBet_ = 1;
				player.chipsBet_ = 1;
				std::cout <<"You bet one chip." << std::endl;
			}
			if (y=='2' && player.chips_>1) {
				player.chips_ = player.chips_ - 2;
				pot_ = pot_ + 2;
				currentBet_ = 2;
				player.chipsBet_ = 2;
				std::cout <<"You bet two chips." << std::endl;
			}
			if (y=='c') {
				std::cout << "You bet no chips." << std::endl;
			}
		}
		if (z=='c') {
			std::cout << "You checked." << std::endl;
		}
	}
	else {
		fcr:
		std::cout << "The current bet is " << currentBet_ << " chips. Would you like to fold, call, or raise? (f/c/r)" << std::endl;
		char x;
		cin >> x;
		while (x!='f' && x!='c' && x!='r') {
			std::cout << "The current bet is " << currentBet_ << " chips. Would you like to fold, call, or raise? (f/c/r)" << std::endl;
			cin >> x;
		}
		if (x=='f') {
			std::cout << "You folded." << std::endl;
			player.inRound_ = false;
		}
		if (x=='c') {
			int callChips = currentBet_ - player.chipsBet_;
			if (callChips > player.chips_) {
				std::cout << "You do not have enough chips to call. The current bet is "<<currentBet_ << " and you only have " << player.chips_ <<" chips." <<std::endl;
				std::cout << "Would you like to go all in and create a sidepot? If no, then you will fold. (y/n)" << std::endl;
				char w;
				cin >> w;
				while (w!='y' && w!='n') {
					std::cout << "Would you like to go all in and create a sidepot? If no, then you will fold. (y/n)" << std::endl;
					cin >> w;
				}
				if (w=='y') {
					pot_ = pot_ + player.chips_;
					player.sidePot_.sidePotChips_ = pot_;
					player.chipsBet_ = player.chipsBet_ + player.chips_;
					player.chips_ = 0;
					player.sidePot_.in_ = true;
					std::cout << "You went all in. Your sidepot contains " <<player.sidePot_.sidePotChips_<< " chips." << std::endl;
				}
				if (w=='n') {
					std::cout <<"You folded." <<  std::endl;
					player.inRound_ = false;
				}
			}
			else {
				player.chips_ = player.chips_ - callChips;
				player.chipsBet_ = player.chipsBet_ + callChips;
				pot_ = pot_ + callChips;
				std::cout << "You put in "<<callChips <<" chips to call." <<std::endl;
			}
		}
		if (x=='r') {
			int callChips = currentBet_ - player.chipsBet_;
			std::cout << "Would you like to raise 1, or 2 chips? (1/2)" << std::endl;
			char y;
			cin >> y;
			while (y!='1' && y!='2') {
				std::cout << "Would you like to raise 1, or 2 chips? (1/2)" << std::endl;
				cin >> y;
			}
			if (y=='1' && (player.chips_ < (currentBet_-player.chipsBet_+1))) {
				std::cout <<"You do not have enough chips to raise a chip." << std::endl;
				goto fcr;
			}
			if (y=='2' &&(player.chips_ < (currentBet_-player.chipsBet_+2))) {
				std::cout <<"You do not have enough chips to raise two chips." << std::endl;
				goto fcr;
			}
			if (y=='1' &&  (player.chips_ >= (currentBet_-player.chipsBet_+1))) {
				player.chips_ = player.chips_ - callChips - 1;
				pot_ = pot_ + 1 + callChips;
				currentBet_ = currentBet_ + 1;
				player.chipsBet_ = player.chipsBet_ + callChips + 1;
				std::cout <<"You put in " << (callChips+1) << " chips to raise the bet one chip." << std::endl;
			}
			if (y=='2' && (player.chips_ >= (currentBet_-player.chipsBet_+2))) {
				player.chips_ = player.chips_ - callChips - 2;
				pot_ = pot_ + 2 + callChips;
				currentBet_ = currentBet_ + 2;
				player.chipsBet_ = player.chipsBet_ + callChips + 2;
				std::cout <<"You put in " << (callChips+2) << " chips to raise the bet two chips." << std::endl;
			}
		}
	}
	std::cout << "The pot currently has " << pot_ << " chips." << std::endl;
	return 0;
}

//This is used for displaying cards in seven card stud
void Game::betweenTurnDisplay (Player & p) {
	std::cout << p.playerName_ << ", it is your turn. This is your hand: " << p.playerHand_.asString() << std::endl;
	std::cout << "You have " << p.chips_ << " chips." << std::endl;
	std::cout << "These are your opponents hands: " << std::endl;
	for (int i = 0; i < playerpVector_.size(); i++) {
		if (playerpVector_[i] == &p) {
			continue;
		}
		else {
			std::cout << playerpVector_[i]->playerName_<<"'s hand: ";
			for (int j = 0; j < playerpVector_[i]->playerHand_.getHandVector().size(); j++) {
				if (playerpVector_[i]->playerHand_.getHandVector()[j].faceDown_ == false) {
					std::cout << toString(playerpVector_[i]->playerHand_.getHandVector()[j]) <<" ";
				}
				else {
					std::cout << "* ";
				}
			}
			std::cout << std::endl;
		}
	}
}

//This method cuts down alot of extra code written when operating a new betting phase in SevenCardStud::before_round()
int Game::new_betting_phase(unsigned int dealtPos){
	currentBet_ = 0;
	for (int i = 0; i < playerpVector_.size(); i++) {
		playerpVector_[i]->chipsBet_ = 0;
	}
	while (true) {
		for (int i = 0; i < playerpVector_.size(); i++) {
			if ((playerpVector_[(dealtPos+i)%playerpVector_.size()]->inRound_ == true) && (playerpVector_[(dealtPos+i)%playerpVector_.size()]->sidePot_.in_ == false)){
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
	return 0;
}