#include "Arene.hpp"
#include "./ui_Arene.h"

Arene::Arene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Arene), _tortue1("Avion",10,30,Armes("Base",30,0.20,0.2,0.1),0),
      _tortue2("HYRAVION",0,0,Armes("Base",30,0.20,0.2,0.1),1)
{
    ui->setupUi(this);
    init();
}

Arene::~Arene()
{
    delete ui;
}

void Arene::init()
{

   // std::string nomT1="Tortue 1", nomT2="Tortue 2";
    //int pvT1=500, pvT2=500, peT1=150, peT2=150;

    std::string map[]= {"P","P","M","M","M",
                        "M","M","M","P","P",
                        "P","M","P","M","P",
                        "P","M","P","M","P",
                        "P","M","P","M","P"};
   for (auto i : map){
     if(i=="P")
         _map.push_back(Tuile::plaine);
     else
         _map.push_back(Tuile::mur);
   }
    _tailleMap=5;

    //Armes arme1("Base",30,0.20,0.2,0.1);

    //this->map=map

    ui->T1->setText(QString::fromStdString(_tortue1.nom())+"\n"+QString::number(_tortue1.PV())
                    +"\n"+QString::number(_tortue1.PE())+"\n");
    ui->T2->setText(QString::fromStdString(_tortue2.nom())+"\n"+QString::number(_tortue2.PV())
                    +"\n"+QString::number(_tortue2.PE())+"\n");
    ui->Map->setText("On verra plus tard");


}

std::vector<int> Arene::tuileAccessible(Tortue tortue){

    // mise en place d'une variable pour simuler le déplacement de la tortue
    int currentTuile=tortue.pos();
    float currentEndu=tortue.PE();
    bool mur=false;

    std::vector<int> listeAccessible;


    //_tailleMap?



    //Déplacement à droite tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (currentTuile/_tailleMap != 0 and currentEndu!=0 and mur==false)
    {
        currentTuile++;
        if (_map[currentTuile]==Tuile::plaine){
            listeAccessible.push_back(currentTuile);
            currentEndu--;
            }
        else
            mur=true;
    }

    //Reviens à la place initiale
    currentTuile=tortue.pos();
    currentEndu=tortue.PE();
    mur=false;

    //Déplacement à gauche tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (currentTuile/_tailleMap != 0 and currentEndu!=0 and mur==false)
    {
        currentTuile--;
        if (Arene::_map[currentTuile]==Tuile::plaine){
            listeAccessible.push_back(currentTuile);
            currentEndu--;
            }
        else
            mur=true;
    }

    //Reviens à la place initiale
    currentTuile=tortue.pos();
    currentEndu=tortue.PE();
    mur=false;

    //Déplacement vers le haut tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (currentTuile>=0 and currentEndu!=0 and mur==false)
    {
        //Avancement virtuel de la tortue
        currentTuile=currentTuile-_tailleMap;
        //Engistrement de la position coutant de l'endu
        if (Arene::_map[currentTuile]==Tuile::plaine){
            listeAccessible.push_back(currentTuile);
            currentEndu--;
            }
        else
            mur=true;
    }

    currentTuile=tortue.pos();
    currentEndu=tortue.PE();
    mur=false;

    //Déplacement vers le bas tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (currentTuile <= static_cast<int>(Arene::_map.size()) and currentEndu!=0 and mur==false)
    {
        currentTuile=currentTuile+_tailleMap;
        if (Arene::_map[currentTuile]==Tuile::plaine){
            listeAccessible.push_back(currentTuile);
            currentEndu--;
            }
        else
            mur=true;
    }
    return listeAccessible;
}





