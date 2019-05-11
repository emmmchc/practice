#if 1==0

#include "widget.h"
#include "ui_widget.h"
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QModelIndex>
#include <QList>
#include <QSqlRecord>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit->setPlaceholderText("输入学号、姓名");
    tabModel = new QSqlRelationalTableModel(this);
    ui->tableView->setModel(tabModel);

    //设置自定义的委托
    ui->tableView->setItemDelegateForColumn(2,new TUserDelegate);
    ui->tableView->setItemDelegateForColumn(6,new CheckBoxDelegate);


    tabModel->setTable("info");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    tabModel->setHeaderData(0,Qt::Horizontal,"学号");
    tabModel->setHeaderData(1,Qt::Horizontal,"姓名");
    tabModel->setHeaderData(2,Qt::Horizontal,"性别");
    tabModel->setHeaderData(3,Qt::Horizontal,"学院");
    tabModel->setHeaderData(4,Qt::Horizontal,"专业");
    tabModel->setHeaderData(5,Qt::Horizontal,"GPA");
    tabModel->setHeaderData(6,Qt::Horizontal,"党员");
    tabModel->setRelation(3,QSqlRelation("departments","departID","department"));
    tabModel->setRelation(4,QSqlRelation("majors","majorID","major"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    tabModel->select();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_submit_btn_clicked()
{
    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll())
    {
        tabModel->database().commit(); //提交
    }
    else
    {
        tabModel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(tabModel->lastError().text()));
    }
}

void Widget::on_cancel_btn_clicked()
{
    tabModel->revertAll();
}

void Widget::on_add_btn_clicked()
{
    //获得表的行数
    int rowNum = tabModel->rowCount();
    //添加一行
    tabModel->insertRow(rowNum);
    tabModel->setData(tabModel->index(rowNum,0),rowNum+1);
}

void Widget::on_del_btn_clicked()
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

void Widget::on_sort_ckb_clicked(bool checked)
{
    if(checked==true)
    {
        tabModel->setSort(5, Qt::DescendingOrder);
        tabModel->select();
    }
    else
    {
        tabModel->setSort(5, Qt::AscendingOrder);
        tabModel->select();
    }

}

void Widget::on_lineEdit_textChanged(QString filter)
{
    if(filter.isEmpty())
    {
        tabModel->setFilter("");
        tabModel->select();
        return;
    }

    QString modelFilter = QString().sprintf("studentID like '%%%s%%' or name like '%%%s%%'", filter.toUtf8().data(), filter.toUtf8().data());
    //qDebug() << modelFilter;
    tabModel->setFilter(modelFilter);
    tabModel->select();
}

void Widget::on_lineEdit_textEdited()
{
    QStringList strList;
    for(int i=0; i<tabModel->rowCount(); ++i)
    {
        QSqlRecord record = tabModel->record(i);
        for(int j=0; j<record.count(); ++j)
        {
            QVariant var = record.value(j);
            if(var.isNull()) continue;
            strList << var.toString();
        }
    }
    //qDebug() << strList;
    QCompleter* completer=new QCompleter(strList);
    ui->lineEdit->setCompleter(completer);
}

#endif
