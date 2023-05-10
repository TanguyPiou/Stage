#include "Arene.hpp"
#include "./ui_Arene.h"


//Partie QT
Arene::Arene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Arene)
{
    ui->setupUi(this);
    init();
}

Arene::~Arene()
{
    delete ui;
}

void Arene::setAreneVirtuel(std::vector<Tortue> listeDesTortues, std::vector<Tuile> map, int tailleMap)
{
    for (std::size_t n=0;n<_listeTortue.size() ;++n )
    {
            _listeTortue[n].setPE(listeDesTortues[n].PE());
            _listeTortue[n].setPV(listeDesTortues[n].PV());
            _listeTortue[n].setDegats(listeDesTortues[n].degats());
            _listeTortue[n].setPos(listeDesTortues[n].pos());
    }
    _map=map;
    _tailleMap=tailleMap;
}

void Arene::init()
{
    _listeTortue.push_back(Tortue ("Avion",10,3,8,0));
    _listeTortue.push_back(Tortue ("HYRAVION",8,3,10,24));


    for (std::size_t i=0; i<_listeTortue.size(); i++){

        ui->T1->setText(ui->T1->text()+QString::fromStdString(_listeTortue[i].nom())+"\nPoints de vie: "+QString::number(_listeTortue[i].PV())+"\nEndurance: "+QString::number(_listeTortue[i].PE())+"\n");
    }


    loadmap(":/maps/maps/default");
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


//Partie C++//

//Fonction de Gestion de la Partie//




bool Arene::finPartie() const
{
    int tortueVivante=0;
    for (auto i : _listeTortue)
    {
        if (laTortueEstEnVie(&i))
            tortueVivante++;
    }
    if (tortueVivante>1)
        return false;
    else
        return true;

}

void Arene::afficheMap()
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
    std::cout<<m;
}



//Fonction Basique//

std::vector<int> Arene::listeDesPositionsTortues() const
{
    std::vector<int> posTortue;
    for (auto i : _listeTortue)
    {
            posTortue.push_back(i.pos());
    }
    return posTortue;
}
bool Arene::presenceDUneTortue(int position) const
{
    bool ret=false;
    for (auto i : _listeTortue){
        if(i.pos()==position)
                ret=true;
    }
    return ret;
}

bool Arene::tuileLibre(int tuileVoulu) const
{
    //On vérifie d'abord que la tuile demandé ne dépasse pas les limites de la map
    if (tuileVoulu<0 or static_cast<int>(_map.size())<=tuileVoulu)
        return false;
    //Puis on vérifie que la tuile n'est pas une tuile bloquante
    else if (_map[tuileVoulu]==Tuile::mur)
        return false;
    //Ensuite que la tuile n'est pas déjà occupé par une tortue
    else if (presenceDUneTortue(tuileVoulu))
        return false;
    //Enfin si la case est accessible
    else
        return true;

}

Tortue * Arene::trouveLaTortuePosition(int position)
{
    Tortue * tortueTrouver;
    for (std::size_t i=0; i<_listeTortue.size();++i){
        if(_listeTortue[i].pos()==position)
                tortueTrouver=&_listeTortue[i];
    }
    return tortueTrouver;
}

Tortue *Arene::trouveLaTortueID(int ID)
{
    return &_listeTortue[ID];
}

int Arene::tailleListeTortue()
{
    return _listeTortue.size();
}

std::vector<Tortue> Arene::listeTortue()
{
    return _listeTortue;
}

std::vector<Arene::Tuile> Arene::map()
{
    return _map;
}

int Arene::tailleDeLaMap()
{
    return _tailleMap;
}



int Arene::numeroDeLaTortue(Tortue *tortue)
{
    int n=1;
    for (std::size_t i=0; i<_listeTortue.size();++i)
    {
         if(tortue->pos()==_listeTortue[i].pos())
             n=i;
    }
    return n;
}

bool Arene::laTortueEstEnVie(Tortue *tortue) const
{
    if (tortue->PV()>0)
        return true;
    else
        return false;
}



//Fonction utile pour toutes les actions//


std::string Arene::directionAction(Tortue *tortue,int tuileVoulu) const
{
    int currentTortue = tortue->pos();
    if (tuileVoulu < currentTortue)
    {
        if(currentTortue/_tailleMap==tuileVoulu/_tailleMap)
        {
            return "Gauche";
        }
        else if (tuileVoulu%_tailleMap == currentTortue%_tailleMap)
        {
            return "Haut";
        }
        else
            return "Pas dans les axes de la tortue (inf)";
    }
    else if (tuileVoulu > currentTortue)
    {
        if (currentTortue/_tailleMap==tuileVoulu/_tailleMap)
        {
            return "Droite";
        }
        else if (tuileVoulu%_tailleMap == currentTortue%_tailleMap)
        {
            return "Bas";
        }
        else
            return "Pas dans les axes de la tortue (sup)";
    }
    else
        return "Pas dans les axes de la tortue";
}

