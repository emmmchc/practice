#ifndef REGULATION_H
#define REGULATION_H

#include <QDialog>
#include "QSqlTableModel"

QString * calculate(double,double,double,double,QString*);
QString * calculate(double,double,QString*);

namespace Ui {
class Regulation;
}

class Regulation : public QDialog
{
    Q_OBJECT

public:
    explicit Regulation(QWidget *parent = 0);
    ~Regulation();
private slots:
    void on_lastDEdit_textChanged(const QString &arg1);

    void on_lastZEdit_textChanged(const QString &arg1);

    void on_nextZEdit_textChanged(const QString &arg1);

    void on_lastTEdit_textChanged(const QString &arg1);

    void on_nextDEdit_textChanged(const QString &arg1);

    void on_nextTEdit_textChanged(const QString &arg1);

    void on_firstRangeEdit_textChanged(const QString &arg1);

    void on_firstMoneyEdit_textChanged(const QString &arg1);

    void on_secondRangeEdit_textChanged(const QString &arg1);

    void on_secondMoneyEdit_textChanged(const QString &arg1);

    void on_thirdRangeEdit_textChanged(const QString &arg1);

    void on_thirdMoneyEdit_textChanged(const QString &arg1);

    void on_GQTYRangeEdit_textChanged(const QString &arg1);

    void on_XXGBRangeEdit_textChanged(const QString &arg1);

    void on_SHSRangeEdit_textChanged(const QString &arg1);

private:
    Ui::Regulation *ui;
    QSqlTableModel model;

};

#endif // REGULATION_H
