#ifndef FORMTORTUE_HPP
#define FORMTORTUE_HPP

#include <QDialog>

namespace Ui {
class formTortue;
}

class formTortue : public QDialog
{
    Q_OBJECT

public:
    explicit formTortue(QWidget *parent = nullptr);
    ~formTortue();
    std::string getNom();
    int getPV();
    int getPE();
    int getDEG();
    int getPOS();

private:
    Ui::formTortue *ui;
};

#endif // FORMTORTUE_HPP
