#pragma once
#include "IA.hpp"


class IAleatoire : public IA{

public:

    IAleatoire();

    std::vector<Arene::infoAction> tour(int ID, std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map,int tailleMap) override;
    char continuTour();
    char tirer(std::vector<int> tortueCible);
    int cible(std::vector<int> tortueCible);
    int mouvement(std::vector<int> mvDispo);


private:

};
