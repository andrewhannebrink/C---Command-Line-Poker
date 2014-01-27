//Andrew Hannebrink (408421)
//ahannebrink@wustl.edu

//This header file defines the abstract base class game, and the games that inherit from it

#ifndef GAME_H
#define GAME_H
#include "deck.h"
#include "player.h"

enum errorStates {game_success, instance_not_available, game_already_started, unknown_game, no_game_in_progress, already_playing};

class Game {
public:
	static Game * instance();
	static void start_game(const string);
	static void stop_game();
	void add_player(const string);
	Player * find_player(const char * &);
	virtual ~Game()  = 0;
	Game();
	int betting_phase(Player &);
	virtual int before_turn(Player &)  =0;
	virtual int turn(Player &) =0;
	virtual int after_turn(Player &) =0;
	virtual int before_round() =0;
	virtual int round() =0;
	virtual int after_round() =0;
	int pot_;
	int currentBet_;
	void betweenTurnDisplay (Player & p);
	int new_betting_phase(unsigned int);
protected:
	static Game * gamep_;
	Deck deck_;
	std::vector<Player *> playerpVector_;
private:
	Game(const Game &);
	Game & operator= (const Game &);
};



#endif