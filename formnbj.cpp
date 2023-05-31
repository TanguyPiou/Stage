#include "formnbj.hpp"
#include "ui_formnbj.h"

formNBJ::formNBJ(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formNBJ)
{
    ui->setupUi(this);
    ui->buttonBox->setDisabled(true);
}

formNBJ::~formNBJ()
{
    delete ui;
}

int formNBJ::getNBJ()
{
    return _choix;
}

void formNBJ::on_btn2J_clicked()
{
    _choix=2;
    ui->buttonBox->setDisabled(false);
}

void formNBJ::on_btn3J_clicked()
{
    _choix=3;
    ui->buttonBox->setDisabled(false);
}

void formNBJ::on_btn4J_clicked()
{
    _choix=4;
    ui->buttonBox->setDisabled(false);
}
