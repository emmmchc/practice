#include "cjimport.h"
#include "ui_cjimport.h"


CJImport::CJImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CJImport)
{
    ui->setupUi(this);
    ui->nameEdit->setEnabled(false);
    ui->idEdit->setEnabled(false);
    ui->classEdit->setEnabled(false);
    tabModel = new QSqlTableModel(this);//为tabModel分配内存
}

CJImport::~CJImport()
{
    delete ui;
}

void CJImport::on_cancelBtn_clicked()
{
    this->accept();
}


void CJImport::on_okBtn_clicked()
{
    if(ui->idEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","该学生信息不存在!");
    }
    else
    {
        tabModel->setTable("users");//绑定学生信息表
        tabModel->setFilter(tr("personId = '%1'").arg(ui->idEdit->text()));
        tabModel->select();
        //由于之前已经经过判断，此时一定存在该名学生

        if(ui->comboBox->currentText() == "上学期")
        {
            QModelIndex index_DY  = tabModel->index(0,tabModel->fieldIndex("personLastDYCJ"), QModelIndex());
            tabModel->setData(index_DY,ui->DYEdit->text());

            QModelIndex index_ZY  = tabModel->index(0,tabModel->fieldIndex("personLastZYCJ"), QModelIndex());
            tabModel->setData(index_ZY,ui->ZYEdit->text());

            QModelIndex index_fail  = tabModel->index(0,tabModel->fieldIndex("personLastFail"), QModelIndex());

            if(ui->failCheck->isChecked() == true)
                tabModel->setData(index_fail,1);
            else
                tabModel->setData(index_fail,0);
        }
        else
        {
            QModelIndex index_DY  = tabModel->index(0,tabModel->fieldIndex("personNextDYCJ"), QModelIndex());
            tabModel->setData(index_DY,ui->DYEdit->text());

            QModelIndex index_ZY  = tabModel->index(0,tabModel->fieldIndex("personNextZYCJ"), QModelIndex());
            tabModel->setData(index_ZY,ui->ZYEdit->text());

            QModelIndex index_fail  = tabModel->index(0,tabModel->fieldIndex("personNextFail"), QModelIndex());

            if(ui->failCheck->isChecked() == true)
                tabModel->setData(index_fail,1);
            else
                tabModel->setData(index_fail,0);
        }

        //进行综测计算

        QModelIndex lastD  = tabModel->index(0,tabModel->fieldIndex("personLastDYCJ"), QModelIndex());
        QModelIndex lastZ  = tabModel->index(0,tabModel->fieldIndex("personLastZYCJ"), QModelIndex());
        QModelIndex nextD  = tabModel->index(0,tabModel->fieldIndex("personNextDYCJ"), QModelIndex());
        QModelIndex nextZ  = tabModel->index(0,tabModel->fieldIndex("personNextZYCJ"), QModelIndex());

        double lastDYCJ = tabModel->data(lastD).toDouble();
        double lastZYCJ = tabModel->data(lastZ).toDouble();
        double nextDYCJ = tabModel->data(nextD).toDouble();
        double nextZYCJ = tabModel->data(nextZ).toDouble();

        qDebug() << lastDYCJ;
        qDebug() << lastZYCJ;
        qDebug() << nextDYCJ;
        qDebug() << nextZYCJ;
        QString *tmp = new QString[3];
        QString *cj = NULL;
        cj = calculate(lastDYCJ,lastZYCJ,nextDYCJ,nextZYCJ,tmp);
        tmp = NULL;
        delete tmp;

        QModelIndex index_cal_1  = tabModel->index(0,tabModel->fieldIndex("personLastZC"), QModelIndex());
        tabModel->setData(index_cal_1,cj[0]);

        QModelIndex index_cal_2  = tabModel->index(0,tabModel->fieldIndex("personNextZC"), QModelIndex());
        tabModel->setData(index_cal_2,cj[1]);

        QModelIndex index_cal_3  = tabModel->index(0,tabModel->fieldIndex("personTotalZC"), QModelIndex());
        tabModel->setData(index_cal_3,cj[2]);

        qDebug() << cj[0];
        qDebug() << cj[1];
        qDebug() << cj[2];
        cj = NULL;


        // 开始事务操作
        tabModel->database().transaction();
        if (tabModel->submitAll() && tabModel->rowCount()!=0)
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
}

void CJImport::on_searchBtn_clicked()
{
    QString sstr = ui->searchEdit->text();
    tabModel->setTable("users");//绑定学生信息表
    tabModel->setFilter(tr("personId = '%1' or personName = '%2'").arg(sstr).arg(sstr));
    /* 查询语句别写错，之前personId打错，就算用正确姓名也查询不到任何结果 */
    tabModel->select();

    if(tabModel->rowCount() < 1)
    {
        QMessageBox::critical(this,"错误","该学生信息不存在!");
    }
    else
    {
        QModelIndex  index_id = tabModel->index(0,tabModel->fieldIndex("personId"), QModelIndex());
        ui->idEdit->setText(tabModel->data(index_id).toString());

        QModelIndex index_name  = tabModel->index(0, tabModel->fieldIndex("personName"), QModelIndex());
        ui->nameEdit->setText(tabModel->data(index_name).toString());

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

        if(ui->comboBox->currentText() == "上学期")
        {

            QModelIndex index_DY  = tabModel->index(0, tabModel->fieldIndex("personLastDYCJ"), QModelIndex());
            ui->DYEdit->setText(tabModel->data(index_DY).toString());

            QModelIndex index_ZY  = tabModel->index(0, tabModel->fieldIndex("personLastZYCJ"), QModelIndex());
            ui->ZYEdit->setText(tabModel->data(index_ZY).toString());

            QModelIndex index_fail  = tabModel->index(0, tabModel->fieldIndex("personLastFail"), QModelIndex());
            if(tabModel->data(index_fail).toInt() == 1)//数据库中 1 代表有挂科
                ui->failCheck->setChecked(true);
            else
                ui->failCheck->setChecked(false);
        }
        else
        {
            QModelIndex index_DY  = tabModel->index(0, tabModel->fieldIndex("personNextDYCJ"), QModelIndex());
            ui->DYEdit->setText(tabModel->data(index_DY).toString());

            QModelIndex index_ZY  = tabModel->index(0, tabModel->fieldIndex("personNextZYCJ"), QModelIndex());
            ui->ZYEdit->setText(tabModel->data(index_ZY).toString());

            QModelIndex index_fail  = tabModel->index(0, tabModel->fieldIndex("personNextFail"), QModelIndex());
            if(tabModel->data(index_fail).toInt() == 1)//数据库中 1 代表有挂科
                ui->failCheck->setChecked(true);
            else
                ui->failCheck->setChecked(false);
        }


    }
}

void CJImport::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    //qDebug() << "窗口关闭";
    //关闭加分窗口前，执行一二三等奖的评定，并传给users表
    tabModel->setTable("users");
    tabModel->setSort(tabModel->fieldIndex("personTotalZC"),Qt::DescendingOrder);//综测检查,降序排列
    tabModel->select();

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("caculation");
    model->select();

    QModelIndex index_1 = model->index(0,model->fieldIndex("firstRange"),QModelIndex());
    int firstRange = model->data(index_1).toInt();

    QModelIndex index_2 = model->index(0,model->fieldIndex("secondRange"),QModelIndex());
    int secondRange = model->data(index_2).toInt();

    QModelIndex index_3 = model->index(0,model->fieldIndex("thirdRange"),QModelIndex());
    int thirdRange = model->data(index_3).toInt();

    QModelIndex index_4 = model->index(0,model->fieldIndex("firstMoney"),QModelIndex());
    int firstMoney = model->data(index_4).toInt();

    QModelIndex index_5 = model->index(0,model->fieldIndex("secondMoney"),QModelIndex());
    int secondMoney = model->data(index_5).toInt();

    QModelIndex index_6 = model->index(0,model->fieldIndex("thirdMoney"),QModelIndex());
    int thirdMoney = model->data(index_6).toInt();

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
}
