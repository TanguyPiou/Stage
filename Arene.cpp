#include "Arene.hpp"
#include "./ui_Arene.h"

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

void Arene::init()
{
    loadmap(":/maps/maps/default");
    initmap();

    //Creation tortues
    int nbplayer=2;  //SETTINGS
    for(int i=0; i<nbplayer; i++){
        _listeTortue.push_back(Tortue ("Tortue"+std::to_string(i+1),10,3,10,_listePosSpawn[i]));
    }
    updatePosTortues();

    //affichage info
    for (std::size_t i=0; i<_listeTortue.size(); i++){
        ui->T1->setText(ui->T1->text()+QString::fromStdString(_listeTortue[i].nom())+"\nPoints de vie: "+QString::number(_listeTortue[i].PV())+"\nEndurance: "+QString::number(_listeTortue[i].PE())+"\nPosition: "+QString::number(_listeTortue[i].pos())+"\n\n");
    }
    printmap();
    //affichage info




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
    int pos=0;
    //Parcours du fichier
    while(!in.atEnd()){
        QString ligne = in.readLine();
        taille++;
        for(auto i : ligne){
            if(i=='M'){
                map.push_back(Tuile::mur);
                pos++;
            }
            else if(i=='P'){
                map.push_back(Tuile::plaine);
                pos++;
            }
            else if(i=='S'){
                map.push_back(Tuile::plaine);
                _listePosSpawn.push_back(pos);
                pos++;
            }
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

void Arene::initmap()
{
    //Nouvelle scene si besoin
    if(!ui->graphicsView->scene()){
        QGraphicsScene *scene= new QGraphicsScene;
        ui->graphicsView->setScene(scene);
    }

    //Taille d'une image (à mettre dans settings plus tard j'imagine)
    int t=64;
    ui->graphicsView->setMinimumSize(t*_tailleMap+_tailleMap,t*_tailleMap+_tailleMap);
    ui->graphicsView->setMaximumSize(t*_tailleMap+_tailleMap,t*_tailleMap+_tailleMap);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Création des images
    QPixmap imgMur= QPixmap(":/images/img/mur.jpg").scaled(t,t);
    QPixmap imgBG= QPixmap(":/images/img/bg.png").scaled(t*_tailleMap,t*_tailleMap);

    //Ajout de l'image de fond
    QGraphicsPixmapItem *background= new QGraphicsPixmapItem;
    background->setPixmap(imgBG);
    background->setPos(0,0);
    ui->graphicsView->scene()->addItem(background);

    //Ajout des murs
    for(std::size_t i=0; i<_map.size(); i++){
        if(_map[i]==Tuile::mur){
            QGraphicsPixmapItem *mur= new QGraphicsPixmapItem;
            mur->setPixmap(imgMur);
            mur->setPos(i%_tailleMap*t,i/_tailleMap*t);
            ui->graphicsView->scene()->addItem(mur);
        }
    }
}

void Arene::updatePosTortues()
{
    int t=64; //settings
    QPixmap imgTortue= QPixmap(":/images/img/tortue.png").scaled(t,t);

    for(auto i : listePositionTortue()){
        QGraphicsPixmapItem *tortue= new QGraphicsPixmapItem;
        tortue->setPixmap(imgTortue);
        tortue->setPos(i%_tailleMap*t,i/_tailleMap*t);
        ui->graphicsView->scene()->addItem(tortue);
    }
}

std::vector<int> Arene::tuileAccessible(Tortue *tortue) const{

    // Mise en place d'une variable pour simuler le déplacement de la tortue
    // On commence par la droite
    bool tir=tortue->tir();
    int currentTuile=tortue->pos()+1;

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
    currentTuile=tortue->pos()-1;

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
    currentTuile=tortue->pos()-_tailleMap;


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
    currentTuile=tortue->pos()+_tailleMap;

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

std::vector<int> Arene::mouvementPossible(Tortue *tortue) const
{
    std::vector<int> transi=tuileAccessible(tortue);
    std::vector<int> mP;
    for (auto i : transi){
            if (distanceAction(tortue, i)<=tortue->PE())
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

bool Arene::tuileDispo(int tuileVoulu) const
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

int Arene::distanceAction(Tortue *tortue, int tuileVoulu) const
{
    //Vérification de qu'elle déplacement il s'agit (Haut,Bas,Droite,Gauche) pour faire le bon calcul
    //Cette fonction ne marche que sur les déplacements de tortue vérifié
    //Dans un premier temps si la tuile voulu est avant la position de la tortue c'est un mouvement soit Haut soit Gauche
    if (tuileVoulu < tortue->pos()){
        int distance=tortue->pos()-tuileVoulu;
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
        int distance=tuileVoulu-tortue->pos();
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

void Arene::deplacementTortue(Tortue *tortue, int positionVoulu)
{
    //On récupère le vecteur de déplacement possible
    std::vector<int> m=mouvementPossible(tortue);
    //Si la position voulu appartient au vecteur m alors on bouge la tortue
    //et on modifie son endurance en fonction du cout en endurance que demande le mouvement
    if (std::count(m.begin(), m.end(), positionVoulu)){
            tortue->setPE(tortue->PE()-distanceAction(tortue,positionVoulu));
            tortue->setPos(positionVoulu);
            std::cout<<"Le déplacement est fait ???";
    }
    //Sinon le déplacement n'est pas fait et renvoie un message d'erreur
    else
        std::cout<<"Le déplacement est impossible";
    // TEST MOUVEMENT
    //std::cout<<'\n'<<"Position de la tortue :"<<tortue.pos();
    //std::cout<<'\n'<<"Endurance de la tortue :"<<tortue.PE();
    // FIN TEST
}

bool Arene::presenceTortue(int position) const
{
    bool ret=false;
    for (auto i : _listeTortue){
        if(i.pos()==position)
                ret=true;
    }
    return ret;
}

void Arene::tir(Tortue *tortue, int cible)
{

   tortue->setTir(true);
   std::vector<int> v=tuileAccessible(tortue);
   if (std::count(v.begin(), v.end(), cible)){
            std::cout<<trouveTortue(cible)->PV()<<std::endl;
            trouveTortue(cible)->setPV(trouveTortue(cible)->PV()-tortue->degats());
            std::cout<<"Tir effectuer"<<trouveTortue(cible)->PV()<<std::endl;
   }
   tortue->setTir(false);
}

std::vector<int> Arene::positionTortue()
{
    std::vector<int> posTortue;
    for (int i=0; i<static_cast<int>(_listeTortue.size());++i)
    {
        posTortue.push_back(_listeTortue[i].pos());
    }
    return posTortue;
}

Tortue * Arene::trouveTortue(int position)
{
    Tortue * tortueTrouver;
    for (int i=0; i<static_cast<int>(_listeTortue.size());++i){
        if(_listeTortue[i].pos()==position)
                tortueTrouver=&_listeTortue[i];
    }
    return tortueTrouver;
}

bool Arene::tortueEnVie(Tortue *tortue) const
{
    if (tortue->PV()>0)
        return true;
    else
        return false;
}

bool Arene::finPartie() const
{
    int tortueVivante=0;
    for (auto i : _listeTortue)
    {
        if (tortueEnVie(&i))
            tortueVivante++;
    }
    if (tortueVivante>1)
        return false;
    else
        return true;

}

std::vector<int> Arene::listePositionTortue() const
{
    std::vector<int> posTortue;
    for (auto i : _listeTortue){
        posTortue.push_back(i.pos());
    }
    return posTortue;
}

void Arene::jeu()
{


    std::string reponse;
    Tortue * tortue;
    int n;

    int tourTortue=0;

    while(not finPartie())
    {
        tortue=&_listeTortue[tourTortue];
        int enduMax=tortue->PE();
        bool peutTirer=true;
        bool finTour=false;
        while (tortue->PE()>0 and not finTour)
        {
            std::cout<<"Terminer le tour(y/n) ? ";
            std::cin>>reponse;
            std::cout<<std::endl;
            if (reponse!="y"){
                if (peutTirer){
                    std::cout<<"Tirer(y/n) ? ";
                    std::cin>>reponse;
                    std::cout<<std::endl;
                    if (reponse=="y"){
                        std::cout<<"Case où tirer : "<<std::endl;
                        std::cin>>n;
                        tir(tortue,n);
                        peutTirer=false;
                    }
                }
                mouvementPossible(tortue);
                std::cout<<"Case ou aller : "<<std::endl;
                std::cin>>n;
                deplacementTortue(tortue,n);
            }
            else
                finTour=true;
        }
        tortue->setPE(enduMax);
        tourTortue=(tourTortue+1)%static_cast<int>(_listeTortue.size());
        std::cout<<"Tour tortue : "<<tourTortue<<std::endl;
    }
    //victoire
}


void Arene::on_actionloadmap_triggered()
{
    QString fileName= QFileDialog::getOpenFileName(this, "Load Map", "../Tortue/maps");

    if (fileName.isEmpty())
        return;
    else{
        _listePosSpawn.clear();
        loadmap(fileName);
    }
    //Maj posSpawn
    for(std::size_t i=0; i<_listeTortue.size(); i++){
        _listeTortue[i].setPos(_listePosSpawn[i]);
    }

    //affichage info maj
    ui->T1->clear();
    for (std::size_t i=0; i<_listeTortue.size(); i++){
        ui->T1->setText(ui->T1->text()+QString::fromStdString(_listeTortue[i].nom())+"\nPoints de vie: "+QString::number(_listeTortue[i].PV())+"\nEndurance: "+QString::number(_listeTortue[i].PE())+"\nPosition: "+QString::number(_listeTortue[i].pos())+"\n\n");
    }
    printmap();
    //affichage info maj

    //Maj scene
    ui->graphicsView->scene()->clear();
    initmap();
    updatePosTortues();
}

void Arene::on_actionclose_triggered()
{
    this->close();
}
