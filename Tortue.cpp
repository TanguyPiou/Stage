#include "Tortue.hpp"


std::string Tortue::nom()
{
    return _nom;
}

float Tortue::PV()
{
    return _PV;
}

void Tortue::setPV(float newPV)
{
    _PV=newPV;
}

float Tortue::PE()
{
    return _PE;
}

void Tortue::setPE(float newPE)
{
    _PE=newPE;
}

int Tortue::pos()
{
    return _pos;
}

void Tortue::setPos(int newPos)
{
    _pos=newPos;
}

bool Tortue::tir()
{
    return _tir;
}

void Tortue::setTir(bool tir)
{
    _tir=tir;
}

Armes Tortue::arme()
{
    return _arme;
}


