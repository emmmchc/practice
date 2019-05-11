#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
namespace Ui {
class QDlgLogin;
}

extern int flag;

class QDlgLogin : public QDialog
{
    Q_OBJECT
private:
    int m_tryCount = 0;//试错次数
    QSqlDatabase db;
public:
    explicit QDlgLogin(QWidget *parent = 0);
    ~QDlgLogin();

private slots:
    void on_btnOk_clicked();

    void on_btnExit_clicked();

private:
    Ui::QDlgLogin *ui;
};

#endif // QDLGLOGIN_H
