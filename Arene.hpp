#pragma once
#include "Tortue.hpp"
#include "Joueur.hpp"
#include "IAleatoire.hpp"
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

//Partie C++///

    //Fonction de Gestion de la Partie//

    void jeu();
    bool finPartie() const;

    //Fonction de base//

    std::vector<int> positionDesTortues();
    std::vector<int> listeDesPositionsTortues()const;
    bool presenceDUneTortue(int position) const;
    bool tuileLibre(int tuileVoulu) const;
    Tortue * trouveLaTortue(int position);
    int numeroDeLaTortue(Tortue *tortue);
    bool laTortueEstEnVie (Tortue *tortue) const;

    //Fonction utile pour toutes les actions//

    std::string directionAction(Tortue *tortue, int tuileVoulu) const;
    int distanceAction (Tortue *tortue, int positionVoulu)const;

    //Fonction permettant de se déplacer//

    std::vector<int> listeMouvementsPossibles(Tortue *tortue) const;
    void deplacerTortue(Tortue *tortue, int positionVoulu);

    //Fonction pour tirer//

    std::vector<int> posTortueAPorterDeTir (Tortue *tortue) const;
    void tir(Tortue *tortue, int cible);

//Fin Partie C++//

//Partie QT//
private slots:
    void on_actionloadmap_triggered();
    void on_actionclose_triggered();


private:
    Ui::Arene *ui;
    std::vector<Tortue> _listeTortue;
    std::vector<Tuile> _map;
    int _tailleMap;
};
