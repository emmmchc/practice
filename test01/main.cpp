#include "mainwindow.h"
#include <QApplication>
#include "qdlglogin.h"
#include <QStyleFactory>
#include <QString>

int flag;//登录时判别用户类型
QString userID;//记录登录用户ID
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));
    QDlgLogin *dlgLogin = new QDlgLogin;
    if(dlgLogin->exec()==QDlgLogin::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    else
        return 0;
}


