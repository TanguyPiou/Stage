#pragma once
#include "Arene.hpp"
#include "IA.hpp"
#include "IAleatoire.hpp"
#include "Joueur.hpp"
#include "formmode.hpp"
#include "formnbj.hpp"
#include "formtortue.hpp"
#include "formmap.hpp"

class JeuInterface
{
public:

    JeuInterface();
    std::string choixMapForm();
    Tortue creerTortueForm();
    Arene creerAreneFormPerso();
    Arene creerAreneForm();
    void jeu();
    int tourTortue();

private:
    int _tourTortue;
    bool _peutTirer;
    formMode _formmode;
    formNBJ _formnbj;
    formTortue _formtortue;
    formMap _formmap;
};
