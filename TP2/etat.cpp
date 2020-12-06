#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <queue>
#include <random>
#include "etat.hpp"

using namespace std;

etat::~etat()
{
    map<char, etat *>::iterator it;
    for(it = enfants.begin(); it != enfants.end(); it++)
    {
        delete(it->second);
    }
}

//permet d'ajouter un mot au lexique
//l'indice donné en argument correspond à l'indice du caractère du mot que l'on est en train de tester
void etat::ajouterMot(string mot, int indice)
{
    //si nous sommes à la fin du mot, l'état actuel est alors un état terminal
    if(int(mot.length())-1 == indice)
    {
        terminal = true;
    }
    //sinon on continue à parcourir l'automate
    else
    {
        indice ++;
        etat *fils = trouverFils(mot.at(indice));
        //si l'état actuel n'a pas de fils correspondant au caractère testé, un nouvel état est ajouté à l'automate
        if(fils == nullptr)
        {
            fils = new etat();
            enfants.insert(map<char, etat*>::value_type(mot.at(indice), fils));
        }
        fils->ajouterMot(mot, indice);
    }
}

//permet d'obtenir le pointeur vers l'état suivant
etat *etat::trouverFils(char lettre)
{
    map<char, etat *>::iterator it;
    it = enfants.find(lettre);
    if(it == enfants.end())
        return nullptr;
    return enfants.at(lettre);
}

//fouille en largeur depuis un état pour obtenir tout les mots qu'il est possible de former à partir du mot passé en argument
set<string> etat::getToutFils(string debut)
{
    set<string> lexique;
    queue<pair<string, etat*>> aExplorer;
    map<char, etat *>::iterator it;
    etat *etatCourant;
    string chaineCourante;

    //si l'état actuel est final, on ajoute le mot correspondant à la liste
    if(terminal)
    {
        lexique.insert(debut);
    }

    //ajout des états accessibles à la liste des états à Explorer
    for(it = enfants.begin(); it != enfants.end(); it++)
    {
        aExplorer.push({debut+it->first, it->second});
    }

    //fouille en largeur
    while (!aExplorer.empty())
    {
        etatCourant = aExplorer.front().second;
        chaineCourante = aExplorer.front().first;   
        if(etatCourant->terminal)
            lexique.insert(chaineCourante);
        
        for(it = etatCourant->enfants.begin(); it != etatCourant->enfants.end(); it++)
        {
            aExplorer.push({chaineCourante+it->first, it->second});
        }
        aExplorer.pop();
    }
    
    return lexique;
}

//fonction récursive pour atteindre l'état où nous emmene le mot
//l'indice en argument correspond à l'indice du caractère dans le mot
set<string> etat::getLexique(string mot, int indice)
{
    set<string> lexique;
    //si nous sommes à la fin du mot, lancement de la fouille en largeur
    if(int(mot.length())-1 == indice)
    {
        lexique = getToutFils(mot);
    }
    else
    {
        indice++;
        etat *fils = trouverFils(mot.at(indice));
        //si le caractère testé ne nous fait passer à nouvel état, alors le mot donné en argument n'est pas dans le lexique
        //une liste vide est alors retournée
        if(fils == nullptr)
            lexique = {};
        else
        {
            lexique = fils->getLexique(mot, indice);
        }  
    }
    return lexique;
}

//retourne un mot aléatoire du lexique
string etat::choixAleatoire()
{
    //récupération du lexique
    set<string> lexique = getLexique("", -1);
    vector<string> lexiquecopy(lexique.size());
    copy(lexique.begin(), lexique.end(), lexiquecopy.begin());
    
    //tirage aléatoire d'un mot
    random_device generator;
    uniform_int_distribution<int> tirage(0, lexique.size()-1);
    return lexiquecopy[tirage(generator)];
}

