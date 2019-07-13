#include "zwmanage.h"



ZWManage::ZWManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZWManage)
{
    ui->setupUi(this);
    tabModel = new QSqlRelationalTableModel(this);
    ui->tableView->setModel(tabModel);
    tabModel->setTable("zw");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setHeaderData(0,Qt::Horizontal,"职务ID");
    tabModel->setHeaderData(1,Qt::Horizontal,"职务");
    tabModel->select();
}

ZWManage::~ZWManage()
{
    delete ui;
}



void ZWManage::on_submit_btn_clicked()
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
}


void ZWManage::on_cancel_btn_clicked()
{
    tabModel->revertAll();
}


void ZWManage::on_add_btn_clicked()
{
    //获得表的行数
    int rowNum = tabModel->rowCount();
    //添加一行
    tabModel->insertRow(rowNum);
}


void ZWManage::on_del_btn_clicked()
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
