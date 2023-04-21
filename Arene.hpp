#pragma once
#include "Tortue.hpp"
#include <iostream>
#include <vector>
#include <QMainWindow>

#include <QFileDialog>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

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
    std::vector<int> tuileAccessible(Tortue tortue);
    void initmap();
    void printmap();

private:
    Ui::Arene *ui;
    Tortue _tortue1;
    Tortue _tortue2;
    bool _tour;
    std::vector<Tuile> _map;
    int _tailleMap;
};



