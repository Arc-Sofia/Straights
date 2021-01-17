#include "board.h"

Board::Board() {}

//insert a new card in order of the card's rank
void Board::insertCard(std::vector<char> &suit, char cardRank) {
	
	if (suit.empty()) { 
		suit.push_back(cardRank); 
		return;
	}
	for (auto it = suit.begin(); it < suit.end(); it++) {
		if (toInt(cardRank) < toInt(*it)) {
			suit.insert(it, cardRank);
			return;
		}
	}
	suit.push_back(cardRank);
}
void Board::addCard(std::string card) {
	//last character of card is the suit
	auto s = card.rbegin();
	switch (*s) {
	case 'C':
		//std::cout << 'C';
		insertCard(clubs, card[0]);
		break;
	case 'H':
		//std::cout << 'H';
		insertCard(hearts, card[0]);
		break;
	case 'S':
		//std::cout << 'S';
		insertCard(spades, card[0]);
		break;
	case 'D':
		//std::cout << 'D';
		insertCard(diamonds, card[0]);
	}
	//notify all observers(players) of change in board
	notifyObservers();
}

void Board::reset() {
	clubs.clear();
	hearts.clear();
	spades.clear();
	diamonds.clear();
}

std::vector<char> Board::getSuit(char suit) const {
	switch (suit) {
	case 'C': return getClubs();
	case 'H': return getHearts();
	case 'S': return getSpades();
	case 'D': return getDiamonds();
	}
}

std::vector<char> Board::getClubs() const {
	std::vector<char> ret;
	for (size_t i = 0; i < clubs.size(); i++) {
		if (clubs[i] != 0) {
			ret.push_back(clubs[i]);
		}
	}
	return ret;
}
std::vector<char> Board::getHearts() const { 
	std::vector<char> ret;
	for (size_t i = 0; i < hearts.size(); i++) {
		if (hearts[i] != 0) {
			ret.push_back(hearts[i]);
		}
	}
	return ret;
}
std::vector<char> Board::getSpades() const { 
	std::vector<char> ret;
	for (size_t i = 0; i < spades.size(); i++) {
		if (spades[i] != 0) {
			ret.push_back(spades[i]);
		}
	}
	return ret;
}
std::vector<char> Board::getDiamonds() const { 
	std::vector<char> ret;
	for (size_t i = 0; i < diamonds.size(); i++) {
		if (diamonds[i] != 0) {
			ret.push_back(diamonds[i]);
		}
	}
	return ret;
}


std::ostream& operator<<(std::ostream& out, const Board& g) {
	out << "Cards on the table:" << std::endl;
	out << "Clubs: ";
	for (auto it : g.getClubs()) { out << it << ' '; }
	out << std::endl;

	out << "Diamonds: ";
	for (auto it : g.getDiamonds()) { out << it << ' '; }
	out << std::endl;
	
	out << "Hearts: ";
	for (auto it : g.getHearts()) { out << it << ' '; }
	out << std::endl;
	
	out << "Spades: ";
	for (auto it : g.getSpades()) { out << it << ' '; }
	return out;
}

