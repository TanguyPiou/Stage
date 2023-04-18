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

    //Armes arme1("Base",30,0.20,0.2,0.1);

    //this->map=map

    ui->T1->setText(QString::fromStdString(_tortue1.nom())+"\n"+QString::number(_tortue1.PV())
                    +"\n"+QString::number(_tortue1.PE())+"\n");
    ui->T2->setText(QString::fromStdString(_tortue2.nom())+"\n"+QString::number(_tortue2.PV())
                    +"\n"+QString::number(_tortue2.PE())+"\n");
    ui->Map->setText("On verra plus tard");


}

void Arene::mouvement()
{
    Tortue *currentTortue;
    int nbcase=3;
    std::string direction="droite";
    if (Arene::Tour)
    {
        *currentTortue=_tortue1;
        if (currentTortue->PE()==0)
        {
            //"pouquoi je fais ça";
        }
    }
    else{}
        *currentTortue=_tortue2;

}






