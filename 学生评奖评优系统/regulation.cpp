#include "regulation.h"
#include "ui_regulation.h"
#include "QSqlTableModel"
#include "QModelIndex"
#include "QDebug"

extern int flag;

Regulation::Regulation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regulation)
{
    ui->setupUi(this);

    model.setTable("caculation");
    model.setEditStrategy(QSqlTableModel::OnFieldChange);//当输入框内容改变时，数据库内容也会同时更新
    model.select();

    QModelIndex index_1 = model.index(0,model.fieldIndex("lastD"),QModelIndex());
    ui->lastDEdit->setText(model.data(index_1).toString());

    QModelIndex index_2 = model.index(0,model.fieldIndex("lastZ"),QModelIndex());
    ui->lastZEdit->setText(model.data(index_2).toString());

    QModelIndex index_3 = model.index(0,model.fieldIndex("lastT"),QModelIndex());
    ui->lastTEdit->setText(model.data(index_3).toString());

    QModelIndex index_4 = model.index(0,model.fieldIndex("nextD"),QModelIndex());
    ui->nextDEdit->setText(model.data(index_4).toString());

    QModelIndex index_5 = model.index(0,model.fieldIndex("nextZ"),QModelIndex());
    ui->nextZEdit->setText(model.data(index_5).toString());

    QModelIndex index_6 = model.index(0,model.fieldIndex("nextT"),QModelIndex());
    ui->nextTEdit->setText(model.data(index_6).toString());

    QModelIndex index_7 = model.index(0,model.fieldIndex("firstRange"),QModelIndex());
    ui->firstRangeEdit->setText(model.data(index_7).toString());

    QModelIndex index_8 = model.index(0,model.fieldIndex("secondRange"),QModelIndex());
    ui->secondRangeEdit->setText(model.data(index_8).toString());

    QModelIndex index_9 = model.index(0,model.fieldIndex("thirdRange"),QModelIndex());
    ui->thirdRangeEdit->setText(model.data(index_9).toString());

    QModelIndex index_10 = model.index(0,model.fieldIndex("XXGBRange"),QModelIndex());
    ui->XXGBRangeEdit->setText(model.data(index_10).toString());

    QModelIndex index_11 = model.index(0,model.fieldIndex("GQTYRange"),QModelIndex());
    ui->GQTYRangeEdit->setText(model.data(index_11).toString());

    QModelIndex index_12 = model.index(0,model.fieldIndex("SHSRange"),QModelIndex());
    ui->SHSRangeEdit->setText(model.data(index_12).toString());

    QModelIndex index_13 = model.index(0,model.fieldIndex("firstMoney"),QModelIndex());
    ui->firstMoneyEdit->setText(model.data(index_13).toString());

    QModelIndex index_14 = model.index(0,model.fieldIndex("secondMoney"),QModelIndex());
    ui->secondMoneyEdit->setText(model.data(index_14).toString());

    QModelIndex index_15 = model.index(0,model.fieldIndex("thirdMoney"),QModelIndex());
    ui->thirdMoneyEdit->setText(model.data(index_15).toString());

    if(flag == 3)
    {
        ui->lastDEdit->setEnabled(false);
        ui->lastZEdit->setEnabled(false);
        ui->lastTEdit->setEnabled(false);
        ui->nextDEdit->setEnabled(false);
        ui->nextZEdit->setEnabled(false);
        ui->nextTEdit->setEnabled(false);
        ui->firstMoneyEdit->setEnabled(false);
        ui->firstRangeEdit->setEnabled(false);
        ui->secondMoneyEdit->setEnabled(false);
        ui->secondRangeEdit->setEnabled(false);
        ui->thirdMoneyEdit->setEnabled(false);
        ui->thirdRangeEdit->setEnabled(false);
        ui->GQTYRangeEdit->setEnabled(false);
        ui->XXGBRangeEdit->setEnabled(false);
        ui->SHSRangeEdit->setEnabled(false);
    }
}

Regulation::~Regulation()
{
    delete ui;
}


//改变输入框内容触发相应槽函数

void Regulation::on_lastDEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("lastD"), QModelIndex());
    model.setData(index,arg1);
    //qDebug() << arg1;
}


