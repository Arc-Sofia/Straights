#include "shuffler.h"

Shuffler::Shuffler() : 
	deck{ std::vector<std::string>{ "AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "TC", "JC", "QC", "KC",
									"AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD", "KD",
									"AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "TH", "JH", "QH", "KH",
									"AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS", "JS", "QS", "KS"
									} }, 
	seed{ 0 } {}

std::vector<std::string> Shuffler::getDeck() { return deck; }
void Shuffler::setSeed(unsigned int s) { seed = s; }

void Shuffler::shuffle() {
	std::default_random_engine rng{ seed };
	std::shuffle(deck.begin(), deck.end(), rng);
}

std::vector<std::string*> Shuffler::distribute(int player) {
	std::vector<std::string*> partition;
	size_t begin = (player - 1) * 13;
	size_t end = begin + 12;

	for (size_t i = begin; i <= end; i++) { partition.push_back(&deck[i]); }
	return partition;
}