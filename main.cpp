#include "Arene.hpp"
#include "jeuaffichage.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    jeuaffichage w;
    w.show();
    //w.jeu();

    return a.exec();
}
