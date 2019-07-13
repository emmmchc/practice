#include "person.h"
#include "ui_person.h"

extern int flag;//这里需要用到flag来判断登录用户是否为学生
extern QString userID; //用来查找该学生

Person::Person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
    ui->searchEdit->setPlaceholderText("输入学号、姓名");//输入框内容类型提示
    //由于users表存储有学生的班级编号，需要relationmodel关联class
    tabModel = new QSqlTableModel(this);

    ui->lastZCEdit->setDisabled(true);
    ui->nextZCEdit->setDisabled(true);
    ui->totalZCEdit->setDisabled(true);
    //综测成绩只能通过计算，不能直接修改

    if(flag == 3)//登录的是学生,直接显示信息并设置相关权限
    {
        ui->searchBtn->setDisabled(true);
        ui->idEdit->setDisabled(true);
        ui->nameEdit->setDisabled(true);
        ui->genderEdit->setDisabled(true);
        ui->classComBox->setDisabled(true);
        ui->spinBox->setDisabled(true);
        ui->isSHS->setDisabled(true);
        ui->isGQTY->setDisabled(true);
        ui->isParty->setDisabled(true);
        ui->isXXGB->setDisabled(true);
        ui->first->setEnabled(false);
        ui->second->setEnabled(false);
        ui->third->setEnabled(false);
        //以上控件，学生不可操作

        tabModel->setTable("users");
        tabModel->setFilter(tr("personId = '%1'").arg(userID));
        //qDebug()<< userID;
        tabModel->select();
        //模型选择学生信息

        if(tabModel->rowCount() < 1)
        {
            QMessageBox::critical(this,"错误","该学生信息尚未录入该系统");
            this->reject();//退出
        }
        else
        {

            QModelIndex index_id  = tabModel->index(0,tabModel->fieldIndex("personId") , QModelIndex());
            ui->idEdit->setText(tabModel->data(index_id).toString());

            QModelIndex index_name  = tabModel->index(0, tabModel->fieldIndex("personName"), QModelIndex());
            ui->nameEdit->setText(tabModel->data(index_name).toString());

            QModelIndex index_gender  = tabModel->index(0, tabModel->fieldIndex("personGender"), QModelIndex());
            ui->genderEdit->setText(tabModel->data(index_gender).toString());

            //先将所有班级填入combobox框
            QSqlTableModel MODEL;
            MODEL.setTable("class");
            MODEL.select();
            for(int i=0; i<MODEL.rowCount(); i++)
            {
                QModelIndex index_1= MODEL.index(i,1,QModelIndex());
                ui->classComBox->addItem(MODEL.data(index_1).toString());
            }

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
                ui->classComBox->setCurrentText(m_model.data(index_m_class).toString());
            }

            //先将所有职务填入combobox框
            QSqlTableModel MODEL_1;
            MODEL_1.setTable("ZW");
            MODEL_1.select();
            for(int i=0; i<MODEL_1.rowCount(); i++)
            {
                QModelIndex index_1= MODEL_1.index(i,1,QModelIndex());
                ui->ZWComBox->addItem(MODEL_1.data(index_1).toString());
            }


            //导入职务时先查找职务字典
            QModelIndex index_ZW  = tabModel->index(0, tabModel->fieldIndex("ZWId"), QModelIndex());
            int z_ZW = tabModel->data(index_ZW).toInt();
            QSqlTableModel z_model;
            z_model.setTable("ZW");
            z_model.setFilter(tr("ZWId = '%1'").arg(z_ZW));
            z_model.select();
            if(z_model.rowCount() == 1)
            {
                QModelIndex index_z_ZW = z_model.index(0,1,QModelIndex());
                ui->ZWComBox->setCurrentText(z_model.data(index_z_ZW).toString());
            }


            QModelIndex index_last  = tabModel->index(0,tabModel->fieldIndex("personLastZC"), QModelIndex());
            ui->lastZCEdit->setText(tabModel->data(index_last).toString());

            QModelIndex index_next  = tabModel->index(0,tabModel->fieldIndex("personNextZC"), QModelIndex());
            ui->nextZCEdit->setText(tabModel->data(index_next).toString());

            QModelIndex index_total  = tabModel->index(0,tabModel->fieldIndex("personTotalZC"), QModelIndex());
            ui->totalZCEdit->setText(tabModel->data(index_total).toString());

            //下面是根据数据库内容，设置CheckedButton是否勾选
            QModelIndex index_Party  = tabModel->index(0, tabModel->fieldIndex("personParty"), QModelIndex());
            if(tabModel->data(index_Party).toInt()==1)
                ui->isParty->setChecked(true);
            else
                ui->isParty->setChecked(false);

            QModelIndex index_SHS  = tabModel->index(0, tabModel->fieldIndex("personSHS"), QModelIndex());
            if(tabModel->data(index_SHS).toInt()==1)
                ui->isSHS->setChecked(true);
            else
                ui->isSHS->setChecked(false);

            QModelIndex index_GQTY  = tabModel->index(0, tabModel->fieldIndex("personGQTY"), QModelIndex());
            if(tabModel->data(index_GQTY).toInt()==1)
                ui->isGQTY->setChecked(true);
            else
                ui->isGQTY->setChecked(false);

            QModelIndex index_XXGB  = tabModel->index(0, tabModel->fieldIndex("personXXGB"), QModelIndex());
            if(tabModel->data(index_XXGB).toInt()==1)
                ui->isXXGB->setChecked(true);
            else
                ui->isXXGB->setChecked(false);

            QModelIndex index_first  = tabModel->index(0, tabModel->fieldIndex("personAward"), QModelIndex());
            if(tabModel->data(index_first).toInt()== 1)
                ui->first->setChecked(true);
            else
                ui->first->setChecked(false);

            QModelIndex index_second  = tabModel->index(0, tabModel->fieldIndex("personAward"), QModelIndex());
            if(tabModel->data(index_second).toInt()== 2)
                ui->second->setChecked(true);
            else
                ui->second->setChecked(false);

            QModelIndex index_third  = tabModel->index(0, tabModel->fieldIndex("personAward"), QModelIndex());
            if(tabModel->data(index_third).toInt()== 3)
                ui->third->setChecked(true);
            else
                ui->third->setChecked(false);

             //奖学金spinbox设置
            QModelIndex index_bonus  = tabModel->index(0, tabModel->fieldIndex("personBonus"), QModelIndex());
            ui->spinBox->setValue(tabModel->data(index_bonus).toInt());
       }

    }
    else if(flag == 2)//部门管理员也不能修改
    {
            ui->first->setEnabled(false);
            ui->second->setEnabled(false);
            ui->third->setEnabled(false);
            ui->isSHS->setDisabled(true);
            ui->isGQTY->setDisabled(true);
            ui->isXXGB->setDisabled(true);
    }

}

