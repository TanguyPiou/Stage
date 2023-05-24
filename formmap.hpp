#ifndef FORMMAP_HPP
#define FORMMAP_HPP

#include <QDialog>

namespace Ui {
class formMap;
}

class formMap : public QDialog
{
    Q_OBJECT

public:
    explicit formMap(QWidget *parent = nullptr);
    ~formMap();
    int getChoix();

private slots:

    void on_btnmap1_clicked();
    void on_btnmap2_clicked();
    void on_btnmap3_clicked();

private:
    Ui::formMap *ui;
    int _choix;
};

#endif // FORMMAP_HPP
