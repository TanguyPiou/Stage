#pragma once
#include "Arene.hpp"
#include "IA.hpp"
#include "IAleatoire.hpp"
#include "Joueur.hpp"

#include "formmode.hpp"
#include "formnbj.hpp"
#include "formtortue.hpp"
#include "formmap.hpp"


#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItemAnimation>
#include <QTimer>
#include <QTimeLine>



namespace Ui {
class jeuaffichage;
}

class jeuaffichage : public QMainWindow
{
    Q_OBJECT

public:
    explicit jeuaffichage(QWidget *parent = nullptr);
    ~jeuaffichage();

    void initmap();
    void initPosTortues();
    void updatePosTortue(int i);

    QString choixMapForm();
    Tortue creerTortueForm();
    Arene creerAreneFormPerso();
    Arene creerAreneForm();
    void jeu();
    int tourTortue();

private slots:
    void on_actionJouer_triggered();

    void on_actionQuitter_triggered();

private:
    Ui::jeuaffichage *ui;
    Arene _arene;
    int _tourTortue;
    bool _peutTirer;

    formMode _formmode;
    formNBJ _formnbj;
    formTortue _formtortue;
    formMap _formmap;

    std::vector<QGraphicsItem*> _items;
};
