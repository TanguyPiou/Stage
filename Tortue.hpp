#pragma once
#include "Armes.hpp"
#include <vector>

class Tortue {
public:

    Tortue(std::string nom, float PV, float pointEndu, Armes arme, int pos):
    _nom(nom), _PV(PV), _PE(pointEndu), _arme(arme), _pos(pos){};

    std::string nom();
    float PV();
    void setPV(float newPV);
    float PE();
    void setPE(float newPE);
    int pos();
    void setPos(int newPos);


private:
    std::string _nom;
    float _PV;
    float _PE;
    Armes _arme;
    int _pos;
};
