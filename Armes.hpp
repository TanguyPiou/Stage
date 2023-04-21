#pragma once
#include <string>


class Armes {
public:

Armes(std::string nom, float degat, float crit, float portee, float endurance);


private :
    std::string _nom;
    float _degat;
    float _crit;
    float _portee;
    float _endurance;
};

