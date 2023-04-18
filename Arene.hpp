#pragma once
#include "Tortue.hpp"
#include <vector>
#include <QMainWindow>

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
    void mouvement();


private:
    Ui::Arene *ui;
    Tortue _tortue1;
    Tortue _tortue2;
    bool Tour;
    std::vector<Tuile> _map;
};