Person::~Person()
{
    delete ui;
}

void Person::on_cancelBtn_clicked()
{
    this->accept();
}

void Person::on_okBtn_clicked()
{
    tabModel->setTable("users");//绑定学生信息表
    if(flag == 3) //如果是学生提出保存信息，只要把职务那一栏提交即可
    {
        QSqlTableModel model;
        model.setTable("ZW");
        QString tmp = ui->ZWComBox->currentText();
        model.setFilter(tr("ZW = '%1'").arg(tmp));
        model.select();
        QModelIndex index = model.index(0,0,QModelIndex());
        int id = model.data(index).toInt();
        //qDebug() << id;
        //进入ZW表将combobox所对应职务的id找到

        QString tmpstr = ui->idEdit->text();
        tabModel->setFilter(tr("personId = '%1'").arg(tmpstr));
        tabModel->select();//得到当前学生记录

        QModelIndex index_1 = tabModel->index(0,tabModel->fieldIndex("ZWId"),QModelIndex());
        tabModel->setData(index_1,id);
    }
    else //管理员可以修改全部信息所以要全部提交
    {

        QString tmpstr = ui->idEdit->text();
        tabModel->setFilter(tr("personId = '%1'").arg(tmpstr));
        tabModel->select();

        if(tabModel->rowCount() == 1)
        {
            QModelIndex index_id  = tabModel->index(0,tabModel->fieldIndex("personId"), QModelIndex());
            tabModel->setData(index_id,ui->idEdit->text());

            QModelIndex index_name  = tabModel->index(0, tabModel->fieldIndex("personName"), QModelIndex());
            tabModel->setData(index_name,ui->nameEdit->text());

            QModelIndex index_gender  = tabModel->index(0, tabModel->fieldIndex("personGender"), QModelIndex());
            tabModel->setData(index_gender,ui->genderEdit->text());

            //导入班级时先查找班级字典
            QString str_class = ui->classComBox->currentText();
            QSqlTableModel t_model;
            t_model.setTable("class");
            t_model.setFilter(tr("className = '%1'").arg(str_class));
            t_model.select();
            QModelIndex index_class =  t_model.index(0,0,QModelIndex());
            int tmp = t_model.data(index_class).toInt();//找到对应班级编号

            //qDebug() << tmp;
            QModelIndex index = tabModel->index(0,tabModel->fieldIndex("classId"),QModelIndex());
            tabModel->setData(index,tmp);//传入tabmodel


            //导入职务时先查找职务字典
            QString str_ZW = ui->ZWComBox->currentText();
            QSqlTableModel model_1;
            model_1.setTable("ZW");
            model_1.setFilter(tr("ZW = '%1'").arg(str_ZW));
            model_1.select();
            QModelIndex index_ZW =  model_1.index(0,0,QModelIndex());
            int tmp_1 = model_1.data(index_ZW).toInt();//找到对应职务编号
            //qDebug() << tmp_1;

            QModelIndex index_1 = tabModel->index(0,tabModel->fieldIndex("ZWId"),QModelIndex());
            tabModel->setData(index_1,tmp_1);//传入tabmodel

            QModelIndex index_last_ZC  = tabModel->index(0, tabModel->fieldIndex("personLastZC"), QModelIndex());
            tabModel->setData(index_last_ZC,ui->lastZCEdit->text());

            QModelIndex index_next_ZC  = tabModel->index(0, tabModel->fieldIndex("personNextZC"), QModelIndex());
            tabModel->setData(index_next_ZC,ui->lastZCEdit->text());

            QModelIndex index_total_ZC  = tabModel->index(0, tabModel->fieldIndex("personTotalZC"), QModelIndex());
            tabModel->setData(index_total_ZC,ui->totalZCEdit->text());

            //下面是根据CheckedButton勾选内容，将1(打钩)或0(没打钩)传入数据库
            QModelIndex index_Party  = tabModel->index(0, tabModel->fieldIndex("personParty"), QModelIndex());
            if(ui->isParty->isChecked() == true)
                tabModel->setData(index_Party,1);
            else
                tabModel->setData(index_Party,0);

            QModelIndex index_SHS  = tabModel->index(0,tabModel->fieldIndex("personSHS"), QModelIndex());
            if(ui->isSHS->isChecked() == true)
                tabModel->setData(index_SHS,1);
            else
                tabModel->setData(index_SHS,0);

            QModelIndex index_GQTY  = tabModel->index(0,tabModel->fieldIndex("personGQTY"), QModelIndex());
            if(ui->isGQTY->isChecked() == true)
                tabModel->setData(index_GQTY,1);
            else
                tabModel->setData(index_GQTY,0);

            QModelIndex index_XXGB  = tabModel->index(0,tabModel->fieldIndex("personXXGB"), QModelIndex());
            if(ui->isXXGB->isChecked() == true)
                tabModel->setData(index_XXGB,1);
            else
                tabModel->setData(index_XXGB,0);
            qDebug() << ui->isXXGB->isChecked();
             //奖学金spinbox设置
            QModelIndex index_bonus  = tabModel->index(0, tabModel->fieldIndex("personBonus"), QModelIndex());
            int jiangxuejin = ui->spinBox->value();//获取spinBox控件内的值要用value，不用text
            //qDebug() << jiangxuejin;
            tabModel->setData(index_bonus,jiangxuejin);
        }
    }
    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll() && tabModel->rowCount()!=0)
    {
        QMessageBox::information(this, "提交信息", "保存成功！",QMessageBox::Ok);
        tabModel->database().commit(); //提交
    }
    else
    {
        QMessageBox::critical(this, "错误信息",
               "提交错误,错误信息\n"+tabModel->lastError().text(),
                  QMessageBox::Ok,QMessageBox::NoButton);
        tabModel->database().rollback(); //回滚
    }
}


