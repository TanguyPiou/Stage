#include "Arene.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arene w;
    w.tuileAccessible(w.tortue1());
    //std::cout<<w.coutEnduDeplacement(w.tortue1(),4);
    w.deplacementTortue(w.tortue1(),11);

    w.show();
    return a.exec();
}
