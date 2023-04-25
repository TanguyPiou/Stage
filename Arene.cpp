#include "Arene.hpp"
#include "./ui_Arene.h"

Arene::Arene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Arene), _tortue1("Avion",10,3,Armes("Base",30,0.20,0.2,0.1),24),
      _tortue2("HYRAVION",10,0,Armes("Base",30,0.20,0.2,0.1),21)
{
    ui->setupUi(this);
    init();
}

Arene::~Arene()
{
    delete ui;
}

Tortue Arene::tortue1()
{
    return _tortue1;
}

Tortue Arene::tortue2()
{
    return _tortue2;
}

void Arene::init()
{

   // std::string nomT1="Tortue 1", nomT2="Tortue 2";
    //int pvT1=500, pvT2=500, peT1=150, peT2=150;

    std::string map[]= {"P","P","P","P","P",
                        "P","P","M","P","P",
                        "P","P","P","M","P",
                        "P","M","P","M","P",
                        "P","M","P","P","P"};
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

    // Mise en place d'une variable pour simuler le déplacement de la tortue
    // On commence par la droite
    int currentTuile=tortue.pos()+1;

    std::vector<int> listeAccessible;

    //Déplacement à droite tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (currentTuile%_tailleMap != 0 and tuileDispo(tortue,currentTuile))
    {
        listeAccessible.push_back(currentTuile);
        currentTuile++;
    }

    //Reviens à la place initiale
    currentTuile=tortue.pos()-1;


    //Déplacement à gauche tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while ((currentTuile+1)%_tailleMap != 0 and tuileDispo(tortue,currentTuile))
    {
        listeAccessible.push_back(currentTuile);
        currentTuile--;
    }

    //Reviens à la place initiale
    currentTuile=tortue.pos()-_tailleMap;


    //Déplacement vers le haut tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (tuileDispo(tortue,currentTuile))
    {
        listeAccessible.push_back(currentTuile);
        currentTuile=currentTuile-_tailleMap;
    }

    currentTuile=tortue.pos()+_tailleMap;

    //Déplacement vers le bas tant qu'on arrive pas au bord de la map et que l'endurance n'est pas à zéro
    //et qu'on a pas rencontré un mur
    while (tuileDispo(tortue,currentTuile))
    {
        listeAccessible.push_back(currentTuile);
        currentTuile=currentTuile+_tailleMap;
    }
    for (auto i : listeAccessible)
    {
        std::cout<<i<<"|";
    }
    return listeAccessible;
}

bool Arene::tuileDispo(Tortue tortue,int tuileVoulu)
{
    if (tuileVoulu<0 or static_cast<int>(_map.size())<=tuileVoulu)
        return false;
    else if (_map[tuileVoulu]==Tuile::mur)
        return false;
    else if (_tortue1.pos()==tuileVoulu and _tortue2.pos()==tuileVoulu)
        return false;
    else if (coutEnduDeplacement(tortue, tuileVoulu)<=tortue.PE())
        return true;
    else
        return false;
}

int Arene::coutEnduDeplacement(Tortue tortue, int tuileVoulu)
{
    if (tuileVoulu < tortue.pos()){
        if ((tortue.pos()-tuileVoulu)<_tailleMap)
            return tortue.pos()-tuileVoulu;
        else
             return (tortue.pos()-tuileVoulu)/_tailleMap;
    }
    else {
        if ((tuileVoulu-tortue.pos())<_tailleMap)
            return tuileVoulu-tortue.pos();
        else
             return (tuileVoulu-tortue.pos())/_tailleMap;

    }
}

void Arene::deplacementTortue(Tortue tortue, int positionVoulu)
{
    std::vector<int> m=tuileAccessible(tortue);
    if (std::count(m.begin(), m.end(), positionVoulu)){
        tortue.setPE(tortue.PE()-coutEnduDeplacement(tortue,positionVoulu));
        tortue.setPos(positionVoulu);
    }
    else
        std::cout<<"Le déplacement est impossible";
    // TEST MOUVEMENT
    //std::cout<<'\n'<<"Position de la tortue :"<<tortue.pos();
    //std::cout<<'\n'<<"Endurance de la tortue :"<<tortue.PE();
    // FIN TEST
}





