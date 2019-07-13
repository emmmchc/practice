#include "pjpyresult.h"
#include "ui_pjpyresult.h"

PJPYResult::PJPYResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PJPYResult)
{
    ui->setupUi(this);


    //删除pjpy表中一二三等奖学生信息
    QSqlTableModel *del = new QSqlTableModel();
    del->setTable("pjpy");
    del->select();

    int pjpyCount = del->rowCount();
    for(int i=0; i<pjpyCount ;i++)
    {
        QModelIndex award_type = del->index(i,del->fieldIndex("awardId"));
        int award = del->data(award_type).toInt();
        if(award == 1 || award == 2 || award == 3)
        {
            del->removeRow(i);
            del->submitAll();
        }
    }



    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("users");
    model->select();
    int rowCount = model->rowCount();
    for(int i = 0; i < rowCount ; i++)
    {
       QModelIndex awardId = model->index(i,model->fieldIndex("personAward"),QModelIndex());
       int awardType = model->data(awardId).toInt();

       if(awardType == 0)
           continue;

       //将评优情况录入评奖评优表(pjpy)中
       QSqlTableModel pjpy;
       pjpy.setTable("pjpy");
       pjpy.select();
       pjpy.insertRow(pjpy.rowCount()); //在末尾添加一个记录
       QModelIndex index_id = pjpy.index(pjpy.rowCount()-1,pjpy.fieldIndex("personId"),QModelIndex());
       QModelIndex index_name = pjpy.index(pjpy.rowCount()-1,pjpy.fieldIndex("personName"),QModelIndex());
       QModelIndex index_gender = pjpy.index(pjpy.rowCount()-1,pjpy.fieldIndex("personGender"),QModelIndex());
       QModelIndex index_CLASSId = pjpy.index(pjpy.rowCount()-1,pjpy.fieldIndex("classId"),QModelIndex());
       QModelIndex index_awardId = pjpy.index(pjpy.rowCount()-1,pjpy.fieldIndex("awardId"),QModelIndex());

       QModelIndex Id = model->index(i,model->fieldIndex("personId"),QModelIndex());
       QString str_Id = model->data(Id).toString();

       QModelIndex Name= model->index(i,model->fieldIndex("personName"),QModelIndex());
       QString str_Name = model->data(Name).toString();

       QModelIndex Gender = model->index(i,model->fieldIndex("personGender"),QModelIndex());
       QString str_Gender = model->data(Gender).toString();

       QModelIndex Class = model->index(i,model->fieldIndex("classId"),QModelIndex());
       int int_Class = model->data(Class).toInt();

       QModelIndex Award = model->index(i,model->fieldIndex("personAward"),QModelIndex());
       int int_Award = model->data(Award).toInt();

       //qDebug() << int_Award;
       pjpy.setData(index_id,str_Id);
       pjpy.setData(index_name,str_Name);
       pjpy.setData(index_gender,str_Gender);
       pjpy.setData(index_CLASSId,int_Class);
       pjpy.setData(index_awardId,int_Award);
       pjpy.submitAll();

    }

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
    //qDebug() << tabModel->rowCount();
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
