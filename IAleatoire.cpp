#include "IAleatoire.hpp"

IAleatoire::IAleatoire():IA()
{
}

char IAleatoire::continuTour()
{
    return 'y';
}

char IAleatoire::tirer(std::vector<int> tortueCible)
{
    if (tortueCible.empty())
        return 'n';
    else
        return 'y';
}

int IAleatoire::cible(std::vector<int> tortueCible)
{
    std::cout<<"";
    return tortueCible[0];
}

int IAleatoire::mouvement(std::vector<int> mvDispo)
{
    srand (time(NULL));
    int Atoir = rand() % mvDispo.size();
    /* TEST
    std::cout<<"test nbr aléatoire : "<<Atoir<<std::endl;
    std::cout<<"Déplacement effectué ??? : "<<mvDispo[Atoir]<<std::endl;
    //*/
   return mvDispo[Atoir];
}

