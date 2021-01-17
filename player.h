#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include "shuffler.h"
#include "board.h"
class Observer;
class Subject;

//Observer of Board
class Player : public Observer{
	std::vector<std::string*> hand;
	std::vector<std::string> discard;
	int name;
	int score;
	bool human;
	std::vector<std::string*> validPlays;
	Shuffler* shuffledDeck;
	//Board* game;
	
public:
	Player(int name, Shuffler *shuffledDeck);
	//accessors
	std::vector<std::string> getDiscard() const;
	int getName() const;
	int getScore() const;
	std::vector<std::string*> getHand() const;
	bool isHuman() const;
	std::vector<std::string*> getValid() const;
	//mutators
	//draws card from shuffler
	void setHand();
	void addScore(int s);

	bool isValid(std::string);
	std::string playCard(std::string card);
	void discardCard(std::string card);
	void ragequit(); //may do other things
	void reset(); // resets the player's hand, discard, and legal play piles

	//notified by board and determines valid plays for player's hand
	void notify(Subject& board);
	int toInt(char card) const; //changes a card's rank to an integer
	std::string playAlgorithm();
};

std::ostream& operator<<(std::ostream& out, const Player& p);
#endif
