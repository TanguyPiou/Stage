#pragma once
#include <vector>
#include <string>
#include <iostream>

class IA
{
public:

    IA();
    virtual char continuTour()=0;
    virtual char tirer(std::vector<int> tortueCible)=0;
    virtual int cible(std::vector<int> tortueCible)=0;
    virtual int mouvement(std::vector<int> mvDispo)=0;


private:
};
