#include "importrange.h"
#include "ui_importrange.h"

ImportRange::ImportRange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportRange)
{
    ui->setupUi(this);
}

ImportRange::~ImportRange()
{
    delete ui;
}

void ImportRange::on_okBtn_clicked()
{
    tabModel = new QSqlTableModel();
    tabModel->setTable("caculation");
    tabModel->select();
    QString leftLoc = ui->leftEdit->text();
    QString rightLoc = ui->rightEdit->text();

    QModelIndex index_left = tabModel->index(0,tabModel->fieldIndex("leftLoc"),QModelIndex());
    QModelIndex index_right = tabModel->index(0,tabModel->fieldIndex("rightLoc"),QModelIndex());
    tabModel->setData(index_left,leftLoc);
    tabModel->setData(index_right,rightLoc);
    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll() && tabModel->rowCount()!=0)
    {
        QMessageBox::information(this, "提交信息", "提交成功！",QMessageBox::Ok);
        tabModel->database().commit(); //提交
    }
    else
    {
        QMessageBox::critical(this, "错误信息",
               "提交错误,错误信息\n"+tabModel->lastError().text(),
                  QMessageBox::Ok,QMessageBox::NoButton);
        tabModel->database().rollback(); //回滚
    }

    QString strFile = QFileDialog::getOpenFileName(this,"选择文件","./","文本文件(*.xls;*.xlsx;)");
    if (strFile.isEmpty())
    {
         return;
    }

    readExcel(strFile);
}

