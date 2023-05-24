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


private:
};
