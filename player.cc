#include "player.h"


Player::Player(int name, Shuffler *shuffledDeck) : 
	score{ 0 }, name{ name }, human{ true }, shuffledDeck{ shuffledDeck }
{}


std::vector<std::string> Player::getDiscard() const { return discard; }
int Player::getName() const { return name; }
int Player::getScore() const { return score; }
std::vector<std::string*> Player::getHand() const { return hand; }
bool Player::isHuman() const { return human; }
std::vector<std::string*> Player::getValid() const { return validPlays; }

void Player::setHand() { hand = shuffledDeck->distribute(name); }
void Player::addScore(int s) { score += s; }
void Player::ragequit() { human = false; }

void Player::reset() {
	hand.clear();
	validPlays.clear();
	discard.clear();
}

int Player::toInt(char card) const {
	switch (card) {
	case 'A':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'T':
		return 10;
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;
	}
}

//look at the state of the board and determine the valid plays
void Player::notify(Subject& board) {
	//subject is the Board
	//hand[i] : string*
	std::vector<char> deck;
	//for (size_t it = 0; it < hand.size(); it++) {
	for (auto it : hand) {
		char suit = it->back();
		switch (suit) {
		case 'C':
			deck = board.getSuit('C');
			break;
		case 'H':
			deck = board.getSuit('H');
			break;
		case 'S':
			deck = board.getSuit('S');
			break;
		case 'D':
			deck = board.getSuit('D');
			break;
		}
		char rank = it->front();
		if (!isValid(*it)) { //card not already in validPlays
			//valid plays 7 of any suit
			if (toInt(rank) == 7) { validPlays.push_back(it); }
			else if (!deck.empty()) {
				//valid plays one smaller or bigger than any played card
				char s = deck.front();
				char l = deck.back();

				if (toInt(s) - toInt(rank) == 1) { validPlays.push_back(it); }
				else if (toInt(rank) - toInt(l) == 1) { validPlays.push_back(it); }
			}
		}
	}
}



bool Player::isValid(std::string card) {
	for (auto it : validPlays) {
		if (card == *it) { return true; }
	}
	return false;
}

std::string Player::playCard(std::string card) {
	if (!isValid(card)) { throw std::invalid_argument{  "This is not a legal play." }; }

	for (auto it = hand.begin(); it != hand.end(); it++) {
		if (**it == card) {
			hand.erase(it);
			break;
		}
	}
	for (auto it = validPlays.begin(); it != validPlays.end(); it++) {
		if (**it == card) {
			validPlays.erase(it);
			break;
		}
	}
	std::cout << "Player" << name << " plays " << card << "." << std::endl;
	return card;
}

void Player::discardCard(std::string card) {

	if (!validPlays.empty()) { throw std::invalid_argument{ "You have a legal play. You may not discard." }; }

	for (auto it = hand.begin(); it != hand.end(); it++) {
		if (**it == card) { 

			hand.erase(it); 

			discard.push_back(card);
			std::cout << "Player" << name << " discards " << card << "." << std::endl;
			return;
		}
	}
	if (true) { throw std::invalid_argument{ "You do not have that card." }; }
	
}

std::string Player::playAlgorithm() {
	//if computer has 7 of spades, must play 7S
	for (auto it : validPlays) {
		if (*it == "7S") { 
			playCard(*it); 
			return *it;
		}
	}

	if (validPlays.empty()) { 
		
		discardCard(*hand[0]); 
		return "";
	} //no valid plays, discard first card in hand
	else { 
		std::string ret = *validPlays[0];
		playCard(*validPlays[0]); //playCard removes card it plays. validPlays may be empty
		return ret;
	} //legal plays, play first legal card
	return "";
}

std::ostream& operator<<(std::ostream& out, const Player& p) {
	std::vector<std::string*> h = p.getHand();
	out << "Your hand: ";
	for (auto it : p.getHand()) { out << *it << ' '; }
	out << std::endl;
	out << "Legal Plays: ";
	for (auto it : p.getValid()) { out << *it << ' '; }

	return out;
}