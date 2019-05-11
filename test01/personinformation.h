#ifndef PERSONINFORMATION_H
#define PERSONINFORMATION_H

#include <QDialog>

namespace Ui {
class PersonInformation;
}

class PersonInformation : public QDialog
{
    Q_OBJECT

public:
    explicit PersonInformation(QWidget *parent = 0);
    ~PersonInformation();

private:
    Ui::PersonInformation *ui;
};

#endif // PERSONINFORMATION_H
