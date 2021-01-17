#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "observer.h"
class Observer;

class Subject {
	std::vector<Observer*> observers;
public:
	
	virtual std::vector<char> getSuit(char suit) const = 0; //used only by Board class
	int toInt(char card) const;
	//no detach since # of observers stays fixed throughout program's lifetime
	void attach(Observer* o);
	void notifyObservers();
};



#endif
