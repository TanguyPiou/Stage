#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Arene.hpp"

class IA
{
public:

    IA();
    virtual std::vector<Arene::infoAction> tour(int ID, std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map,int tailleMap)=0;
    /*virtual char continuTour()=0;
    virtual char tirer(std::vector<int> tortueCible)=0;
    virtual int cible(std::vector<int> tortueCible)=0;
    virtual int mouvement(std::vector<int> mvDispo)=0;
    */


private:
};
