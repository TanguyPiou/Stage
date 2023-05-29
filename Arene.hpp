#pragma once
#include "Tortue.hpp"
#include <vector>
#include <QMainWindow>
#include <iostream>
#include <fstream>





class Arene
{


public:
    enum class Tuile {plaine,mur};
    enum class typeAction{deplacement,tir};

    struct infoAction
    {
        int identifiant;
        typeAction typedAction;
        int positionAction;
    };
    Arene(std::string fileName);
    Arene(std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map,int tailleMap);
    Arene(std::vector<Tortue> listeDesTortues, std::string map);
    Arene();

    ~Arene();

    void loadmap(std::string fileName);
    void printmap();

//Partie C++///


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

    //get
    int getTailleMap() const;
    std::vector<Tuile> getMap() const;

//Fin Partie C++//




private:
    std::vector<Tortue> _listeTortue;
    std::vector<Tuile> _map;
    int _tailleMap;
    //Qui sera surement mis autre part
    std::vector<std::vector<infoAction>> _historiquePartie;

};
