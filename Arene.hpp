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
    Tortue tortue1();
    Tortue tortue2();
    std::vector<int> tuileAccessible(Tortue tortue);
    bool tuileDispo(int tuile);
    int coutEnduDeplacement (Tortue tortue, int positionVoulu);
    void deplacementTortue(Tortue tortue, int positionVoulu);


private:
    Ui::Arene *ui;
    Tortue _tortue1;
    Tortue _tortue2;
    bool _tour;
    std::vector<Tuile> _map;
    int _tailleMap;
};



