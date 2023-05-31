#include "Joueur.hpp"

Joueur::Joueur()
{
}

std::vector<Arene::infoAction> Joueur::tour(int ID, std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map, int tailleMap)
{
    Arene areneVirtuel(listeDesTortues,map,tailleMap);

    Tortue* tortue=areneVirtuel.trouveLaTortueID(ID);
    std::vector<Arene::infoAction> currentTour;
    Arene::infoAction currentAction;

    int tuile;
    bool peutTirer=true;


    while (tortue->PE()>0 and not areneVirtuel.finPartie() and continuTour()=='y')
    {
        if (peutTirer and tirer(areneVirtuel.posTortueAPorterDeTir(tortue))=='y')
        {
            tuile=cible(areneVirtuel.posTortueAPorterDeTir(tortue));
            areneVirtuel.tir(tortue,tuile);
            peutTirer=false;
            currentAction.identifiant=areneVirtuel.numeroDeLaTortue(tortue);
            currentAction.typedAction=Arene::typeAction::tir;
            currentAction.positionAction=tuile;
        }
        else
        {
            tuile=mouvement(areneVirtuel.listeMouvementsPossibles(tortue));
            areneVirtuel.deplacerTortue(tortue,tuile);
            currentAction.identifiant=areneVirtuel.numeroDeLaTortue(tortue);
            currentAction.typedAction=Arene::typeAction::deplacement;
            currentAction.positionAction=tuile;
        }
        currentTour.push_back(currentAction);
    }
    return currentTour;
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
    char n;
    if (tortueCible.empty())
        return 'n';
    else
    {
        std::cout<<"Voulez vous tirer(y/n) : "<<std::endl;
        std::cin>>n;
        std::cout<<std::endl;
        return n;
    }
}

int Joueur::cible(std::vector<int> tortueCible)
{
    int n;
    std::cout<<"Vous pouvez vous tirer sur ces cases : "<<std::endl;
    for (auto i:tortueCible)
    {
        std::cout<<"|"<<i<<"|";
    }
    std::cout<<std::endl<<"Voulez tirer sur quelles cases : ";
    std::cin>>n;

    std::cout<<std::endl;
    return n;
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
