#ifndef FORMMODE_HPP
#define FORMMODE_HPP

#include <QDialog>

namespace Ui {
class formMode;
}

class formMode : public QDialog
{
    Q_OBJECT

public:
    explicit formMode(QWidget *parent = nullptr);
    ~formMode();
    int getChoix();

private slots:
    void on_btn_mode_1v1_clicked();

    void on_btn_mode_perso_clicked();

private:
    Ui::formMode *ui;
    int _choix;
};

#endif // FORMMODE_HPP
