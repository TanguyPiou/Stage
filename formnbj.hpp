#ifndef FORMNBJ_HPP
#define FORMNBJ_HPP

#include <QDialog>

namespace Ui {
class formNBJ;
}

class formNBJ : public QDialog
{
    Q_OBJECT

public:
    explicit formNBJ(QWidget *parent = nullptr);
    ~formNBJ();

    int getNBJ();

private slots:
    void on_btn2J_clicked();

    void on_btn3J_clicked();

    void on_btn4J_clicked();

private:
    Ui::formNBJ *ui;
    int _choix;
};

#endif // FORMNBJ_HPP
