#pragma once

//#include "state.h"
#include <string>

class state{
		private:
			char let;
			state* next;
			size_t length;


		public:
			state(char letter, state* n = nullptr) :let(letter), next(n) {};
			~state(){delete(next);};
			state* getNext() { return next; };
			char getLet() { return let; };
			void setNext(state* n) { next = n; };
			size_t getLength(){return length; };

};

class Machine {

private:

	state* current;
	state* start; //permet de supprimer tout les pointeurs des states de la machine

public:
	Machine(std::string mot);
	~Machine(){delete(start);};
	int next(char let);
	int errors(std::string mot);

};

