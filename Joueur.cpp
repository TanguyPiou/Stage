#include "Joueur.hpp"

Joueur::Joueur()
{
}


char Joueur::continuTour()
{
    char n;
    std::cout<<"Voulez vous continuer le tour(y/n) : ";
    std::cin>>n;
    std::cout<<std::endl;
    return n;
}

char Joueur::tirer(std::vector<int> tortueCible)
{
    if (tortueCible.empty())
        return 'n';
    else
    {
        std::cout<<"Oups l'aim bot est activé"<<std::endl;
        return 'y';
    }
}

int Joueur::cible(std::vector<int> tortueCible)
{
    std::cout<<"Oups le shoot bot est activé"<<std::endl;
    return tortueCible[0];
}

int Joueur::mouvement(std::vector<int> mvDispo)
{
    int n;
    std::cout<<"Vous pouvez vous déplacer sur les cases :";
    for (auto i:mvDispo)
    {
        std::cout<<"|"<<i<<"|";
    }
    std::cout<<std::endl<<"Voulez vous déplacer sur quelles cases : ";
    std::cin>>n;
    std::cout<<std::endl;

   return n;
}
