#include "excellenceapply.h"
#include "ui_excellenceapply.h"

extern QString userID; //用来查找该学生

ExcellenceApply::ExcellenceApply(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExcellenceApply)
{
    ui->setupUi(this);
    ui->idEdit->setEnabled(false);
    ui->classEdit->setEnabled(false);
    ui->nameEdit->setEnabled(false);
    ui->genderEdit->setEnabled(false);
    //以上控件不可编辑

    tabModel = new QSqlTableModel(this);
    tabModel->setTable("users");
    tabModel->setFilter(tr("personId = '%1'").arg(userID));//userID是学生登录系统时所记录的学号
    tabModel->select();

    QModelIndex index_id  = tabModel->index(0,tabModel->fieldIndex("personId") , QModelIndex());
    ui->idEdit->setText(tabModel->data(index_id).toString());

    QModelIndex index_name  = tabModel->index(0, tabModel->fieldIndex("personName"), QModelIndex());
    ui->nameEdit->setText(tabModel->data(index_name).toString());

    QModelIndex index_gender  = tabModel->index(0, tabModel->fieldIndex("personGender"), QModelIndex());
    ui->genderEdit->setText(tabModel->data(index_gender).toString());

    //导入班级时先查找班级字典
    QModelIndex index_class  = tabModel->index(0, tabModel->fieldIndex("classId"), QModelIndex());
    int m_class = tabModel->data(index_class).toInt();
    QSqlTableModel m_model;
    m_model.setTable("class");
    m_model.setFilter(tr("classId = '%1'").arg(m_class));
    m_model.select();
    if(m_model.rowCount() == 1)
    {
        QModelIndex index_m_class = m_model.index(0,1,QModelIndex());
        ui->classEdit->setText(m_model.data(index_m_class).toString());
    }

}

ExcellenceApply::~ExcellenceApply()
{
    delete ui;
}

void ExcellenceApply::on_okBtn_clicked()
{
    tabModel->setTable("users");
    tabModel->setFilter(tr("personId = '%1'").arg(userID));//userID是学生登录系统时所记录的学号
    tabModel->select();

    //先提取出学生的 姓名 性别 班级id 综测

    QModelIndex Index_name  = tabModel->index(0,tabModel->fieldIndex("personName"), QModelIndex());
    QString str_name = tabModel->data(Index_name).toString();

    QModelIndex Index_gender  = tabModel->index(0,tabModel->fieldIndex("personGender"), QModelIndex());
    QString str_gender = tabModel->data(Index_gender).toString();

    QModelIndex Index_classId  = tabModel->index(0,tabModel->fieldIndex("classId"), QModelIndex());
    int ClassId = tabModel->data(Index_classId).toInt();

    QModelIndex Index_total_zc  = tabModel->index(0,tabModel->fieldIndex("personTotalZC"), QModelIndex());
    double total_zc = tabModel->data(Index_total_zc).toDouble();

    QString str_excelReason = ui->textEdit->toPlainText();//评优理由

    QModelIndex index_last_fail  = tabModel->index(0,tabModel->fieldIndex("personLastFail") , QModelIndex());
    QModelIndex index_next_fail  = tabModel->index(0,tabModel->fieldIndex("personNextFail") , QModelIndex());
    int flag = 0;

    //综测前30%
    tabModel->setTable("users");
    tabModel->setSort(tabModel->fieldIndex("personTotalZC"),Qt::DescendingOrder);//综测检查,降序排列
    tabModel->select();

    int in = (3/10.0) * tabModel->rowCount();//把第 "in" -1  行的记录取出来跟本学生对比综测

    QModelIndex index_compare = tabModel->index(in-1,tabModel->fieldIndex("personTotalZC"));
    double cp = tabModel->data(index_compare).toDouble();

    if(cp > total_zc)//总综测比前30%都小，不合格
        flag = 1;

    if(tabModel->data(index_last_fail).toInt() == 1 or tabModel->data(index_next_fail).toInt() == 1)//有不及格科目，不合格
        flag = 1;

    if(flag == 1)
    {
        QMessageBox::critical(this,"提交失败","综测小于前30%或者有挂科记录");
    }
    else
    {
        QMessageBox::information(this, "提交成功", "申请成功!\n请等待处理结果",QMessageBox::Ok);

        QSqlTableModel model;
        model.setTable("post");
        model.select();
        model.insertRow(model.rowCount()); //在末尾添加一个记录

        QModelIndex index_id = model.index(model.rowCount()-1,model.fieldIndex("personId"),QModelIndex());
        QModelIndex index_name = model.index(model.rowCount()-1,model.fieldIndex("personName"),QModelIndex());
        QModelIndex index_gender = model.index(model.rowCount()-1,model.fieldIndex("personGender"),QModelIndex());
        QModelIndex index_classId = model.index(model.rowCount()-1,model.fieldIndex("classId"),QModelIndex());
        //QModelIndex index_postAdd = model.index(model.rowCount()-1,model.fieldIndex("postAdd"),QModelIndex());
        QModelIndex index_postSHS = model.index(model.rowCount()-1,model.fieldIndex("postSHS"),QModelIndex());
        QModelIndex index_postXXGB = model.index(model.rowCount()-1,model.fieldIndex("postXXGB"),QModelIndex());
        QModelIndex index_postGQTY = model.index(model.rowCount()-1,model.fieldIndex("postGQTY"),QModelIndex());
        //QModelIndex index_isLast = model.index(model.rowCount()-1,model.fieldIndex("isLast"),QModelIndex());
        //QModelIndex index_score = model.index(model.rowCount()-1,model.fieldIndex("score"),QModelIndex());
        QModelIndex index_excelReason = model.index(model.rowCount()-1,model.fieldIndex("excelReason"),QModelIndex());

        model.setData(index_id,userID);
        model.setData(index_name,str_name);
        model.setData(index_gender,str_gender);
        model.setData(index_classId,ClassId);

        if(ui->GQTYchkBox->isChecked() == true)
            model.setData(index_postGQTY,1);
        if(ui->SHSchkBox->isChecked() == true)
            model.setData(index_postSHS,1);
        if(ui->XXGBchkBox->isChecked() == true)
            model.setData(index_postXXGB,1);


        model.setData(index_excelReason,str_excelReason);

        // 开始事务操作
        model.database().transaction();
        if (model.submitAll())
            model.database().commit(); //提交
        else
        {
            model.database().rollback(); //回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(model.lastError().text()));
        }

    }
}

void ExcellenceApply::on_XXGBchkBox_clicked(bool checked)
{
    if(checked == true)
    {
        ui->SHSchkBox->setEnabled(false);
        ui->GQTYchkBox->setEnabled(false);
    }
    else
    {
        ui->SHSchkBox->setEnabled(true);
        ui->GQTYchkBox->setEnabled(true);
    }
}


void ExcellenceApply::on_SHSchkBox_clicked(bool checked)
{
    if(checked == true)
    {
        ui->XXGBchkBox->setEnabled(false);
        ui->GQTYchkBox->setEnabled(false);
    }
    else
    {
        ui->XXGBchkBox->setEnabled(true);
        ui->GQTYchkBox->setEnabled(true);
    }
}


void ExcellenceApply::on_GQTYchkBox_clicked(bool checked)
{
    if(checked == true)
    {
        ui->SHSchkBox->setEnabled(false);
        ui->XXGBchkBox->setEnabled(false);
    }
    else
    {
        ui->SHSchkBox->setEnabled(true);
        ui->XXGBchkBox->setEnabled(true);
    }
}
