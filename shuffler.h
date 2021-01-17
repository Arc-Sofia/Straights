#ifndef _SHUFFLER_H_
#define _SHUFFLER_H_

#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include "subject.h"

//class Subject;

class Shuffler {
	std::vector<std::string> deck;
	unsigned int seed;
public:
	Shuffler();

	//accessor
	std::vector<std::string> getDeck();
	//mutator
	void setSeed(unsigned int s);

	void shuffle();
	std::vector<std::string*> distribute(int par);
};

#endif