#include "personadd.h"
#include "ui_personadd.h"

PersonAdd::PersonAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonAdd)
{
    ui->setupUi(this);

    tabModel = new QSqlRelationalTableModel(this);
    tabModel->setTable("users");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

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
    tabModel->setHeaderData(tabModel->fieldIndex("ZWId"),Qt::Horizontal,"职务");
    tabModel->setHeaderData(tabModel->fieldIndex("personLastZC"),Qt::Horizontal,"综测(上学期)");
    tabModel->setHeaderData(tabModel->fieldIndex("personNextZC"),Qt::Horizontal,"综测(下学期)");
    tabModel->setHeaderData(tabModel->fieldIndex("personTotalZC"),Qt::Horizontal,"综测(学年)");
    tabModel->setHeaderData(tabModel->fieldIndex("personParty"),Qt::Horizontal,"党员");
    tabModel->setHeaderData(tabModel->fieldIndex("personSHS"),Qt::Horizontal,"三好生");
    tabModel->setHeaderData(tabModel->fieldIndex("personGQTY"),Qt::Horizontal,"优秀共青团员");
    tabModel->setHeaderData(tabModel->fieldIndex("personXXGB"),Qt::Horizontal,"优秀学生干部");
    tabModel->setHeaderData(tabModel->fieldIndex("personBonus"),Qt::Horizontal,"奖学金");
    tabModel->setHeaderData(tabModel->fieldIndex("personLastDYCJ"),Qt::Horizontal,"德育成绩(上)");
    tabModel->setHeaderData(tabModel->fieldIndex("personLastZYCJ"),Qt::Horizontal,"智育成绩(上)");
    tabModel->setHeaderData(tabModel->fieldIndex("personLastFail"),Qt::Horizontal,"挂科记录(上)");
    tabModel->setHeaderData(tabModel->fieldIndex("personNextDYCJ"),Qt::Horizontal,"德育成绩(下)");
    tabModel->setHeaderData(tabModel->fieldIndex("personNextZYCJ"),Qt::Horizontal,"智育成绩(下)");
    tabModel->setHeaderData(tabModel->fieldIndex("personNextFail"),Qt::Horizontal,"挂科记录(下)");
    tabModel->setHeaderData(tabModel->fieldIndex("personAward"),Qt::Horizontal,"奖学金");
    ui->tableView->setModel(tabModel);

    //qDebug() << "users表中有" << tabModel->rowCount();
    //tableView上为“性别”字段设置自定义代理组件
    QStringList strList;
    strList<<"女"<<"男";
    bool isEditable=false;
    delegateGender.setItems(strList,isEditable);
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personGender"),&delegateGender); //Combbox选择型

    //tableView上为“党员”字段设置自定义代理组件
    int col = tabModel->fieldIndex("personParty");//设置代理的列
    delegateParty.setColumn(col);
    ui->tableView->setItemDelegateForColumn(col,&delegateParty);

    //tableView上为“三好生”字段设置自定义代理组件
    int col_1 = tabModel->fieldIndex("personSHS");
    delegateSHS.setColumn(col_1);
    ui->tableView->setItemDelegateForColumn(col_1,&delegateSHS);

    //tableView上为“优秀共青团员”字段设置自定义代理组件
    int col_2 = tabModel->fieldIndex("personGQTY");
    delegateGQTY.setColumn(col_2);
    ui->tableView->setItemDelegateForColumn(col_2,&delegateGQTY);

    qDebug() << "users表中有" << tabModel->rowCount();

    //tableView上为“优秀学生干部”字段设置自定义代理组件
    int col_3 = tabModel->fieldIndex("personXXGB");
    delegateXXGB.setColumn(col_3);
    ui->tableView->setItemDelegateForColumn(col_3,&delegateXXGB);

    //tableView上为“挂科记录(上)”字段设置自定义代理组件
    int col_4 = tabModel->fieldIndex("personLastFail");
    delegateLastFail.setColumn(col_4);
    ui->tableView->setItemDelegateForColumn(col_4,&delegateLastFail);

    //tableView上为“挂科记录(下)”字段设置自定义代理组件
    int col_5 = tabModel->fieldIndex("personNextFail");
    delegateNextFail.setColumn(col_5);
    ui->tableView->setItemDelegateForColumn(col_5,&delegateNextFail);

    //班级,职务和奖学金放分别在三张表中，在users表中通过相应编号关联
    tabModel->setRelation(tabModel->fieldIndex("classId"),QSqlRelation("class","classId","className"));
    tabModel->setRelation(tabModel->fieldIndex("ZWId"),QSqlRelation("zw","ZWId","ZW"));
    tabModel->setRelation(tabModel->fieldIndex("personAward"),QSqlRelation("award","awardId","awardType"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));


    tabModel->select();
    qDebug() << "users表中有" << tabModel->rowCount();

    //隐藏不需要显示的列
    //ui->tableView->setColumnHidden(tabModel->fieldIndex("ZC"),true);


    //设置指定列不可编辑
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personId"),new NoEditDelegate());
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personName"),new NoEditDelegate());
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personGender"),new NoEditDelegate());
    //ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personSHS"),new NoEditDelegate());
    //ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personGQTY"),new NoEditDelegate());
    //ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personXXGB"),new NoEditDelegate());
    //ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personParty"),new NoEditDelegate());
    //ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personLastFail"),new NoEditDelegate());
    //ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personNextFail"),new NoEditDelegate());
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personLastDYCJ"),new NoEditDelegate());
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personLastZYCJ"),new NoEditDelegate());
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personNextDYCJ"),new NoEditDelegate());
    ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("personNextZYCJ"),new NoEditDelegate());


}

PersonAdd::~PersonAdd()
{
    delete ui;
}

void PersonAdd::on_submit_btn_clicked()
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

void PersonAdd::on_cancel_btn_clicked()
{
    tabModel->revertAll();
}

void PersonAdd::on_backBtn_clicked()
{
    this->accept();
}
