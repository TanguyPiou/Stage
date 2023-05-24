#include "IAleatoire.hpp"

IAleatoire::IAleatoire():IA()
{
}

std::vector<Arene::infoAction> IAleatoire::tour(int ID,std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map,int tailleMap)
{
    Arene areneVirtuel(listeDesTortues,map,tailleMap);

    Tortue* tortue=areneVirtuel.trouveLaTortueID(ID);
    std::vector<Arene::infoAction> currentTour;
    Arene::infoAction currentAction;

    int tuile;
    bool peutTirer=true;


    while (tortue->PE()>0 and not areneVirtuel.finPartie())
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
    srand (time(NULL));
    int Atoir = rand() % tortueCible.size();
    return tortueCible[Atoir];
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

