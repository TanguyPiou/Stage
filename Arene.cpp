#include "Arene.hpp"



Arene::Arene()
{
    /*
    int n;
    std::string map;
    std::string nomTortue;
    float PV;
    float PE;
    int degat;
    int pos;


    std::cout<<"Quel map (1, 2 ou 3) : ";
    std::cin>>n;
    if (n==3)
    {
        map="maps/map2";
    }
    else if (n==2)
    {
        map="maps/map1";
    }
    else
    {
        map="maps/default";
    }

    std::cout<<std::endl<<"Nombre de joueur : ";
    std::cin>>n;

    for (int i=0; i<n;++i)
    {
        std::cout<<"Tortue "<<i<<" : "<<std::endl;
        std::cout<<"Nom de la tortue : ";
        std::cin>>nomTortue;
        std::cout<<"Nombre de PV : ";
        std::cin>>PV;
        std::cout<<"Nombre de PE : ";
        std::cin>>PE;
        std::cout<<"Nombre de degat : ";
        std::cin>>degat;
        std::cout<<"Positionnement sur la map : ";
        std::cin>>pos;

        _listeTortue.push_back(Tortue(nomTortue,PV,PE,degat,pos));

    }

    loadmap(map);*/
    Arene("Settings/defaut.txt");

}

Arene::Arene(std::vector<Tortue> listeDesTortues, std::vector<Arene::Tuile> map, int tailleMap)
{
    //for (std::size_t n=0;n<_listeTortue.size() ;++n )
    {
    _listeTortue=listeDesTortues;
    }
    _map=map;
    _tailleMap=tailleMap;
}

Arene::Arene(std::vector<Tortue> listeDesTortues, std::string map)
{
    _listeTortue=listeDesTortues;
    loadmap(map);
}

Arene::~Arene()
{
}

Arene::Arene(std::string fileName)
{
    std::string nomTortue;
    float PV;
    float PE;
    int degat;
    int pos;
    std::ifstream fichier(fileName);
    std::string map;
    int numLigne=1;

     if(fichier)
     {
        //L'ouverture s'est bien passée, on peut donc lire
        std::string ligne; //Une variable pour stocker les lignes lues

        while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            std::cout<<"Tortue : "<<numLigne;
            switch (numLigne)
            {
                case(1) :
                    if (ligne=="3")
                    {
                        map="maps/map2";
                    }
                    else if (ligne=="2")
                    {
                        map="maps/map1";
                    }
                    else
                    {
                        map="maps/default";
                    }
                    break;
                case(2) :
                    nomTortue=ligne;
                    break;
                case(3) :
                    PV=std::stof(ligne);
                    break;
                case(4) :
                    PE=std::stof(ligne);
                    break;
                case(5) :
                    degat=std::stof(ligne);
                    break;
                case(6) :
                    pos=std::stof(ligne);
                    std::cout<<"Tortue : "<<nomTortue<<PV<<PE<<degat<<pos<<std::endl;
                    _listeTortue.push_back(Tortue(nomTortue,PV,PE,degat,pos));
                    numLigne=1;
                    break;
            }
            ++numLigne;
        }
     }
     else
     {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
     }

    loadmap(map);
}

void Arene::loadmap(std::string fileName)
{
    std::ifstream fichier(fileName);
    std::vector<Tuile> map;
    int taille=0;

     if(fichier)
     {
        //L'ouverture s'est bien passée, on peut donc lire

        std::string ligne; //Une variable pour stocker les lignes lues

        while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {

           //std::cout << ligne << std::endl;
           taille++;
           for(auto i : ligne){
               if(i=='M') map.push_back(Tuile::mur);
               else map.push_back(Tuile::plaine);
           }
           //Et on l'affiche dans la console
           //Ou alors on fait quelque chose avec cette ligne
           //À vous de voir
        }
     }
     else
     {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
     }


    //Parcours du fichier

    _map=map;
    _tailleMap=taille;


}


//Partie C++//

//Fonction qui actualise l'arène virtuel avec celle de l'arène principal


    //Fonction d'affichage c++//

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

//BUG je ne sais pas pk n'est pas utilisé

Tortue * Arene::vainqueur()
{
    Tortue * TortueTop1;

    for (auto i : _listeTortue)
    {
        if (laTortueEstEnVie(&i))
        {
            TortueTop1=&i;
        }
    }
    return TortueTop1;
}

    //Accesseur//

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

    //Fonction d'information basique//

int Arene::tailleListeTortue()
{
    return _listeTortue.size();
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

std::vector<int> Arene::listeDesPositionsTortues() const
{
    std::vector<int> posTortue;
    for (auto i : _listeTortue)
    {
            posTortue.push_back(i.pos());
    }
    return posTortue;
}


    //Fonction de vérification//

bool Arene::presenceDUneTortue(int position) const
{
    bool ret=false;
    for (auto i : _listeTortue){
        if(i.pos()==position and laTortueEstEnVie(&i))
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

bool Arene::laTortueEstEnVie(Tortue *tortue) const
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
        if (laTortueEstEnVie(&i))
            tortueVivante++;
    }
    if (tortueVivante>1)
        return false;
    else
        return true;

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
    /* TEST MOUVEMENT
    std::cout<<'\n'<<"Position de la tortue :"<<tortue->pos();
    std::cout<<'\n'<<"Endurance de la tortue :"<<tortue->PE();
    // FIN TEST */
}



//Fonction Permettant de Tirer//

std::vector<int> Arene::posTortueAPorterDeTir(Tortue *tortue)
{
    int currentTortue = tortue->pos();
    int deplacementVirtuel;
    bool toucher=false;

    std::vector<int> tortueTirable;
    for(auto tortueCibler : listeDesPositionsTortues())
    {
        if (laTortueEstEnVie(trouveLaTortuePosition(tortueCibler)))
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

    }
    return tortueTirable;
}


void Arene::tir(Tortue *tortue, int cible)
{
   std::vector<int> v=posTortueAPorterDeTir(tortue);
   Tortue * tortueCibler;
   int PVrestant;
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
            PVrestant=tortueCibler->PV()-tortue->degats();
            if(PVrestant<0)
                PVrestant=0;
            tortueCibler->setPV(PVrestant);
            tortue->setPE(tortue->PE()-1);
            //std::cout<<"Tir effectuer"<<trouveLaTortuePosition(cible)->PV()<<std::endl;
   }
}

int Arene::getTailleMap() const
{
    return _tailleMap;
}

std::vector<Arene::Tuile> Arene::getMap() const
{
    return _map;
}

//Partie QT //
