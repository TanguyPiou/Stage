#pragma once
#include "IA.hpp"


class Joueur : public IA
{
public:

    Joueur();
    char continuTour() override;
    char tirer(std::vector<int> tortueCible) override;
    int cible(std::vector<int> tortueCible) override;
    int mouvement(std::vector<int> mvDispo) override;


private:
};

