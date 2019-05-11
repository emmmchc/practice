#include "pjpyresult.h"
#include "ui_pjpyresult.h"

PJPYResult::PJPYResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PJPYResult)
{
    ui->setupUi(this);
    tabModel = new QSqlRelationalTableModel(this);
    tabModel->setTable("pjpy");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(tabModel);
    if (!(tabModel->select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tabModel->lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }
    tabModel->setHeaderData(tabModel->fieldIndex("personId"),Qt::Horizontal,"学号");
    tabModel->setHeaderData(tabModel->fieldIndex("personName"),Qt::Horizontal,"名字");
    tabModel->setHeaderData(tabModel->fieldIndex("personGender"),Qt::Horizontal,"性别");
    tabModel->setHeaderData(tabModel->fieldIndex("classId"),Qt::Horizontal,"班级");
    tabModel->setHeaderData(tabModel->fieldIndex("awardId"),Qt::Horizontal,"获奖情况");

    //班级和获奖情况放分别在class award两张表中，在users表中通过相应编号关联
    tabModel->setRelation(tabModel->fieldIndex("classId"),QSqlRelation("class","classId","className"));
    tabModel->setRelation(tabModel->fieldIndex("awardId"),QSqlRelation("award","awardId","awardType"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    //不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tabModel->select();
}

PJPYResult::~PJPYResult()
{
    delete ui;
}

void PJPYResult::on_searchBtn_clicked()
{
    tabModel->setTable("pjpy");
    QString sstr = ui->searchEdit->text();
    tabModel->setFilter(tr("personId = '%1' or personName = '%2'").arg(sstr).arg(sstr));

    tabModel->setHeaderData(tabModel->fieldIndex("personId"),Qt::Horizontal,"学号");
    tabModel->setHeaderData(tabModel->fieldIndex("personName"),Qt::Horizontal,"名字");
    tabModel->setHeaderData(tabModel->fieldIndex("personGender"),Qt::Horizontal,"性别");
    tabModel->setHeaderData(tabModel->fieldIndex("classId"),Qt::Horizontal,"班级");
    tabModel->setHeaderData(tabModel->fieldIndex("awardId"),Qt::Horizontal,"获奖情况");

    //班级和获奖情况放分别在class award两张表中，在users表中通过相应编号关联
    tabModel->setRelation(tabModel->fieldIndex("classId"),QSqlRelation("class","classId","className"));
    tabModel->setRelation(tabModel->fieldIndex("awardId"),QSqlRelation("award","awardId","awardType"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    //不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tabModel->select();
}
