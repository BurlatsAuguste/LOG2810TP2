#pragma once

#include <string>


//Classe pour entreposer un état du système
class state{
		private:
			char let;
			state* next;

		//fonctions get/set standard
		public:
			state(char letter, state* n = nullptr) :let(letter), next(n) {};
			~state(){delete next;};
			state* getNext() { return next; };
			char getLet() { return let; };
			void setNext(state* n) { next = n; };

};

class Machine {

private:

	state* current;
	state* start;
	size_t length;//permet de supprimer tous les pointeurs des states de la machine

public:
	Machine(std::string mot);
	~Machine(){delete(start);};
	int next(char let);
	int errors(std::string mot);

};

