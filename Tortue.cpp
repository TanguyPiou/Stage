#include "Tortue.hpp"


std::string Tortue::nom() const
{
    return _nom;
}

float Tortue::PV() const
{
    return _PV;
}

void Tortue::setPV(float newPV)
{
    _PV=newPV;
}

float Tortue::PE() const
{
    return _PE;
}

void Tortue::setPE(float newPE)
{
    _PE=newPE;
}

int Tortue::pos() const
{
    return _pos;
}

void Tortue::setPos(int newPos)
{
    _pos=newPos;
}

bool Tortue::tir() const
{
    return _tir;
}

void Tortue::setTir(bool tir)
{
    _tir=tir;
}

Armes Tortue::arme() const
{
    return _arme;
}


