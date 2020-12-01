#include <string>
#include "Machine.hpp"

using namespace std;


Machine::Machine(string mot)
{
	length = mot.length();
	current = nullptr;
	start = nullptr;
	if (length > 0)
	{
		current = new state(mot.at(0));
		start = current;
		state* prev = current;
		state* actual = nullptr;
		for (size_t i = 1; i < length; i++)
		{
			actual = new state(mot.at(i));
			prev->setNext(actual);
			prev = actual;
		}
		//actual->setNext(start);
	}
}

int Machine::next(char let)
{
	char let2 = current->getLet();
	current = current->getNext();
	return let == let2 ? 0:1;
}

int Machine::errors(string mot)
{
	if (mot.length() != length)
		return -1;
	int ans = 0;
	for (size_t i = 0; i < mot.length(); i++)
	{
		ans += next(mot.at(i));
	}
	current = start;
	return ans;
}