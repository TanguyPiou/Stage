#include "jeuaffichage.hpp"
#include "ui_jeuaffichage.h"

jeuaffichage::jeuaffichage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jeuaffichage)
{
    ui->setupUi(this);
    formMode();
    formNBJ();
    formTortue();
    formMap();
    _arene=creerAreneForm();
    initmap();
    initPosTortues();

}

jeuaffichage::~jeuaffichage()
{
    delete ui;
}


void jeuaffichage::initmap()
{
    //Nouvelle scene si besoin
    if(!ui->graphicsView->scene()){
        QGraphicsScene *scene= new QGraphicsScene;
        ui->graphicsView->setScene(scene);
    }

    std::vector<Arene::Tuile> map=_arene.getMap();
    int tailleMap=_arene.getTailleMap();
    //Taille d'une image (à mettre dans settings plus tard j'imagine)
    int t=150;
    ui->graphicsView->setMinimumSize(t*tailleMap+tailleMap,t*tailleMap+tailleMap);
    ui->graphicsView->setMaximumSize(t*tailleMap+tailleMap,t*tailleMap+tailleMap);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Création des images
    QPixmap imgMur= QPixmap(":/images/img/mur.jpg").scaled(t,t);
    QPixmap imgBG= QPixmap(":/images/img/bg.png").scaled(t*tailleMap,t*tailleMap);

    //Ajout de l'image de fond
    QGraphicsPixmapItem *background= new QGraphicsPixmapItem;
    background->setPixmap(imgBG);
    background->setPos(0,0);
    ui->graphicsView->scene()->addItem(background);

    //Ajout des murs
    for(std::size_t i=0; i<map.size(); i++){
        if(map[i]==Arene::Tuile::mur){
            QGraphicsPixmapItem *mur= new QGraphicsPixmapItem;
            mur->setPixmap(imgMur);
            mur->setPos(i%tailleMap*t,i/tailleMap*t);
            ui->graphicsView->scene()->addItem(mur);
        }
    }
}

void jeuaffichage::initPosTortues()
{
    int t=150; //settings
    QPixmap imgTortue= QPixmap(":/images/img/tortue.png").scaled(t,t);

    for(auto i : _arene.listeDesPositionsTortues()){
        QGraphicsPixmapItem *tortue= new QGraphicsPixmapItem;
        tortue->setPixmap(imgTortue);
        tortue->setPos(i%_arene.getTailleMap()*t,i/_arene.getTailleMap()*t);
        _items.push_back(tortue);
        ui->graphicsView->scene()->addItem(tortue);
    }
}

void jeuaffichage::updatePosTortue(int i)
{
    int t=150;
    QTimeLine *timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(_items[i]);
    animation->setTimeLine(timer);
    int newx=_arene.listeDesPositionsTortues()[i]%_arene.getTailleMap()*t;
    int newy=_arene.listeDesPositionsTortues()[i]/_arene.getTailleMap()*t;
    animation->setPosAt(0.1, QPointF(newx, newy));

    timer->start();


}

std::string jeuaffichage::choixMapForm()
{
    if(_formmap.exec()==QDialog::Accepted){
        int choix=_formmap.getChoix();
        switch (choix) {
            case(1):return("maps/default"); break;
            case(2):return("maps/map1"); break;
            case(3):return("maps/map2"); break;
        }
    }
    return ("maps/default");
}

Tortue jeuaffichage::creerTortueForm()
{
    _formtortue.exec();

    return Tortue(_formtortue.getNom(),_formtortue.getPV(),_formtortue.getPE(),_formtortue.getDEG(),_formtortue.getPOS());

}

Arene jeuaffichage::creerAreneFormPerso()
{
    if(_formnbj.exec()==QDialog::Accepted){
        int nbj=_formnbj.getNBJ();
        std::vector<Tortue> listeTortue;

        for(int i=0; i<nbj; i++){
            listeTortue.push_back(creerTortueForm());
        }
        std::string map=choixMapForm();

        return Arene(listeTortue, map);
    }


    return Arene("Settings/defaut.txt");
}

