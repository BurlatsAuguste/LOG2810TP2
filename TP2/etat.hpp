#include <vector>
#include <string>
#include <map>
#include <set>

#ifndef DEF_etat
#define DEF_etat

class etat
{
private:
    bool terminal;
    std::map<char, etat *> enfants;

public:
    etat(){terminal = false;};
    ~etat();
    void ajouterMot(std::string mot, int indice = -1);
    etat *trouverFils(char lettre);
    std::set<std::string> getLexique(std::string debut, int indice);
    std::set<std::string> getToutFils(std::string debut);
    std::string choixAleatoire();
};


#endif