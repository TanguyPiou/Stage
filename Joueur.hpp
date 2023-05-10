#pragma once
#include "IA.hpp"
#include "Arene.hpp"


class Joueur : public IA
{
public:

    Joueur();
    std::vector<Arene::infoAction> tour(int ID, std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map,int tailleMap) override;
    char continuTour();
    char tirer(std::vector<int> tortueCible);
    int cible(std::vector<int> tortueCible);
    int mouvement(std::vector<int> mvDispo);


private:
};