int Arene::distanceAction(Tortue *tortue, int tuileVoulu) const
{
    //Vérification de qu'elle déplacement il s'agit (Haut,Bas,Droite,Gauche) pour faire le bon calcul
    //Cette fonction ne marche que sur les déplacements de tortue vérifié
    //Dans un premier temps si la tuile voulu est avant la position de la tortue c'est un mouvement soit Haut soit Gauche

    std::string direc=directionAction(tortue,tuileVoulu);

        //Dans un deuxième temps on regarde si la distance
        //entre les deux tuiles est inférieur à la taille en longueur de la map
        //Si oui c'est un mouvement à Gauche on retourne la distance entre la tortue et la tuile voulu
     if (direc=="Gauche")
            return tortue->pos()-tuileVoulu;
        //Sinon c'est un mouvement vers le haut
        //On retourne le quotient de divison entre la distance de la tortue et la tuile voulu et la taille de la map
     else if (direc=="Haut")
             return (tortue->pos()-tuileVoulu)/_tailleMap;

    //Sinon c'est un mouvement vers le Bas ou vers la droite
    else if (direc=="Droite")
       return tuileVoulu-tortue->pos();

    else
        return (tuileVoulu-tortue->pos())/_tailleMap;
}







//Fonction permettant de se déplacer//

std::vector<int> Arene::listeMouvementsPossibles(Tortue *tortue) const
{

    // Mise en place d'une variable pour simuler le déplacement de la tortue
    // On commence par la droite
    int currentTuile=tortue->pos()+1;

    std::vector<int> listeAccessible;
    //Déplacement à droite tant que on n'arrive pas à un bord droit de la map et que la tuile est accessible pour la tortue
    while (currentTuile%_tailleMap != 0 and tuileLibre(currentTuile) and distanceAction(tortue, currentTuile)<=tortue->PE())
    {
        //Ajout dans le vecteur de la position vérifié
        listeAccessible.push_back(currentTuile);
        //Vérification de la tuile suivante à droite
        currentTuile++;
    }

    //Puis on va à gauche de la position de la tortue de base
    currentTuile=tortue->pos()-1;

    //Déplacement à gauche tant que on n'arrive pas à un bord gauche de la map et que la tuile est accessible pour la tortue
    while ((currentTuile+1)%_tailleMap != 0 and tuileLibre(currentTuile) and distanceAction(tortue, currentTuile)<=tortue->PE())
    {
        //Ajout dans le vecteur de la position vérifié
        listeAccessible.push_back(currentTuile);
        //Vérification de la tuile suivante à gauche
        currentTuile--;
    }

    //Ensuite on va au dessus de la case où est la tortue de base
    currentTuile=tortue->pos()-_tailleMap;

    //Déplacement vers le haut tant que la tuile est accessible pour la tortue
    while (tuileLibre(currentTuile) and distanceAction(tortue, currentTuile)<=tortue->PE())
    {
        //Ajout dans le vecteur de la position vérifié
        listeAccessible.push_back(currentTuile);
        //Tuile suivante au dessus
        currentTuile=currentTuile-_tailleMap;
    }

    //Ensuite on va en dessous de la case où est la tortue de base
    currentTuile=tortue->pos()+_tailleMap;

    //Déplacement vers le bas tant que la tuile est accessible pour la tortue
    while (tuileLibre(currentTuile) and distanceAction(tortue, currentTuile)<=tortue->PE())
    {
        //Ajout dans le vecteur de la position vérifié
        listeAccessible.push_back(currentTuile);
        //Vérification de la tuile suivante en dessous
        currentTuile=currentTuile+_tailleMap;
    }
    /*TEST MOUVEMENT POSSIBLE
    std::cout<<"Mouvement possible : ";
    for (auto i : listeAccessible)
    {
        std::cout<<i<<"|";
    }
    std::cout<<std::endl;
    // FIN TEST*/
    return listeAccessible;

}

