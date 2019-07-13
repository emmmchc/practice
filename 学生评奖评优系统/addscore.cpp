#include "addscore.h"
#include "ui_addscore.h"

extern QString userID; //用来记录登录学生学号

AddScore::AddScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddScore)
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

AddScore::~AddScore()
{
    delete ui;
}


void AddScore::on_okBtn_clicked()
{
    tabModel->setTable("users");
    tabModel->setFilter(tr("personId = '%1'").arg(userID));//userID是学生登录系统时所记录的学号
    tabModel->select();

    //先提取出学生的 姓名 性别 班级id

    QModelIndex Index_name  = tabModel->index(0,tabModel->fieldIndex("personName"), QModelIndex());
    QString str_name = tabModel->data(Index_name).toString();

    QModelIndex Index_gender  = tabModel->index(0,tabModel->fieldIndex("personGender"), QModelIndex());
    QString str_gender = tabModel->data(Index_gender).toString();

    QModelIndex Index_classId  = tabModel->index(0,tabModel->fieldIndex("classId"), QModelIndex());
    int ClassId = tabModel->data(Index_classId).toInt();

    double d_score = ui->spinBox->value();//想要加的分数

    QString str_addReason = ui->textEdit->toPlainText();//加分理由

    //qDebug() << d_score;
    if(ui->comboBox->currentText() == "上学期")
    {
        QModelIndex index_fail  = tabModel->index(0,tabModel->fieldIndex("personLastFail") , QModelIndex());
        int flag = tabModel->data(index_fail).toInt();
        if(flag == 1)
        {
            QMessageBox::critical(this,"提交失败","申请加分的学期有挂科记录");
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
            QModelIndex index_post_add = model.index(model.rowCount()-1,model.fieldIndex("postAdd"),QModelIndex());
            //QModelIndex index_postSHS = model.index(model.rowCount()-1,model.fieldIndex("postSHS"),QModelIndex());
            //QModelIndex index_postXXGB = model.index(model.rowCount()-1,model.fieldIndex("postXXGB"),QModelIndex());
            //QModelIndex index_postGQTY = model.index(model.rowCount()-1,model.fieldIndex("postGQTY"),QModelIndex());
            QModelIndex index_isLast = model.index(model.rowCount()-1,model.fieldIndex("isLast"),QModelIndex());
            QModelIndex index_score = model.index(model.rowCount()-1,model.fieldIndex("score"),QModelIndex());
            QModelIndex index_addReason = model.index(model.rowCount()-1,model.fieldIndex("addReason"),QModelIndex());

            model.setData(index_id,userID);
            model.setData(index_name,str_name);
            model.setData(index_gender,str_gender);
            model.setData(index_classId,ClassId);
            model.setData(index_isLast,1);//表示上学期提交的
            model.setData(index_score,d_score);
            model.setData(index_addReason,str_addReason);

            //在post表中标记 postAdd为1
            model.setData(index_post_add,1);


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
    else
    {
        QModelIndex index_fail  = tabModel->index(0,tabModel->fieldIndex("personNextFail") , QModelIndex());
        int flag = tabModel->data(index_fail).toInt();
        if(flag == 1)
        {
            QMessageBox::critical(this,"提交失败","申请加分的学期有挂科记录");
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
            QModelIndex index_post_add = model.index(model.rowCount()-1,model.fieldIndex("postAdd"),QModelIndex());
            //QModelIndex index_postSHS = model.index(model.rowCount()-1,model.fieldIndex("postSHS"),QModelIndex());
            //QModelIndex index_postXXGB = model.index(model.rowCount()-1,model.fieldIndex("postXXGB"),QModelIndex());
            //QModelIndex index_postGQTY = model.index(model.rowCount()-1,model.fieldIndex("postGQTY"),QModelIndex());
            QModelIndex index_isLast = model.index(model.rowCount()-1,model.fieldIndex("isLast"),QModelIndex());
            QModelIndex index_score = model.index(model.rowCount()-1,model.fieldIndex("score"),QModelIndex());
            QModelIndex index_addReason = model.index(model.rowCount()-1,model.fieldIndex("addReason"),QModelIndex());

            model.setData(index_id,userID);
            model.setData(index_name,str_name);
            model.setData(index_gender,str_gender);
            model.setData(index_classId,ClassId);
            model.setData(index_isLast,0);//表示下学期提交的
            model.setData(index_score,d_score);
            model.setData(index_addReason,str_addReason);

            //在post表中标记 postAdd为1
            model.setData(index_post_add,1);

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
}



