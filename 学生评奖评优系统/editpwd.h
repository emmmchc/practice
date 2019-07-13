#ifndef EDITPWD_H
#define EDITPWD_H

#include <QDialog>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QMessageBox>
#include <QSqlError>
extern QString userID;//记录登录用户ID
namespace Ui {
class EditPwd;
}

class EditPwd : public QDialog
{
    Q_OBJECT

public:
    explicit EditPwd(QWidget *parent = 0);
    ~EditPwd();

private slots:
    void on_cancleBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::EditPwd *ui;
    QSqlTableModel *tabModel;
};

#endif // EDITPWD_H
