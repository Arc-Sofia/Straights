#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>

void Subject::attach(Observer* o) { observers.push_back(o); }

void Subject::notifyObservers() {
    for (auto& ob : observers) ob->notify(*this);
}

int Subject::toInt(char card) const {
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
