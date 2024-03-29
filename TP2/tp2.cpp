#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "etat.hpp"
#include "Machine.hpp"

using namespace std;

//retourne le nombre de ligne du fichier dont le nom est donné en argument
int getNbLigne(string filename)
{
    ifstream file(filename);
    if(!file)
    {
        //cout << "Impossible d'ouvrir le fichier en lecture" << endl;
        exit(-1);
    }
    string ligne;
    int nbLigne = 0;
    while(getline(file, ligne))
    {
        nbLigne++;
    }
    file.close();
    return nbLigne;
}

//initialise le lexique depuis le fichier dont le nom est passé en argument
//retourne un pointeur vers l'état initial de l'automate
etat *creerLexique(string filename)
{
    ifstream file(filename);

    //si le nom de fichier donné par l'utilisateur n'est pas bon, la fonction s'arrête et retourne nullptr
    if(!file)
    {
        cout << "Impossible d'ouvrir le fichier en lecture" << endl;
        return nullptr;
    }
    etat *automate = new etat();
    string mot;
    file >> mot;
    int count = 1;
    int nombreLigne = getNbLigne(filename);
    
    //ajouter tous les mots au lexique
    while(count <= nombreLigne)
    {
        automate->ajouterMot(mot, -1);
        file >> mot;
        count++;
    } 
    return automate;
}

//Fonction qui effectue la partie 2 du jeu soit les essais et le nombre d'erreurs
//Retourne true si l'utilisateur gagne false sinon

bool partie2(Machine* machines)
{
    //15 essais au maximum
    for (int i = 0; i < 15; i++)
    {
        string guess;
        cin >> guess;

        int errors = machines->errors(guess);

        //traitement selon le nombre d'erreurs
        if (errors == 0) {
            cout << "Bravo vous avez trouve le code secret !" << endl;
            return true;
        }
        if (errors == -1) {
            cout << "Le mot n'est pas de la bonne longueur" << endl;
        }
        else {
            cout << "Le code entré comporte " << errors << " erreurs" << endl;
        }
    }
    return false;
    
}

//Lancement du choix automatique de mot
void modeAuto(etat* racine) {

    //trouver un mot aléatoire dans le lexique
    string randomWord = racine->choixAleatoire();
    Machine* machines = new Machine(randomWord);

    cout << "Mode automatique lancé" << endl;
    cout << "Le mot à chercher est d'une longeur de " << randomWord.length() << " lettres" << endl << endl;

    bool win = partie2(machines);
    if (!win)
        cout << "Quinze essais effectués. Vous avez perdu." << endl << "Le code était : " << randomWord << endl;

    delete machines;


}

void modeDeuxJoeur(etat* racine) {
    string code;
    bool choisi = false;
    

    while (! choisi)
    {
        cout << "Entrez le code secret : " << endl;
        cin >> code;

        set<string> lexique = racine->getLexique(code, -1);

        bool isWord = !(std::find(lexique.begin(), lexique.end(), code) == lexique.end());
        if (!isWord) {
            cout << "Ce mot n'existe pas dans le lexique" << endl<<endl;
        }

        cout << "Suggestion(s)" << endl;
        for (string el : lexique)
        {
            cout << el << endl;
        }
        cout << endl;

        if (isWord)
        {
            cout << "Voulez - vous s´electionner ce code ? (1:oui / 0 : non)" << endl;
            cout << "Réponse: ";
            int choix;
            cin >> choix;
            if (choix == 1)
                choisi = true;
        }

    }

    cout << "Le code sélectionné est: " << code<<endl<<endl;

    Machine* machines = new Machine(code);

    cout << "Le mot à chercher est d'une longeur de " << code.length() << " lettres" << endl << endl;

    bool win = partie2(machines);
    if (!win)
        cout << "Quinze essais effectués. Vous avez perdu." << endl << "Le code était : " << code << endl;
    
    delete machines;
}


int main(int argc, char const *argv[])
{
    int choix_action;
    string filename;
    string recherche;
    etat *automate = nullptr;

    while (true)
    {
        cout << endl << "Que souhaitez-vous faire ?" << endl
               << "1 Initialisation du jeu"<< endl
               <<"2 Partie contre l'ordinateur"<< endl
                <<"3 Deux joueurs"<< endl
                <<"4 Quitter" <<endl;
    
    //choix de l'action
        if(cin >> choix_action)
        {
            switch(choix_action)
            {
                case 1:
                    if(automate)
                        delete(automate);
                    cout << "Veuillez entrer le chemin vers le fichier" << endl;
                    cin >> filename;
                    automate = creerLexique(filename);
                    break;
                case 2:
                    if (!automate)
                        cout << "Veuiller au préalable initialiser le jeu " << endl;

                    else
                        modeAuto(automate);
                    break;
                case 3:
                    if (!automate)
                        cout << "Veuiller au préalable initialiser le jeu " << endl;

                    else
                        modeDeuxJoeur(automate);
                    break;
                case 4:
                    cout << "au revoir" << endl;
                    //suppression des pointeurs pour éviter les fuites de mémoire
                    delete(automate);
                    exit(0);
                    break;
                default:
                    cout <<"Veuillez indiquer votre selection par un nombre entre 1 et 4" << endl;
            } 
        }
        else
        {
            cout <<"Veuillez indiquer votre selection par un nombre entre 1 et 5" << endl;
            cin.clear();
            cin.ignore(1);
        }
    }
    return 0;
}
