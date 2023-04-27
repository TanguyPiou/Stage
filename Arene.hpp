#pragma once
#include "Tortue.hpp"
#include <vector>
#include <QMainWindow>
#include <iostream>

#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class Arene; }
QT_END_NAMESPACE




class Arene : public QMainWindow
{
    Q_OBJECT

public:
    Arene(QWidget *parent = nullptr);
    ~Arene();

    enum class Tuile {plaine,mur};
    void init();
    void loadmap(const QString & fileName);
    void printmap();
    int tailleMap();
    Tortue tortue1();
    Tortue tortue2();
    std::vector<int> tuileAccessible(Tortue tortue);
    std::vector<int> mouvementPossible(Tortue tortue);
    bool tuileDispo(int tuileVoulu);
    int distanceAction (Tortue tortue, int positionVoulu);
    void deplacementTortue(Tortue tortue, int positionVoulu);
    bool presenceTortue(int position);
    void tir(Tortue tortue, int cible);
    Tortue * trouveTortue(int position);

private slots:
    void on_actionloadmap_triggered();

private:
    Ui::Arene *ui;
    Tortue _tortue1;
    Tortue _tortue2;
    bool _tour;
    std::vector<Tuile> _map;
    int _tailleMap;
};



