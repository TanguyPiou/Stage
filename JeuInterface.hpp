#pragma once
#include "Arene.hpp"
#include "IA.hpp"
#include "IAleatoire.hpp"
#include "Joueur.hpp"

class JeuInterface
{
public:

    JeuInterface();
    void jeu();
    int tourTortue();

private:
    int _tourTortue;
    bool _peutTirer;
};
