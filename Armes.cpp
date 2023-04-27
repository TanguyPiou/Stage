#include "Armes.hpp"

Armes::Armes(std::string nom, float degat, float crit, float portee, float endurance)
    :_nom(nom), _degat(degat), _crit(crit), _portee(portee), _endurance(endurance){}

float Armes::degat()
{
    return _degat;
};

