#include "Arene.hpp"
#include "./ui_Arene.h"

Arene::Arene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Arene), _tortue1("Avion",10,3,Armes("Base",2,0.20,0.2,0.1),24),
      _tortue2("HYRAVION",8,0,Armes("Base",30,0.20,0.2,0.1),21)
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
    loadmap(":/maps/maps/default");
    ui->T1->setText(QString::fromStdString(_tortue1.nom())+"\n"+QString::number(_tortue1.PV())
                    +"\n"+QString::number(_tortue1.PE())+"\n");
    ui->T2->setText(QString::fromStdString(_tortue2.nom())+"\n"+QString::number(_tortue2.PV())
                    +"\n"+QString::number(_tortue2.PE())+"\n");
    printmap();

}

void Arene::loadmap(const QString & fileName)
{

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
    file.close();

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
std::vector<int> Arene::tuileAccessible(Tortue tortue){

    // Mise en place d'une variable pour simuler le déplacement de la tortue
    // On commence par la droite
    bool tir=tortue.tir();
    int currentTuile=tortue.pos()+1;

    std::vector<int> listeAccessible;

    //Déplacement à droite tant que on n'arrive pas à un bord droit de la map et que la tuile est accessible pour la tortue
    while (currentTuile%_tailleMap != 0 and tuileDispo(currentTuile))
    {
        if (not tir){
            //Ajout dans le vecteur de la position vérifié
            listeAccessible.push_back(currentTuile);
        }
        //Vérification de la tuile suivante à droite
        currentTuile++;
    }

    if (tir){
        if(presenceTortue(currentTuile))
            listeAccessible.push_back(currentTuile);
    }
    //Puis on va à gauche de la position de la tortue de base
    currentTuile=tortue.pos()-1;

    //Déplacement à gauche tant que on n'arrive pas à un bord gauche de la map et que la tuile est accessible pour la tortue
    while ((currentTuile+1)%_tailleMap != 0 and tuileDispo(currentTuile))
    {
        if (not tir){
            //Ajout dans le vecteur de la position vérifié
            listeAccessible.push_back(currentTuile);
        }
        //Vérification de la tuile suivante à gauche
        currentTuile--;
    }


    if (tir){
        std::cout<<"passe";
        if(presenceTortue(currentTuile)){
            std::cout<<"passe2";
            listeAccessible.push_back(currentTuile);
        }
    }
    //Ensuite on va au dessus de la case où est la tortue de base
    currentTuile=tortue.pos()-_tailleMap;


    //Déplacement vers le haut tant que la tuile est accessible pour la tortue
    while (tuileDispo(currentTuile))
    {
        if (not tir){
            //Ajout dans le vecteur de la position vérifié
            listeAccessible.push_back(currentTuile);
        }
        //Tuile suivante au dessus
        currentTuile=currentTuile-_tailleMap;
    }

    if (tir){
        if(presenceTortue(currentTuile))
            listeAccessible.push_back(currentTuile);
    }
    //Ensuite on va en dessous de la case où est la tortue de base
    currentTuile=tortue.pos()+_tailleMap;

    //Déplacement vers le bas tant que la tuile est accessible pour la tortue
    while (tuileDispo(currentTuile))
    {
        if (not tir){
            //Ajout dans le vecteur de la position vérifié
            listeAccessible.push_back(currentTuile);
        }
        //Vérification de la tuile suivante en dessous
        currentTuile=currentTuile+_tailleMap;
    }

    if (tir){
        if(presenceTortue(currentTuile))
            listeAccessible.push_back(currentTuile);
    }

    // TEST VECTEUR RENVOYER
    std::cout<<"Tuile dispo : ";
    for (auto i : listeAccessible)
    {
        std::cout<<i<<"|";
    }
    std::cout<<std::endl;
    // FIN TEST
    return listeAccessible;

}

std::vector<int> Arene::mouvementPossible(Tortue tortue)
{
    std::vector<int> transi=tuileAccessible(tortue);
    std::vector<int> mP;
    for (auto i : transi){
            if (distanceAction(tortue, i)<=tortue.PE())
                mP.push_back(i);
    }
    //TEST MOUVEMENT POSSIBLE
    std::cout<<"Mouvement possible : ";
    for (auto i : mP)
    {
        std::cout<<i<<"|";
    }
    std::cout<<std::endl;
    // FIN TEST
    return mP;

}

bool Arene::tuileDispo(int tuileVoulu)
{
    //On vérifie d'abord que la tuile demandé ne dépasse pas les limites de la map
    if (tuileVoulu<0 or static_cast<int>(_map.size())<=tuileVoulu)
        return false;
    //Puis on vérifie que la tuile n'est pas une tuile bloquante
    else if (_map[tuileVoulu]==Tuile::mur)
        return false;
    //Ensuite que la tuile n'est pas déjà occupé par une tortue
    else if (presenceTortue(tuileVoulu))
        return false;
    //Enfin si la case est accessible
    else
        return true;

}

int Arene::distanceAction(Tortue tortue, int tuileVoulu)
{
    //Vérification de qu'elle déplacement il s'agit (Haut,Bas,Droite,Gauche) pour faire le bon calcul
    //Cette fonction ne marche que sur les déplacements de tortue vérifié
    //Dans un premier temps si la tuile voulu est avant la position de la tortue c'est un mouvement soit Haut soit Gauche
    if (tuileVoulu < tortue.pos()){
        int distance=tortue.pos()-tuileVoulu;
        //Dans un deuxième temps on regarde si la distance
        //entre les deux tuiles est inférieur à la taille en longueur de la map
        //Si oui c'est un mouvement à Gauche on retourne la distance entre la tortue et la tuile voulu
        if ((distance)<_tailleMap)
            return distance;
        //Sinon c'est un mouvement vers le haut
        //On retourne le quotient de divison entre la distance de la tortue et la tuile voulu et la taille de la map
        else
             return (distance)/_tailleMap;
    }
    //Sinon c'est un mouvement vers le Bas ou vers la droite
    else {
        int distance=tuileVoulu-tortue.pos();
        //Dans un deuxième temps on regarde si la distance
        //entre les deux tuiles est inférieur à la taille en longueur de la map
        //Si oui c'est un mouvement à Droite on retourne la distance entre la tortue et la tuile voulu
        if ((distance)<_tailleMap)
            return distance;
        //Sinon c'est un mouvement vers le haut
        //On retourne le quotient de divison entre la distance de la tortue et la tuile voulu et la taille de la map
        else
             return (distance)/_tailleMap;

    }
}

void Arene::deplacementTortue(Tortue tortue, int positionVoulu)
{
    //On récupère le vecteur de déplacement possible
    std::vector<int> m=mouvementPossible(tortue);
    //Si la position voulu appartient au vecteur m alors on bouge la tortue
    //et on modifie son endurance en fonction du cout en endurance que demande le mouvement
    if (std::count(m.begin(), m.end(), positionVoulu)){
            tortue.setPE(tortue.PE()-distanceAction(tortue,positionVoulu));
            tortue.setPos(positionVoulu);
    }
    //Sinon le déplacement n'est pas fait et renvoie un message d'erreur
    else
        std::cout<<"Le déplacement est impossible";
    // TEST MOUVEMENT
    //std::cout<<'\n'<<"Position de la tortue :"<<tortue.pos();
    //std::cout<<'\n'<<"Endurance de la tortue :"<<tortue.PE();
    // FIN TEST
}

bool Arene::presenceTortue(int position)
{
    if (_tortue1.pos()==position or _tortue2.pos()==position)
        return true;
    else
        return false;
}

void Arene::tir(Tortue tortue, int cible)
{

   tortue.setTir(true);
   std::vector<int> v=tuileAccessible(tortue);
   if (std::count(v.begin(), v.end(), cible)){
            trouveTortue(cible)->setPV(trouveTortue(cible)->PV()-tortue.arme().degat());
   }
   tortue.setTir(false);
}

Tortue * Arene::trouveTortue(int position)
{

    if (_tortue1.pos()==position)
        return &_tortue1;
    else
        return &_tortue2;
}

void Arene::on_actionloadmap_triggered()
{
    QString fileName= QFileDialog::getOpenFileName(this, "Load Map", "../Tortue/maps");

    if (fileName.isEmpty())
        return;
    else loadmap(fileName);
    ui->T1->setText(QString::fromStdString(_tortue1.nom())+"\n"+QString::number(_tortue1.PV())
                    +"\n"+QString::number(_tortue1.PE())+"\n");
    ui->T2->setText(QString::fromStdString(_tortue2.nom())+"\n"+QString::number(_tortue2.PV())
                    +"\n"+QString::number(_tortue2.PE())+"\n");
    printmap();
}

void Arene::on_actionclose_triggered()
{
    this->close();
}



