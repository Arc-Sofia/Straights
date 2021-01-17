#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "subject.h"


// Subject of Player
class Board : public Subject {
	std::vector<char> clubs;
	std::vector<char> hearts;
	std::vector<char> spades;
	std::vector<char> diamonds;
	
	void insertCard(std::vector<char> &suit, char card);
	
public:
	// default cstr
	Board();

	//adds a card to the pile corresponding to its suit
	void addCard(std::string card);
	//empties the board for a new round
	void reset();

	//returns a vector of cards for suit that has been played
	virtual std::vector<char> getSuit(char suit) const;
	
	//get suit piles
	std::vector<char> getClubs() const;
	std::vector<char> getHearts() const;
	std::vector<char> getSpades() const;
	std::vector<char> getDiamonds() const;


};

std::ostream& operator<<(std::ostream& out, const Board& g);

#endif
