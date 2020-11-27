#include <vector>
#include <string>
#include <map>

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
    void ajouterMot(std::string mot, int indice);
    etat *trouverFils(char lettre);
    std::vector<std::string> getLexique(std::string debut, int indice);
    std::vector<std::string> getToutFils(std::string debut);
    std::string choixAleatoire();
};


#endif