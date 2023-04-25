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





    /*
    Tortue *currentTortue;
    int nbcase=3;
    std::string direction="droite";
    if (Arene::Tour)
    {
        *currentTortue=_tortue1;
        if (currentTortue->PE()==0)
        {
            //"pouquoi je fais ça";
        }
    }
    else{}
        *currentTortue=_tortue2;
    */