void Arene::deplacerTortue(Tortue *tortue, int positionVoulu)
{
    //On récupère le vecteur de déplacement possible
    std::vector<int> m=listeMouvementsPossibles(tortue);
    //Si la position voulu appartient au vecteur m alors on bouge la tortue
    //et on modifie son endurance en fonction du cout en endurance que demande le mouvement
    if (std::count(m.begin(), m.end(), positionVoulu)){
            tortue->setPE(tortue->PE()-distanceAction(tortue,positionVoulu));
            tortue->setPos(positionVoulu);
            //std::cout<<"Le déplacement est fait";
    }
    //Sinon le déplacement n'est pas fait et renvoie un message d'erreur
    else
        std::cout<<"Le déplacement est impossible";
    // TEST MOUVEMENT
    //std::cout<<'\n'<<"Position de la tortue :"<<tortue.pos();
    //std::cout<<'\n'<<"Endurance de la tortue :"<<tortue.PE();
    // FIN TEST
}



//Fonction Permettant de Tirer//

std::vector<int> Arene::posTortueAPorterDeTir(Tortue *tortue) const
{
    int currentTortue = tortue->pos();
    int deplacementVirtuel;
    bool toucher=false;

    std::vector<int> tortueTirable;
    for(auto tortueCibler : listeDesPositionsTortues())
    {
        std::string direc=directionAction(tortue,tortueCibler);
        if (direc=="Gauche")
        {
            deplacementVirtuel=currentTortue-1;
            if (deplacementVirtuel==tortueCibler)
                toucher=true;
            else
            {
                while (toucher==false and tuileLibre(deplacementVirtuel))
                {
                    deplacementVirtuel=deplacementVirtuel-1;
                    if (deplacementVirtuel==tortueCibler)
                    {
                        toucher=true;
                    }
                }
            }
            if(toucher)
            {
                tortueTirable.push_back(tortueCibler);
            }
        }
        else if (direc=="Haut")
        {
            deplacementVirtuel=currentTortue-_tailleMap;
            if (deplacementVirtuel==tortueCibler)
                toucher=true;
            else
            {
                while (toucher==false and tuileLibre(deplacementVirtuel))
                {
                    deplacementVirtuel=deplacementVirtuel-_tailleMap;
                    if (deplacementVirtuel==tortueCibler)
                        toucher=true;
                }
            }
            if(toucher)
                tortueTirable.push_back(tortueCibler);

        }
        else if (direc=="Droite")
        {
            deplacementVirtuel=currentTortue+1;
            if (deplacementVirtuel==tortueCibler)
                toucher=true;
            else
            {
                while (toucher==false and tuileLibre(deplacementVirtuel))
                {
                    deplacementVirtuel=deplacementVirtuel+1;
                    if (deplacementVirtuel==tortueCibler)
                        toucher=true;
                }
            }
            if(toucher)
                tortueTirable.push_back(tortueCibler);
        }
        else if (direc=="Bas")
        {
            deplacementVirtuel=currentTortue+_tailleMap;
            if (deplacementVirtuel==tortueCibler)
                toucher=true;
            else
            {
                while (toucher==false and tuileLibre(deplacementVirtuel))
                {
                    deplacementVirtuel=deplacementVirtuel+_tailleMap;
                    if (deplacementVirtuel==tortueCibler)
                        toucher=true;
                }
            }
            if(toucher)
                tortueTirable.push_back(tortueCibler);
        }
        toucher=false;
    }
    return tortueTirable;
}


void Arene::tir(Tortue *tortue, int cible)
{
   std::vector<int> v=posTortueAPorterDeTir(tortue);
   Tortue * tortueCibler;
   /*TEST Tir Possible
   std::cout<<"Tir Possible : ";
   for (auto i : v)
   {
       std::cout<<i<<"|";
   }
   std::cout<<std::endl;
   // FIN TEST*/
   if (std::count(v.begin(), v.end(), cible)){
            //std::cout<<trouveLaTortuePosition(cible)->PV()<<std::endl;
            tortueCibler=trouveLaTortuePosition(cible);
            tortueCibler->setPV(tortueCibler->PV()-tortue->degats());
            tortue->setPE(tortue->PE()-1);
            //std::cout<<"Tir effectuer"<<trouveLaTortuePosition(cible)->PV()<<std::endl;
   }
}

//Partie QT //


void Arene::on_actionloadmap_triggered()
{
    QString fileName= QFileDialog::getOpenFileName(this, "Load Map", "../Tortue/maps");

    if (fileName.isEmpty())
        return;
    else loadmap(fileName);

    for (std::size_t i=0; i<_listeTortue.size(); i++){

        ui->T1->setText(ui->T1->text()+QString::fromStdString(_listeTortue[i].nom())+"\nPoints de vie: "+QString::number(_listeTortue[i].PV())+"\nEndurance: "+QString::number(_listeTortue[i].PE())+"\n");
    }
    printmap();
}

void Arene::on_actionclose_triggered()
{
    this->close();
}
