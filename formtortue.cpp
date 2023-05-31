#include "formtortue.hpp"
#include "ui_formtortue.h"

formTortue::formTortue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formTortue)
{
    ui->setupUi(this);
}

formTortue::~formTortue()
{
    delete ui;
}

std::string formTortue::getNom()
{
    return ui->lineEdit->text().toStdString();
}

int formTortue::getPV()
{
    return ui->spinBoxPV->value();
}

int formTortue::getPE()
{
    return ui->spinBoxPE->value();
}

int formTortue::getDEG()
{
    return ui->spinBoxDEG->value();
}

int formTortue::getPOS()
{
    return ui->spinBoxPOS->value();
}
