#include "qdlglogin.h"
#include "ui_qdlglogin.h"

extern QString userID;
extern int exitCode;
QDlgLogin::QDlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDlgLogin)
{
    ui->setupUi(this);
    ui->editPswd->setEchoMode(QLineEdit::Password);//密码输入不可见
    ui->comboBox->setCurrentIndex(1);//设置默认为系统管理员
}

QDlgLogin::~QDlgLogin()
{
    delete ui;
}

void QDlgLogin::on_btnOk_clicked()
{

    QString user = ui->editUser->text().trimmed();//输入用户名
    QString pswd = ui->editPswd->text().trimmed();//输入密码

    QSqlTableModel model;
    model.setTable("admin");

    //判断用户身份
    if(ui->comboBox->currentIndex()==1)
    {
        model.setFilter(tr("userName = '%1' and userPwd = '%2' and type = '%3'").arg(user).arg(pswd).arg("系统管理员"));
        flag = 1;
    }
    else if(ui->comboBox->currentIndex()==2)
    {
        model.setFilter(tr("userName = '%1' and userPwd = '%2' and type = '%3'").arg(user).arg(pswd).arg("部门管理员"));
        flag = 2;
    }
    else if(ui->comboBox->currentIndex()==3)
    {
        model.setFilter(tr("userName = '%1' and userPwd = '%2' and type = '%3'").arg(user).arg(pswd).arg("学生"));
        flag = 3;
    }
    else
    {
        model.setFilter(tr("name = '%1' and password = '%2' and type = '%3'").arg(user).arg(pswd).arg(0));
    }

    //根据条件筛选记录
    model.select();

    if(model.rowCount()==1)
    {
        if(flag == 3)//登录成功，如果是学生，收集他的学号存入全局变量userID
        {
            QModelIndex id = model.index(0,model.fieldIndex("userName"),QModelIndex());
            userID = model.data(id).toString();
        }
        QMessageBox::information(this, "Login", "登录成功！",QMessageBox::Ok);
        this->accept();//关闭登录界面
    }
    else
    {
        m_tryCount++;
        if(m_tryCount>3)
        {
            QMessageBox::critical(this,"错误","输入错误次数太多，强行退出");
            exitCode = 0;
            this->reject();//退出
        }
        else
            QMessageBox::warning(this,"错误提示","用户名或密码错误");
    }
}


void QDlgLogin::on_btnExit_clicked()
{
    exitCode = 0;
    this->close();
    //qApp->exit(123);
}
