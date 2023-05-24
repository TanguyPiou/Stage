#include "Arene.hpp"
#include "JeuInterface.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JeuInterface w;
    w.jeu();

    return 0;
    //return a.exec();
}
