#include "usersmanage.h"
#include "ui_usersmanage.h"

#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QModelIndex>
#include <QList>
#include <QSqlRecord>
#include <QDebug>

UsersManage::UsersManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersManage)
{
    ui->setupUi(this);

    tabModel = new QSqlRelationalTableModel;
    tabModel->setTable("admin");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!(tabModel->select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tabModel->lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }

    tabModel->setHeaderData(tabModel->fieldIndex("id"),Qt::Horizontal,"ID");
    tabModel->setHeaderData(tabModel->fieldIndex("userName"),Qt::Horizontal,"账号");
    tabModel->setHeaderData(tabModel->fieldIndex("userPwd"),Qt::Horizontal,"密码");
    tabModel->setHeaderData(tabModel->fieldIndex("trueName"),Qt::Horizontal,"真实姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("gender"),Qt::Horizontal,"性别");
    tabModel->setHeaderData(tabModel->fieldIndex("type"),Qt::Horizontal,"类别");

    ui->tableView->setModel(tabModel);

    //tableView上为“类别”字段设置自定义代理组件
    QStringList strList;
    strList<<"系统管理员"<<"部门管理员"<<"学生";
    bool isEditable=false;
    delegateType.setItems(strList,isEditable);
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("type"),&delegateType); //Combbox选择型

    //tableView上为“性别”字段设置自定义代理组件
    QStringList strList_1;
    strList_1<<"女"<<"男";
    bool isEditable_1=false;
    delegateGender.setItems(strList_1,isEditable_1);
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("gender"),&delegateGender); //Combbox选择型
    theSelection=new QItemSelectionModel(tabModel);//关联选择模型
    tabModel->select();
}

UsersManage::~UsersManage()
{
    delete ui;
}

void UsersManage::on_submit_btn_clicked()
{
    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll())
    {

        tabModel->database().commit(); //提交
        QMessageBox::information(this, "提交成功", "保存成功！",QMessageBox::Ok);
    }
    else
    {
        tabModel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(tabModel->lastError().text()));
    }

    QSqlTableModel Model;
    Model.setTable("admin");
    Model.setFilter(tr("type = '%1'").arg("学生"));
    Model.select();
    qDebug() << Model.rowCount();
    if(Model.rowCount() >= 1)
    {

        for(int i=0; i<Model.rowCount(); i++)
        {

            QModelIndex index_id = Model.index(i,Model.fieldIndex("userName"));
            QModelIndex index_name = Model.index(i,Model.fieldIndex("trueName"));
            QModelIndex index_gender = Model.index(i,Model.fieldIndex("gender"));
            QString str_id = Model.data(index_id).toString();
            QString str_name = Model.data(index_name).toString();
            QString str_gender = Model.data(index_gender).toString();\

            QSqlTableModel model,model_1;
            model.setTable("users");
            model_1.setTable("users");
            model_1.setFilter(tr("personId = '%1'").arg(str_id));
            model_1.select();
            model.select();

            if(model_1.rowCount() == 1)//存在该名学生在users表中，则不再进行插入
                ;
            else
            {
                //qDebug() << str_id;
                //qDebug() << str_name;
                //qDebug() << str_gender;
                //qDebug() << tr("插入前行数:'%1'").arg(model.rowCount());
                model.insertRow(model.rowCount());
                //qDebug() << tr("插入后行数:'%2'").arg(model.rowCount());

                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personId")),str_id);
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personName")),str_name);
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personGender")),str_gender);

                // 开始事务操作
                model.database().transaction();
                if (model.submitAll())
                    model.database().commit(); //提交
                else
                    model.database().rollback(); //回滚

            }
        }
    }

}

void UsersManage::on_cancel_btn_clicked()
{
    tabModel->revertAll();
}

void UsersManage::on_add_btn_clicked()
{
    tabModel->insertRow(tabModel->rowCount(),QModelIndex()); //在末尾添加一个记录

    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);//创建最后一行的ModelIndex
    theSelection->clearSelection();//清空选择项
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);//设置刚插入的行为当前选择行

    int currow=curIndex.row(); //获得当前行
    tabModel->setData(tabModel->index(currow,0),tabModel->rowCount()); //自动生成编号
    tabModel->setData(tabModel->index(currow,tabModel->fieldIndex("userPwd")),"123456");//设置默认登录密码
}

void UsersManage::on_del_btn_clicked()
{
    //通过tableview去获取被选中的部分的数据model
    QItemSelectionModel * selectModel = ui->tableView->selectionModel();
    //通过选中的数据结构，获取这些格子的ModelIndex
    QModelIndexList selectList =  selectModel->selectedIndexes();
    QList<int> delRow;

    // 遍历这些格子，获取格子所在行，因为可能存在相同的行，所以要去重
    for(int i=0; i<selectList.size(); ++i)
    {
        QModelIndex index = selectList.at(i);
        //tabModel->removeRow(index.row());
        delRow << index.row();
    }

    while(delRow.size() > 0)
    {
        int row = delRow.at(0);
        delRow.removeAll(row);
        tabModel->removeRow(row);
    }

    int ok = QMessageBox::warning(this,tr("删除选中记录!"),
                                  tr("你确定删除选中记录吗？"),
                                 QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        tabModel->revertAll(); //如果不删除，则撤销
    }
    else tabModel->submitAll(); //否则提交，在数据库中删除该行
}
