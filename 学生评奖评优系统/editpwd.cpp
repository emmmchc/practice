#include "editpwd.h"
#include "ui_editpwd.h"

EditPwd::EditPwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPwd)
{
    ui->setupUi(this);
}

EditPwd::~EditPwd()
{
    delete ui;
}

void EditPwd::on_cancleBtn_clicked()
{
    this->close();
}



void EditPwd::on_okBtn_clicked()
{
    QString new_pwd = ui->lineEdit->text();
    tabModel = new QSqlTableModel();
    tabModel->setTable("admin");//绑定用户表
    QString tmpstr =userID;//得到登录用户ID
    tabModel->setFilter(tr("userName = '%1'").arg(tmpstr));
    tabModel->select();//得到当前用户记录
    QModelIndex index = tabModel->index(0,tabModel->fieldIndex("userPwd"),QModelIndex());
    tabModel->setData(index,new_pwd);
    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll() && tabModel->rowCount()!=0)
    {
        QMessageBox::information(this, "提交信息", "修改成功！",QMessageBox::Ok);
        tabModel->database().commit(); //提交
    }
    else
    {
        QMessageBox::critical(this, "错误信息",
               "提交错误,错误信息\n"+tabModel->lastError().text(),
                  QMessageBox::Ok,QMessageBox::NoButton);
        tabModel->database().rollback(); //回滚
    }
}
