#include "Tortue.hpp"


Tortue::Tortue(std::string nom, float PV, float pointEndu, int degats, int pos)
    :_nom(nom), _PV(PV), _PE(pointEndu), _degats(degats), _pos(pos), _tir(false){};


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

int Tortue::degats() const
{
    return _degats;
}

void Tortue::setDegats(int degats)
{
    _degats=degats;
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


