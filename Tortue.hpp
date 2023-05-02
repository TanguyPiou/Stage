#pragma once
#include "Armes.hpp"
#include <vector>

class Tortue {
public:

    Tortue(std::string nom, float PV, float pointEndu, Armes arme, int pos):
    _nom(nom), _PV(PV), _PE(pointEndu), _arme(arme), _pos(pos), _tir(false){};

    std::string nom() const;
    float PV() const;
    void setPV(float newPV);
    float PE() const;
    void setPE(float newPE);
    int pos() const;
    void setPos(int newPos);
    bool tir() const;
    void setTir(bool tir);
    Armes arme() const;


private:
    std::string _nom;
    float _PV;
    float _PE;
    Armes _arme;
    int _pos;
    bool _tir;
};
