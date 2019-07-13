#include "mainwindow.h"
#include <QApplication>
#include "qdlglogin.h"
#include <QStyleFactory>
#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
int flag;//登录时判别用户类型
QString userID;//记录登录用户ID
int exitCode = 0;//系统关闭时状态码
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));


    //连接数据库
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open())
    {
        QMessageBox::critical(NULL,"连接结果", "连接数据库失败");
        return 0;
    }

    QDlgLogin *dlgLogin = new QDlgLogin;


    do{
        if(dlgLogin->exec()==QDlgLogin::Accepted )
        {
            MainWindow w;
            w.show();
            exitCode  = a.exec();

        }

       }while( exitCode  == 888  );

    return a.exec();
}