Arene jeuaffichage::creerAreneForm()
{
    if(_formmode.exec()==QDialog::Accepted){
        int mode=_formmode.getChoix();

        switch (mode) {
            case(1):return Arene("Settings/defaut.txt"); break;
            case(2): return creerAreneFormPerso(); break;
        }
    }
    return Arene("Settings/defaut.txt");

}

void jeuaffichage::jeu()
{
        //Arene a("../Stage-Piou/Settings/defaut.txt");
        //Arene a = creerAreneForm();


        Tortue * tortue;
        Tortue * victime;
        _tourTortue=0;
        _peutTirer=true;
        int enduMax;
        std::vector<Arene::infoAction> tour;

        IA* joueur;
        std::vector<IA*> listeJoueur;

        //Modifiable

        IAleatoire J1;
        IAleatoire J2;
        Joueur J3;


        listeJoueur.push_back(&J1);
        listeJoueur.push_back(&J2);
        listeJoueur.push_back(&J3);


        _arene.afficheMap();

        while(not _arene.finPartie())
        {
            if (_arene.laTortueEstEnVie(_arene.trouveLaTortueID(_tourTortue)))
            {
                std::cout<<"Tour tortues : "<<_tourTortue<<std::endl;
                tortue=_arene.trouveLaTortueID(_tourTortue);
                joueur=listeJoueur[_tourTortue];

                enduMax=tortue->PE();

                std::cout<<"Position des tortues : "<<std::endl;
                for (auto i : _arene.listeDesPositionsTortues())
                {
                    std::cout<<_arene.trouveLaTortuePosition(i)->nom()<<"(tortue "<<_arene.numeroDeLaTortue(_arene.trouveLaTortuePosition(i))<<") |"<<i<<"|"<<std::endl;
                }
                std::cout<<std::endl;


                tour=joueur->tour(_tourTortue, _arene.listeTortue(), _arene.map(), _arene.tailleDeLaMap());
                for(auto i : tour)
                {
                    if (i.typedAction==Arene::typeAction::deplacement)
                    {
                        _arene.deplacerTortue(tortue,i.positionAction);

                        updatePosTortue(_tourTortue);
                        std::cout<<tortue->nom()<<"(tortue "<<_arene.numeroDeLaTortue(tortue)<<") c'est déplacé sur la case "<<i.positionAction<<std::endl<<std::endl;

                    }
                    else if (i.typedAction==Arene::typeAction::tir and _peutTirer)
                    {
                        _peutTirer=false;
                        _arene.tir(tortue,i.positionAction);
                        victime=_arene.trouveLaTortuePosition(i.positionAction);

                        std::cout<<tortue->nom()<<"(tortue "<<_arene.numeroDeLaTortue(tortue)<<") a tirer sur "<<victime->nom()<<"(tortue "<<_arene.numeroDeLaTortue(victime)<<")"<<std::endl;
                        std::cout<<victime->nom()<<" a subis "<<tortue->degats()<<" de dégat il lui reste "<<victime->PV()<<std::endl<<std::endl;

                    }
                    else
                    {
                        std::cout<<"Problème dans le vecteur du tour";
                    }
                }
            }
            //a._historiquePartie.push_back(tour);

            tortue->setPE(enduMax);
            _tourTortue=(_tourTortue+1)%_arene.tailleListeTortue();
            _peutTirer=true;

        }
        //Par une magie obscure ça marche pas
        //tortue=a.vainqueur();
        std::cout<<tortue->nom()<<"(tortue "<<_arene.numeroDeLaTortue(tortue)<<") est vainqueur large il avait "
        <<tortue->PV()<<" PV"<<std::endl;
        //victoire


}



int jeuaffichage::tourTortue()
{
    return _tourTortue;
}

void jeuaffichage::on_actionJouer_triggered()
{
    jeu();
}

void jeuaffichage::on_actionQuitter_triggered()
{
    this->close();
}
