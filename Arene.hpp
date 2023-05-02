#pragma once
#include "Tortue.hpp"
#include <vector>
#include <QMainWindow>
#include <iostream>

#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

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
    void loadmap(const QString & fileName);
    void printmap();
    int tailleMap();
    // A SUPPR
    Tortue *tortue1();
    Tortue *tortue2();
    // FIN SUPPR
    std::vector<int> tuileAccessible(Tortue *tortue) const;
    std::vector<int> mouvementPossible(Tortue *tortue) const;
    bool tuileDispo(int tuileVoulu) const;
    int distanceAction (Tortue *tortue, int positionVoulu)const;
    void deplacementTortue(Tortue *tortue, int positionVoulu);
    bool presenceTortue(int position) const;
    void tir(Tortue *tortue, int cible);
    std::vector<int> positionTortue();
    Tortue * trouveTortue(int position);
    bool tortueEnVie (Tortue *tortue) const;
    bool finPartie() const;

    void jeu();

private slots:
    void on_actionloadmap_triggered();
    void on_actionclose_triggered();

private:
    Ui::Arene *ui;
    std::vector<Tortue> _listeTortue;
    //A enlevé quand on pourra créer des tortues au début du jeu
    //Créé fonction accéder tortue
    std::vector<Tuile> _map;
    int _tailleMap;
};
