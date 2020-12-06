#include <string>
#include "Machine.hpp"

using namespace std;

//création de la machine de Mealy
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
	}
}

//Retour est 1/0 et la fonction passe au prochain état
int Machine::next(char let)
{
	char let2 = current->getLet();
	current = current->getNext();
	return let == let2 ? 0:1;
}

//détermine le nombre d'erreurs dans un mot test
//retourne -1 si les chaines ne sont pas de longueur egale
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
