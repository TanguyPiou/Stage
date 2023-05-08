#include "Arene.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arene w;
    w.jeu();
    w.show();
    return a.exec();
}
