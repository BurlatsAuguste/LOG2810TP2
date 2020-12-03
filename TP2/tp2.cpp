#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "etat.hpp"
#include "Machine.hpp"

using namespace std;

etat *creerLexique(string filename)
{
    ifstream file(filename);

    //si le nom de fichier donné par l'utilisateur n'est pas bon, la fonction s'arrête et retourne NULL
    if(!file)
    {
        cout << "Impossible d'ouvrir le fichier en lecture" << endl;
        return nullptr;
    }
    etat *automate = new etat();
    string mot;
    getline(file, mot);
    while(mot != "")
    {
        automate->ajouterMot(mot, -1);
        getline(file, mot);
    } 
    return automate;
}

void afficherLexique(etat *automate, string mot)
{
    set<string> lexique = automate->getLexique(mot, -1);
    for(string s : lexique)
        cout << s << endl;
    
}




bool partie2(Machine* machines)
{
    
    for (int i = 0; i < 15; i++)
    {
        string guess;
        cin >> guess;

        int errors = machines->errors(guess);

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

void modeAuto(etat* racine) {

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
