#include "Arene.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arene w;
    //std::cout<<w.coutEnduDeplacement(w.tortue1(),4);

    //w.tir(w.tortue1(),21);

    w.jeu();
    std::cout<<"Vie T2 : "<<w.tortue2()->PV()<<w.tortue1()->pos()<<std::endl;
    w.show();
    return a.exec();
}
