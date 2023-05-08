#pragma once
#include "IA.hpp"


class IAleatoire : public IA
{
public:

IAleatoire();
char continuTour() override;
char tirer(std::vector<int> tortueCible) override;
int cible(std::vector<int> tortueCible) override;
int mouvement(std::vector<int> mvDispo) override;


private:

};