void ImportRange::readExcel(QString filePath)
{
    QAxObject *excel = NULL;    //本例中，excel设定为Excel文件的操作对象
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel操作对象
    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)", false); //true 表示操作文件时可见，false表示为不可见
    workbooks = excel->querySubObject("WorkBooks");

    //————————————————按文件路径打开文件————————————————————
    workbook = workbooks->querySubObject("Open(QString&)", filePath);
    // 获取打开的excel文件中所有的工作sheet
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");

    QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);


    QSqlTableModel *Model = new QSqlTableModel();
    Model->setTable("caculation");
    Model->select();
    QModelIndex index_left = Model->index(0,Model->fieldIndex("leftLoc"),QModelIndex());
    QModelIndex index_right = Model->index(0,Model->fieldIndex("rightLoc"),QModelIndex());

    QVariant leftLoc = Model->data(index_left);
    QVariant rightLoc = Model->data(index_right);

    qDebug() << leftLoc << rightLoc;
    QVariantList params;
    params << leftLoc << rightLoc;  //数据范围

    excel = worksheet->querySubObject("Range(QVariant,QVariant)",params);
    QVariant excel_data = excel->dynamicCall("Value2()");
    //qDebug() << excel_data;
    if (excel)
    {
        delete excel;
        excel = NULL;
    }
    QList<QList<QVariant>> res;
    castVariant2ListListVariant(excel_data, res);


    QSqlTableModel model;
    model.setTable("admin");
    model.select();

    int i = model.rowCount()+10;
    QList<QList<QVariant>>::iterator iteLst = res.begin();
    for (iteLst = res.begin(); iteLst != res.end(); iteLst++)
    {
        model.insertRow(model.rowCount());
        model.setData(model.index(model.rowCount()-1,model.fieldIndex("id")),i);
        model.setData(model.index(model.rowCount()-1,model.fieldIndex("userName")),(*iteLst)[0].toString());
        model.setData(model.index(model.rowCount()-1,model.fieldIndex("userPwd")),(*iteLst)[1].toString());
        model.setData(model.index(model.rowCount()-1,model.fieldIndex("trueName")),(*iteLst)[2].toString());
        model.setData(model.index(model.rowCount()-1,model.fieldIndex("gender")),(*iteLst)[3].toString());
        model.setData(model.index(model.rowCount()-1,model.fieldIndex("type")),(*iteLst)[4].toString());



        if((*iteLst)[4].toString() == "学生")
        {
            //qDebug() << "识别出是一名学生";
            QSqlTableModel model,model_1;
            model.setTable("users");
            model_1.setTable("users");
            model_1.setFilter(tr("personId = '%1'").arg((*iteLst)[0].toString()));
            model_1.select();
            model.select();

            if(model_1.rowCount() == 1 && ui->ZCchkBox->isChecked()==true)//存在该名学生在users表中
            {
                QModelIndex lastD = model_1.index(0,model_1.fieldIndex("personLastDYCJ"));
                model_1.setData(lastD,(*iteLst)[5].toDouble());

                QModelIndex lastZ = model_1.index(0,model_1.fieldIndex("personLastZYCJ"));
                model_1.setData(lastZ,(*iteLst)[6].toDouble());

                QModelIndex nextD = model_1.index(0,model_1.fieldIndex("personNextDYCJ"));
                model_1.setData(nextD,(*iteLst)[7].toDouble());

                QModelIndex nextZ = model_1.index(0,model_1.fieldIndex("personNextZYCJ"));
                model_1.setData(nextZ,(*iteLst)[8].toDouble());

                QModelIndex classId = model_1.index(0,model_1.fieldIndex("classId"));
                model_1.setData(classId,(*iteLst)[9].toInt());


                double lastDYCJ = (*iteLst)[5].toDouble();
                double lastZYCJ = (*iteLst)[6].toDouble();
                double nextDYCJ = (*iteLst)[7].toDouble();
                double nextZYCJ = (*iteLst)[8].toDouble();


                QString *tmp = new QString[3];
                QString *cj = NULL;
                cj = calculate(lastDYCJ,lastZYCJ,nextDYCJ,nextZYCJ,tmp);
                tmp = NULL;
                delete tmp;

                QModelIndex index_cal_1  = model_1.index(0,model_1.fieldIndex("personLastZC"), QModelIndex());
                model_1.setData(index_cal_1,cj[0]);

                QModelIndex index_cal_2  = model_1.index(0,model_1.fieldIndex("personNextZC"), QModelIndex());
                model_1.setData(index_cal_2,cj[1]);

                QModelIndex index_cal_3  = model_1.index(0,model_1.fieldIndex("personTotalZC"), QModelIndex());
                model_1.setData(index_cal_3,cj[2]);


                cj = NULL;

                // 开始事务操作
                model_1.database().transaction();
                if (model_1.submitAll())
                    model_1.database().commit(); //提交
                else
                {
                    model_1.database().rollback(); //回滚
                    qDebug() << "导入users表出错";
                }


            }
            else if(model_1.rowCount() != 1 && ui->ZCchkBox->isChecked()==false)
            {
                model.insertRow(model.rowCount());
                //qDebug() << tr("插入后行数:'%2'").arg(model.rowCount());

                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personId")),(*iteLst)[0].toString());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personName")),(*iteLst)[2].toString());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personGender")),(*iteLst)[3].toString());
                // 开始事务操作
                model.database().transaction();
                if (model.submitAll())
                    model.database().commit(); //提交
                else
                    model.database().rollback(); //回滚

            }
            else if(model_1.rowCount() != 1 && ui->ZCchkBox->isChecked()==true)
            {

                qDebug() << "无该学生记录";
                model.insertRow(model.rowCount());
                //qDebug() << tr("插入后行数:'%2'").arg(model.rowCount());

                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personId")),(*iteLst)[0].toString());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personName")),(*iteLst)[2].toString());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personGender")),(*iteLst)[3].toString());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personLastDYCJ")),(*iteLst)[5].toDouble());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personLastZYCJ")),(*iteLst)[6].toDouble());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personNextDYCJ")),(*iteLst)[7].toDouble());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personNextZYCJ")),(*iteLst)[8].toDouble());
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("classId")),(*iteLst)[9].toInt());

                double lastDYCJ = (*iteLst)[5].toDouble();
                double lastZYCJ = (*iteLst)[6].toDouble();
                double nextDYCJ = (*iteLst)[7].toDouble();
                double nextZYCJ = (*iteLst)[8].toDouble();

                QString *tmp = new QString[3];
                QString *cj = NULL;
                cj = calculate(lastDYCJ,lastZYCJ,nextDYCJ,nextZYCJ,tmp);
                tmp = NULL;
                delete tmp;


                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personLastZC")),cj[0]);
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personNextZC")),cj[1]);
                model.setData(model.index(model.rowCount()-1,model.fieldIndex("personTotalZC")),cj[2]);


               //qDebug() << cj[0] << cj[1] << cj[2];
                cj = NULL;


                // 开始事务操作
                model.database().transaction();
                if (model.submitAll())
                    model.database().commit(); //提交
                else
                    model.database().rollback(); //回滚
            }

        }

        i++;

        // 开始事务操作
        model.database().transaction();
        if (model.submitAll())
            model.database().commit(); //提交
        else
            model.database().rollback(); //回滚
    }

    tabModel = new QSqlTableModel();
    tabModel->setTable("users");
    tabModel->setSort(tabModel->fieldIndex("personTotalZC"),Qt::DescendingOrder);//综测检查,降序排列
    tabModel->select();

    QSqlTableModel *MModel = new QSqlTableModel();
    MModel->setTable("caculation");
    MModel->select();

    QModelIndex index_1 = MModel->index(0,MModel->fieldIndex("firstRange"),QModelIndex());
    int firstRange = MModel->data(index_1).toInt();

    QModelIndex index_2 = MModel->index(0,MModel->fieldIndex("secondRange"),QModelIndex());
    int secondRange = MModel->data(index_2).toInt();

    QModelIndex index_3 = MModel->index(0,MModel->fieldIndex("thirdRange"),QModelIndex());
    int thirdRange = MModel->data(index_3).toInt();

    QModelIndex index_4 = MModel->index(0,MModel->fieldIndex("firstMoney"),QModelIndex());
    int firstMoney = MModel->data(index_4).toInt();

    QModelIndex index_5 = MModel->index(0,MModel->fieldIndex("secondMoney"),QModelIndex());
    int secondMoney = MModel->data(index_5).toInt();

    QModelIndex index_6 = MModel->index(0,MModel->fieldIndex("thirdMoney"),QModelIndex());
    int thirdMoney = MModel->data(index_6).toInt();

    int first = (firstRange/100.0) * tabModel->rowCount();//把0 到 first -1  行的记录取出来

    int second = (secondRange/100.0) * tabModel->rowCount();//把0 到 second -1  行的记录取出来

    int third = (thirdRange/100.0) * tabModel->rowCount();//把0 到 third -1  行的记录取出来

    qDebug() << first;
    qDebug() << second;
    qDebug() << third;

    //以下授予其一等奖
    for(int i=0; i < first; i++)
    {
        QModelIndex index_first = tabModel->index(i,tabModel->fieldIndex("personAward"));
        tabModel->setData(index_first,1);//1代表一等奖，以此类推

        QModelIndex index_bonus = tabModel->index(i,tabModel->fieldIndex("personBonus"));
        tabModel->setData(index_bonus,firstMoney); //一等奖学金

        tabModel->submitAll();
    }

    //以下授予其二等奖
    for(int i=first; i < second; i++)
    {
        QModelIndex index_second = tabModel->index(i,tabModel->fieldIndex("personAward"));
        tabModel->setData(index_second,2);

        QModelIndex index_bonus = tabModel->index(i,tabModel->fieldIndex("personBonus"));
        tabModel->setData(index_bonus,secondMoney); //二等奖学金

        tabModel->submitAll();
    }
    //以下授予其三等奖
    for(int i=second; i < third; i++)
    {
        QModelIndex index_third = tabModel->index(i,tabModel->fieldIndex("personAward"));
        tabModel->setData(index_third,3);

        QModelIndex index_bonus = tabModel->index(i,tabModel->fieldIndex("personBonus"));
        tabModel->setData(index_bonus,thirdMoney); //三等奖学金

        tabModel->submitAll();
    }



    QMessageBox::information(this,tr("提示"),tr("表格导入成功！"));

}

void ImportRange::castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0;i<rowCount;++i)
    {
        rowData = varRows[i].toList();
        res.push_back(rowData);
    }
}

