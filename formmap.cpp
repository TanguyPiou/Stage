#include "formmap.hpp"
#include "ui_formmap.h"

formMap::formMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formMap)
{
    ui->setupUi(this);
    ui->buttonBox->setDisabled(true);
}

formMap::~formMap()
{
    delete ui;
}

int formMap::getChoix()
{
    return _choix;
}

void formMap::on_btnmap1_clicked()
{
    _choix=1;
    ui->buttonBox->setDisabled(false);
}

void formMap::on_btnmap2_clicked()
{
    _choix=2;
    ui->buttonBox->setDisabled(false);
}

void formMap::on_btnmap3_clicked()
{
    _choix=3;
    ui->buttonBox->setDisabled(false);
}