void Person::on_searchBtn_clicked()
{
    //管理员查找学生信息

    tabModel->setTable("users");
    QString sstr = ui->searchEdit->text();
    tabModel->setFilter(tr("personId = '%1' or personName = '%2'").arg(sstr).arg(sstr));
    tabModel->select();
    if(tabModel->rowCount() < 1)
    {
        QMessageBox::critical(this,"错误","该学生信息尚未录入该系统");
    }
    else
    {
        QModelIndex index_id  = tabModel->index(0,tabModel->fieldIndex("personId"), QModelIndex());
        ui->idEdit->setText(tabModel->data(index_id).toString());

        QModelIndex index_name  = tabModel->index(0, tabModel->fieldIndex("personName"), QModelIndex());
        ui->nameEdit->setText(tabModel->data(index_name).toString());

        QModelIndex index_gender  = tabModel->index(0, tabModel->fieldIndex("personGender"), QModelIndex());
        ui->genderEdit->setText(tabModel->data(index_gender).toString());

        //先将所有班级填入combobox框
        QSqlTableModel MODEL;
        MODEL.setTable("class");
        MODEL.select();
        for(int i=0; i<MODEL.rowCount(); i++)
        {
            QModelIndex index_1= MODEL.index(i,1,QModelIndex());
            ui->classComBox->addItem(MODEL.data(index_1).toString());
        }

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
            ui->classComBox->setCurrentText(m_model.data(index_m_class).toString());
        }

        //先将所有职务填入combobox框
        QSqlTableModel MODEL_1;
        MODEL_1.setTable("ZW");
        MODEL_1.select();
        for(int i=0; i<MODEL_1.rowCount(); i++)
        {
            QModelIndex index_1= MODEL_1.index(i,1,QModelIndex());
            ui->ZWComBox->addItem(MODEL_1.data(index_1).toString());
        }

        //导入职务时先查找职务字典
        QModelIndex index_ZW  = tabModel->index(0, tabModel->fieldIndex("ZWId"), QModelIndex());
        int z_ZW = tabModel->data(index_ZW).toInt();
        QSqlTableModel z_model;
        z_model.setTable("ZW");
        z_model.setFilter(tr("ZWId = '%1'").arg(z_ZW));
        z_model.select();
        if(z_model.rowCount() == 1)
        {
            QModelIndex index_z_ZW = z_model.index(0,1,QModelIndex());
            ui->ZWComBox->setCurrentText(z_model.data(index_z_ZW).toString());
        }

        QModelIndex index_last_ZC  = tabModel->index(0, tabModel->fieldIndex("personLastZC"), QModelIndex());
        ui->lastZCEdit->setText(tabModel->data(index_last_ZC).toString());

        QModelIndex index_next_ZC  = tabModel->index(0, tabModel->fieldIndex("personNextZC"), QModelIndex());
        ui->nextZCEdit->setText(tabModel->data(index_next_ZC).toString());

        QModelIndex index_total_ZC  = tabModel->index(0, tabModel->fieldIndex("personTotalZC"), QModelIndex());
        ui->totalZCEdit->setText(tabModel->data(index_total_ZC).toString());

        //下面是根据数据库内容，设置CheckedButton是否勾选
        QModelIndex index_Party  = tabModel->index(0, tabModel->fieldIndex("personParty"), QModelIndex());
        if(tabModel->data(index_Party).toInt()==1)
            ui->isParty->setChecked(true);
        else
            ui->isParty->setChecked(false);

        QModelIndex index_SHS  = tabModel->index(0, tabModel->fieldIndex("personSHS"), QModelIndex());
        if(tabModel->data(index_SHS).toInt()==1)
            ui->isSHS->setChecked(true);
        else
            ui->isSHS->setChecked(false);

        QModelIndex index_GQTY  = tabModel->index(0, tabModel->fieldIndex("personGQTY"), QModelIndex());
        if(tabModel->data(index_GQTY).toInt()==1)
            ui->isGQTY->setChecked(true);
        else
            ui->isGQTY->setChecked(false);

        QModelIndex index_XXGB  = tabModel->index(0,tabModel->fieldIndex("personXXGB"), QModelIndex());
        if(tabModel->data(index_XXGB).toInt()==1)
            ui->isXXGB->setChecked(true);
        else
            ui->isXXGB->setChecked(false);

        QModelIndex index_first  = tabModel->index(0, tabModel->fieldIndex("personAward"), QModelIndex());
        if(tabModel->data(index_first).toInt()== 1)
            ui->first->setChecked(true);
        else
            ui->first->setChecked(false);

        QModelIndex index_second  = tabModel->index(0, tabModel->fieldIndex("personAward"), QModelIndex());
        if(tabModel->data(index_second).toInt()== 2)
            ui->second->setChecked(true);
        else
            ui->second->setChecked(false);

        QModelIndex index_third  = tabModel->index(0, tabModel->fieldIndex("personAward"), QModelIndex());
        if(tabModel->data(index_third).toInt()== 3)
            ui->third->setChecked(true);
        else
            ui->third->setChecked(false);


         //奖学金spinbox设置
        QModelIndex index_bonus  = tabModel->index(0, tabModel->fieldIndex("personBonus"), QModelIndex());
        ui->spinBox->setValue(tabModel->data(index_bonus).toInt());
   }
}
