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
    enum class typeAction{deplacement,tir};

    struct infoAction
    {
        int identifiant;
        typeAction typedAction;
        int positionAction;
    };

    void init();
    void loadmap(const QString & fileName);
    void printmap();

//Partie C++///

    //Fonction qui actualise l'arène virtuel avec celle de l'arène principal
    //A revoir
    void setAreneVirtuel(std::vector<Tortue> listeDesTortues, std::vector<Tuile> map, int tailleMap);

    //Fonction d'affichage c++//

    void afficheMap();
    Tortue * vainqueur();

    //Accesseur//

    std::vector<Tortue> listeTortue();
    std::vector<Tuile> map();
    int tailleDeLaMap();

    //Fonction d'information basique//

    int tailleListeTortue();
    int numeroDeLaTortue(Tortue *tortue);
    Tortue * trouveLaTortuePosition(int position);
    Tortue * trouveLaTortueID(int ID);
    std::vector<int> listeDesPositionsTortues()const;

    //Fonction de vérification//

    bool presenceDUneTortue(int position) const;
    bool tuileLibre(int tuileVoulu) const;
    bool laTortueEstEnVie (Tortue *tortue) const;
    bool finPartie() const;

    //Fonction utile pour toutes les actions//

    std::string directionAction(Tortue *tortue, int tuileVoulu) const;
    int distanceAction (Tortue *tortue, int positionVoulu)const;

    //Fonction permettant de se déplacer//

    std::vector<int> listeMouvementsPossibles(Tortue *tortue) const;
    void deplacerTortue(Tortue *tortue, int positionVoulu);

    //Fonction pour tirer//

    std::vector<int> posTortueAPorterDeTir (Tortue *tortue);
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
    //Qui sera surement mis autre part
    std::vector<std::vector<infoAction>> _historiquePartie;

};
