#include "JeuInterface.hpp"
JeuInterface::JeuInterface()
{

}

void JeuInterface::jeu()
{

        Arene a;
        //a.show();

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
        IAleatoire J3;


        listeJoueur.push_back(&J1);
        listeJoueur.push_back(&J2);
        listeJoueur.push_back(&J3);


        a.afficheMap();

        while(not a.finPartie())
        {
            if (a.laTortueEstEnVie(a.trouveLaTortueID(_tourTortue)))
            {
                std::cout<<"Tour tortues : "<<_tourTortue<<std::endl;
                tortue=a.trouveLaTortueID(_tourTortue);
                joueur=listeJoueur[_tourTortue];

                enduMax=tortue->PE();

                std::cout<<"Position des tortues : "<<std::endl;
                for (auto i : a.listeDesPositionsTortues())
                {
                    std::cout<<a.trouveLaTortuePosition(i)->nom()<<"(tortue "<<a.numeroDeLaTortue(a.trouveLaTortuePosition(i))<<") |"<<i<<"|"<<std::endl;
                }
                std::cout<<std::endl;


                tour=joueur->tour(_tourTortue, a.listeTortue(), a.map(), a.tailleDeLaMap());
                for(auto i : tour)
                {
                    if (i.typedAction==Arene::typeAction::deplacement)
                    {
                        a.deplacerTortue(tortue,i.positionAction);

                        std::cout<<tortue->nom()<<"(tortue "<<a.numeroDeLaTortue(tortue)<<") c'est déplacé sur la case "<<i.positionAction<<std::endl<<std::endl;

                    }
                    else if (i.typedAction==Arene::typeAction::tir and _peutTirer)
                    {
                        _peutTirer=false;
                        a.tir(tortue,i.positionAction);
                        victime=a.trouveLaTortuePosition(i.positionAction);

                        std::cout<<tortue->nom()<<"(tortue "<<a.numeroDeLaTortue(tortue)<<") a tirer sur "<<victime->nom()<<"(tortue "<<a.numeroDeLaTortue(victime)<<")"<<std::endl;
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
            _tourTortue=(_tourTortue+1)%a.tailleListeTortue();
            _peutTirer=true;

        }
        //Par une magie obscure ça marche pas
        //tortue=a.vainqueur();
        std::cout<<tortue->nom()<<"(tortue "<<a.numeroDeLaTortue(tortue)<<") est vainqueur large il avait "
        <<tortue->PV()<<" PV les autres sont nuls"<<std::endl;
        //victoire

}

int JeuInterface::tourTortue()
{
    return _tourTortue;
}
