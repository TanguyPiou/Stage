#include "Arene.hpp"
#include "./ui_Arene.h"

Arene::Arene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Arene), _tortue1("Avion",10,30,Armes("Base",30,0.20,0.2,0.1),0),
      _tortue2("HYRAVION",0,0,Armes("Base",30,0.20,0.2,0.1),1)
{
    ui->setupUi(this);
    init();
    printmap();
}

Arene::~Arene()
{
    delete ui;
}

void Arene::init()
{

    initmap();

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

void Arene::initmap()
{

    QString fileName= QFileDialog::getOpenFileName(this, "Load Map", "../Tortue/maps");

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
            return;
        }

        QTextStream in(&file);

        std::vector<Tuile> map;
        int taille=0;
        //Parcours du fichier
        while(!in.atEnd()){
            QString ligne = in.readLine();
            taille++;
            for(auto i : ligne){
                if(i=='M') map.push_back(Tuile::mur);
                else map.push_back(Tuile::plaine);
            }
        }

        _map=map;
        _tailleMap=taille;
    }
}

void Arene::printmap()
{
    std::string m="";
    int cpt=0;
    for(auto i: _map){
        if(i==Tuile::mur) m+="M ";
        else if(i==Tuile::plaine) m+="P ";
        else m+="?";
        cpt++;
        if(cpt==_tailleMap){
            m+="\n";
            cpt=0;
        }
    }
    ui->Map->setText(QString::fromStdString(m));
}





