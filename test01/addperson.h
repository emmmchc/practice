#ifndef ADDPERSON_H
#define ADDPERSON_H



namespace Ui {
class AddPerson;
}

class AddPerson : public QDialog
{
    Q_OBJECT

public:
    explicit AddPerson(QWidget *parent = 0);
    ~AddPerson();

private slots:
    void on_cancelBtn_clicked();

private:
    Ui::AddPerson *ui;

};

#endif // ADDPERSON_H