void Regulation::on_lastZEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("lastZ"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_nextZEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("nextZ"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_lastTEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("lastT"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_nextDEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("nextD"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_nextTEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("nextT"), QModelIndex());
    model.setData(index,arg1);
}


void Regulation::on_firstRangeEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("firstRange"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_firstMoneyEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("firstMoney"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_secondRangeEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("secondRange"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_secondMoneyEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("secondMoney"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_thirdRangeEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("thirdRange"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_thirdMoneyEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("thirdMoney"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_GQTYRangeEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("GQTYRange"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_XXGBRangeEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("XXGBRange"), QModelIndex());
    model.setData(index,arg1);
}

void Regulation::on_SHSRangeEdit_textChanged(const QString &arg1)
{
    QModelIndex index  = model.index(0, model.fieldIndex("SHSRange"), QModelIndex());
    model.setData(index,arg1);
}

QString *calculate(double lastDYCJ,double lastZYCJ,double nextDYCJ,double nextZYCJ,QString *tmp)
{
    //提取calculation表中的六个权重
    QSqlTableModel model_cal;
    model_cal.setTable("caculation");
    model_cal.select();
    //qDebug() << model_cal.rowCount();
    QModelIndex index_lastDY  = model_cal.index(0,model_cal.fieldIndex("lastD"), QModelIndex());
    QModelIndex index_lastZY  = model_cal.index(0,model_cal.fieldIndex("lastZ"), QModelIndex());
    QModelIndex index_nextDY  = model_cal.index(0,model_cal.fieldIndex("nextD"), QModelIndex());
    QModelIndex index_nextZY  = model_cal.index(0,model_cal.fieldIndex("nextZ"), QModelIndex());
    QModelIndex index_lastT  = model_cal.index(0,model_cal.fieldIndex("lastT"), QModelIndex());
    QModelIndex index_nextT  = model_cal.index(0,model_cal.fieldIndex("nextT"), QModelIndex());

    double lastDY = model_cal.data(index_lastDY).toDouble();
    double lastZY = model_cal.data(index_lastZY).toDouble();
    double nextDY = model_cal.data(index_nextDY).toDouble();
    double nextZY = model_cal.data(index_nextZY).toDouble();
    double lastT = model_cal.data(index_lastT).toDouble();
    double nextT = model_cal.data(index_nextT).toDouble();

    double lastZC = lastDYCJ * lastDY + lastZYCJ * lastZY;
    double nextZC = nextDYCJ * nextDY + nextZYCJ * nextZY;
    double totalZC = lastZC * lastT + nextZC * nextT ;

    //将double类型数据保留两位小数
    QString str_1 = QString::number(lastZC, 'f', 2);
    QString str_2 = QString::number(nextZC, 'f', 2);
    QString str_3 = QString::number(totalZC, 'f', 2);

    tmp[0] = str_1;
    tmp[1] = str_2;
    tmp[2] = str_3;
    return tmp;
}


QString *calculate(double lastZC,double nextZC,QString *tmp)
{
    //提取calculation表中的权重
    QSqlTableModel model_cal;
    model_cal.setTable("caculation");
    model_cal.select();
    //qDebug() << model_cal.rowCount();
    //QModelIndex index_lastDY  = model_cal.index(0,model_cal.fieldIndex("lastD"), QModelIndex());
    //QModelIndex index_lastZY  = model_cal.index(0,model_cal.fieldIndex("lastZ"), QModelIndex());
    //QModelIndex index_nextDY  = model_cal.index(0,model_cal.fieldIndex("nextD"), QModelIndex());
    //QModelIndex index_nextZY  = model_cal.index(0,model_cal.fieldIndex("nextZ"), QModelIndex());
    QModelIndex index_lastT  = model_cal.index(0,model_cal.fieldIndex("lastT"), QModelIndex());
    QModelIndex index_nextT  = model_cal.index(0,model_cal.fieldIndex("nextT"), QModelIndex());

    double lastT = model_cal.data(index_lastT).toDouble();
    double nextT = model_cal.data(index_nextT).toDouble();
;
    double totalZC = lastZC * lastT + nextZC * nextT ;

    //将double类型数据保留两位小数
    QString str_1 = QString::number(totalZC, 'f', 2);

    tmp[0] = str_1;
    return tmp;
}


