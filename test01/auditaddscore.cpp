#include "auditaddscore.h"
#include "ui_auditaddscore.h"

AuditAddScore::AuditAddScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuditAddScore)
{
    ui->setupUi(this);
    tabModel = new QSqlRelationalTableModel(this);
    ui->tableView->setModel(tabModel);
    tabModel->setTable("post");
    tabModel->setFilter("postAdd = '1'");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setHeaderData(tabModel->fieldIndex("personId"),Qt::Horizontal,"学号");
    tabModel->setHeaderData(tabModel->fieldIndex("personName"),Qt::Horizontal,"姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("personGender"),Qt::Horizontal,"性别");
    tabModel->setHeaderData(tabModel->fieldIndex("classId"),Qt::Horizontal,"班级");

    //ui->tableView->setItemDelegate(new NoEditDelegate);
    //只能选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //单击选中
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //隐藏不需要显示的列
    ui->tableView->setColumnHidden(tabModel->fieldIndex("id"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postAdd"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postSHS"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postGQTY"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postXXGB"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("isLast"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("score"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("addReason"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("excelReason"),true);

    //将classid 与class表关联
    tabModel->setRelation(tabModel->fieldIndex("classId"),QSqlRelation("class","classId","className"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    tabModel->select();

    connect(ui->tableView->selectionModel(),
               SIGNAL(currentRowChanged(const QModelIndex &,
                                        const QModelIndex &)),
               this, SLOT(StartOperate()));

}

AuditAddScore::~AuditAddScore()
{
    delete ui;
}

void AuditAddScore::StartOperate()
{

    //获取选中行内容，依次填入界面相应控件
    int row= ui->tableView->currentIndex().row();
    //qDebug() << row;
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("post");
    model->setFilter("postAdd = '1'");
    model->select();
    //qDebug() << row;
    QModelIndex index_id = model->index(row,model->fieldIndex("personId"));
    ui->idEdit->setText(model->data(index_id).toString());

    QModelIndex index_name = model->index(row,model->fieldIndex("personName"));
    ui->nameEdit->setText(model->data(index_name).toString());

    //导入班级时先查找班级字典
    QModelIndex index_class  = model->index(row, model->fieldIndex("classId"));
    int m_class = model->data(index_class).toInt();

    QSqlTableModel m_model;
    m_model.setTable("class");
    m_model.setFilter(tr("classId = '%1'").arg(m_class));
    m_model.select();
    if(m_model.rowCount() == 1)
    {
        QModelIndex index_m_class = m_model.index(0,1,QModelIndex());
        ui->classEdit->setText(m_model.data(index_m_class).toString());
    }

    QModelIndex index_isLast = model->index(row,tabModel->fieldIndex("isLast"));
    int k = model->data(index_isLast).toInt();

    if(k)
        ui->comboBox->setCurrentText("上学期");
    else
        ui->comboBox->setCurrentText("下学期");

    QModelIndex index_score = model->index(row,tabModel->fieldIndex("score"));
    ui->spinBox->setValue(model->data(index_score).toDouble());

    QModelIndex index_text = model->index(row,tabModel->fieldIndex("addReason"));
    ui->textEdit->setPlainText(model->data(index_text).toString());
}

void AuditAddScore::on_okBtn_clicked()
{
    //将同意加分的综测加回users表中，并在post表中删除该条记录
    int row= ui->tableView->currentIndex().row();

    if(ui->comboBox->currentText() == "上学期")
    {
        double d_add_zc = ui->spinBox->value();

        QSqlTableModel *model = new QSqlTableModel();
        model->setTable("users");
        model->setFilter(tr("personId = '%1'").arg(ui->idEdit->text()));
        model->select();

        QModelIndex index_zc = model->index(0,model->fieldIndex("personLastZC"));
        QString str_zc = model->data(index_zc).toString();
        double ZC = d_add_zc + str_zc.toDouble();

        model->setData(index_zc,ZC);
        model->submitAll();
    }
    else
    {
        double d_add_zc = ui->spinBox->value();

        QSqlTableModel *model = new QSqlTableModel();
        model->setTable("users");
        model->setFilter(tr("personId = '%1'").arg(ui->idEdit->text()));
        model->select();
        QModelIndex index_zc = model->index(0,model->fieldIndex("personNextZC"));
        QString str_zc = model->data(index_zc).toString();
        double ZC = d_add_zc + str_zc.toDouble();
        model->setData(index_zc,ZC);
        model->submitAll();
    }

    tabModel->removeRow(row);
    tabModel->submitAll();
    ui->tableView->setModel(tabModel);
    tabModel->setTable("post");
    tabModel->setFilter("postAdd = '1'");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setHeaderData(tabModel->fieldIndex("personId"),Qt::Horizontal,"学号");
    tabModel->setHeaderData(tabModel->fieldIndex("personName"),Qt::Horizontal,"姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("personGender"),Qt::Horizontal,"性别");
    tabModel->setHeaderData(tabModel->fieldIndex("classId"),Qt::Horizontal,"班级");

    //ui->tableView->setItemDelegate(new NoEditDelegate);
    //只能选中单行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //单击选中
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //隐藏不需要显示的列
    ui->tableView->setColumnHidden(tabModel->fieldIndex("id"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postAdd"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postSHS"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postGQTY"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("postXXGB"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("isLast"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("score"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("addReason"),true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("excelReason"),true);

    //将classid 与class表关联
    tabModel->setRelation(tabModel->fieldIndex("classId"),QSqlRelation("class","classId","className"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    tabModel->select();

}


void AuditAddScore::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    //进行综测计算
    QString id = ui->idEdit->text();
    tabModel->setTable("users");
    tabModel->setFilter(tr("personId = '%1'").arg(id));
    tabModel->select();

    QModelIndex lastT  = tabModel->index(0,tabModel->fieldIndex("personLastZC"), QModelIndex());
    QModelIndex nextT  = tabModel->index(0,tabModel->fieldIndex("personNextZC"), QModelIndex());

    double lastZC = tabModel->data(lastT).toDouble();
    double nextZC = tabModel->data(nextT).toDouble();

    qDebug() << lastZC;
    qDebug() << nextZC;
    QString *tmp = new QString();
    QString *cj = NULL;
    cj = calculate(lastZC,nextZC,tmp);
    tmp = NULL;
    delete tmp;

    QModelIndex index_cal_3  = tabModel->index(0,tabModel->fieldIndex("personTotalZC"), QModelIndex());
    tabModel->setData(index_cal_3,cj[0]);

    qDebug() << cj[0];
    cj = NULL;


    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll() && tabModel->rowCount()!=0)
        tabModel->database().commit(); //提交
    else
        tabModel->database().rollback(); //回滚

    //qDebug() << "窗口关闭";
    //关闭加分窗口前，执行一二三等奖的评定，并传给users表
    tabModel->setTable("users");
    tabModel->setSort(tabModel->fieldIndex("personTotalZC"),Qt::DescendingOrder);//综测检查,降序排列
    tabModel->select();

    int first = (4/100.0) * tabModel->rowCount();//把0 到 first -1  行的记录取出来

    int second = (20/100.0) * tabModel->rowCount();//把0 到 second -1  行的记录取出来

    int third = (40/100.0) * tabModel->rowCount();//把0 到 third -1  行的记录取出来

    //qDebug() << second;
    //qDebug() << third;

    //以下授予其一等奖
    for(int i=0; i < first; i++)
    {
        QModelIndex index_first = tabModel->index(i,tabModel->fieldIndex("personAward"));
        tabModel->setData(index_first,1);//1代表一等奖，以此类推

        QModelIndex index_bonus = tabModel->index(i,tabModel->fieldIndex("personBonus"));
        tabModel->setData(index_bonus,1500); //一等奖学金1500元;
    }

    //以下授予其二等奖
    for(int i=first; i < second; i++)
    {
        QModelIndex index_second = tabModel->index(i,tabModel->fieldIndex("personAward"));
        tabModel->setData(index_second,2);

        QModelIndex index_bonus = tabModel->index(i,tabModel->fieldIndex("personBonus"));
        tabModel->setData(index_bonus,750); //二等奖学金750元;
    }
    //以下授予其三等奖
    for(int i=second; i < third; i++)
    {
        QModelIndex index_third = tabModel->index(i,tabModel->fieldIndex("personAward"));
        tabModel->setData(index_third,3);

        QModelIndex index_bonus = tabModel->index(i,tabModel->fieldIndex("personBonus"));
        tabModel->setData(index_bonus,300); //三等奖学金300元;
    }
    // 开始事务操作
    tabModel->database().transaction();
    if (tabModel->submitAll())
        tabModel->database().commit(); //提交
    else
    {
        tabModel->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(tabModel->lastError().text()));
    }
}
