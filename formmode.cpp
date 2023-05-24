#include "formmode.hpp"
#include "ui_formmode.h"

formMode::formMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formMode)
{
    ui->setupUi(this);
    ui->buttonBox->setDisabled(true);
}

formMode::~formMode()
{
    delete ui;
}

int formMode::getChoix()
{
    return _choix;
}

void formMode::on_btn_mode_1v1_clicked()
{
    _choix=1;
    ui->buttonBox->setDisabled(false);
}

void formMode::on_btn_mode_perso_clicked()
{
    _choix=2;
    ui->buttonBox->setDisabled(false);
}
