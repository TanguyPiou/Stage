#pragma once
#include "Tortue.hpp"
#include <vector>
#include <QMainWindow>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class Arene; }
QT_END_NAMESPACE




class Arene : public QMainWindow
{
    Q_OBJECT

public:
    Arene(QWidget *parent = nullptr);
    ~Arene();

    enum class Tuile {plaine,mur};
    void init();
    int tailleMap();
    Tortue *tortue1();
    Tortue *tortue2();
    std::vector<int> tuileAccessible(Tortue *tortue) const;
    std::vector<int> mouvementPossible(Tortue *tortue) const;
    bool tuileDispo(int tuileVoulu) const;
    int distanceAction (Tortue *tortue, int positionVoulu)const;
    void deplacementTortue(Tortue *tortue, int positionVoulu);
    bool presenceTortue(int position) const;
    void tir(Tortue *tortue, int cible);
    Tortue * trouveTortue(int position);
    bool tortueEnVie (Tortue *tortue) const;
    bool finPartie() const;

    void jeu();


private:
    Ui::Arene *ui;
    std::vector<Tortue> _listeTortue;
    //A enlevé quand on pourra créer des tortues au début du jeu
    //Créé fonction accéder tortue
    Tortue _tortue1;
    Tortue _tortue2;
    // BESOIN ???????S
    int _tour;
    std::vector<Tuile> _map;
    int _tailleMap;
};



