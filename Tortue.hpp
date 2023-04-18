#pragma once
#include "Armes.hpp"

class Tortue {
public:

    Tortue(std::string nom, float PV, float pointEndu, Armes arme, int pos):
    _nom(nom), _PV(PV), _PE(pointEndu), _arme(arme), _pos(pos){};

    std::string nom();
    float PV();
    float PE();
    int pos();

private:
    std::string _nom;
    float _PV;
    float _PE;
    Armes _arme;
    int _pos;
};
