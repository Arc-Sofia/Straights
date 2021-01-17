#include <iostream>
#include <chrono>
#include "board.h"
#include "player.h"
#include "shuffler.h"

int main(int argc, char* argv[]) {
	//default seed is current system time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//user inputed seed from command line
	if (argc > 1) {
		try {
			seed = std::stoi(std::string{ argv[1] });
		}
		catch (std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
		catch (std::out_of_range& e) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
	}

	Board game;

	Shuffler sh_deck;
	int turn = 0;
	std::vector<Player*> players;
	Player p1(1, &sh_deck);
	Player p2(2, &sh_deck);
	Player p3(3, &sh_deck);
	Player p4(4, &sh_deck);
	players.push_back(&p1);
	players.push_back(&p2);
	players.push_back(&p3);
	players.push_back(&p4);

	game.attach(&p1);
	game.attach(&p2);
	game.attach(&p3);
	game.attach(&p4);

	std::string cmd;

	//game initialization
	bool win = false;
	for (auto pl : players) {
		try {
			std::cout << "Is Player" << pl->getName() << " a human (h) or a computer (c)?" << std::endl;
			std::cin >> cmd;
			if (cmd == "c") { pl->ragequit(); }
			else if (cmd == "h") {}
			else { throw std::invalid_argument{ "Error: player declared as neither human or computer." }; }
		}
		catch (std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << "Terminating game" << std::endl;
			exit(1);
		}
	}

	Player* pl;
	while (!win) {
		game.reset();
		for (auto pl : players) { pl->reset(); }
		sh_deck.shuffle(); //shuffle deck for first round;
		for (auto pl : players) { pl->setHand(); }
		game.notifyObservers();

		for (auto pl : players) {
			if (pl->isValid("7S")) { turn = pl->getName() - 1; }
		}

		std::cout << "A new round begins. It's Player" << players[turn]->getName() << "'s turn to play." << std::endl;
		while (true) {
			if (turn > 3) { turn = 0; }
			pl = players[turn];

			if (pl->getHand().empty()) {
				for (auto p : players) {
					int s = 0;
					std::vector<std::string> discards = p->getDiscard();

					std::cout << "Player" << p->getName() << "'s discards: ";
					for (auto r : discards) {
						std::cout << r << ' ';
						s += p->toInt(r[0]);
					}
					std::cout << std::endl;

					std::cout << "Player" << p->getName() << "'s score: " <<
						p->getScore() << " + " << s << " = ";
					p->addScore(s);
					if (p->getScore() >= 80) { win = true; }
					std::cout << p->getScore() << std::endl;
				}
				break;
			}
			if (pl->isHuman()) {
				std::cout << game << std::endl;
				std::cout << *pl << std::endl;
				std::cin >> cmd;
				if (std::cin.eof()) { exit(0); }
				try {
					if (cmd == "deck") {
						for (int i = 1; i <= 4; i++) {
							for (auto it : sh_deck.distribute(i)) {
								std::cout << *it << ' ';
							}
							std::cout << std::endl;
						}
					}
					else if (cmd == "play") {
						std::string card;
						std::cin >> card;
						pl->playCard(card);
						game.addCard(card);
						//std::cout << "Player" << pl->getName() << " plays " << card << "." << std::endl;
					}
					else if (cmd == "discard") {
						std::string card;
						std::cin >> card;
						pl->discardCard(card);
						//std::cout << "Player" << pl->getName() << " discards " << card << "." << std::endl;
					}
					else if (cmd == "ragequit") { 
						pl->ragequit(); 
						std::cout << "Player" << pl->getName() << " ragequits. A computer will now take over." << std::endl;
						std::string card = pl->playAlgorithm();
						if (card != "") { game.addCard(card); }
					}
					else if (cmd == "quit") { exit(0); }
					else { throw std::invalid_argument{ "Error: unknown command " + cmd }; }
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
					turn--;
				} //try
			} //if 
			else {
				std::string card = pl->playAlgorithm();
				if (card != "") { game.addCard(card); }
			}
			turn++;
			std::cout << std::endl;
		} //while
	} //while

	std::vector<Player*> winners;
	int lowest = players[0]->getScore();
	for (auto pl : players) {
		if (pl->getScore() < lowest) { lowest = pl->getScore(); }
	}
	for (auto w : players) {
		if (w->getScore() == lowest) { winners.push_back(w); }
	}
	for (auto w : winners) {
		std::cout << "Player" << w->getName() << " wins!" << std::endl;
	}
} //main