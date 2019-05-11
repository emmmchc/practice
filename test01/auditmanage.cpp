#include "auditmanage.h"
#include "ui_auditmanage.h"

AuditManage::AuditManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuditManage)
{
    ui->setupUi(this);

    tabModel = new QSqlRelationalTableModel(this);
    ui->tableView->setModel(tabModel);
    tabModel->setTable("post");
    tabModel->setFilter("postAdd = '0'");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setHeaderData(tabModel->fieldIndex("personId"),Qt::Horizontal,"学号");
    tabModel->setHeaderData(tabModel->fieldIndex("personName"),Qt::Horizontal,"姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("personGender"),Qt::Horizontal,"性别");
    tabModel->setHeaderData(tabModel->fieldIndex("classId"),Qt::Horizontal,"班级");
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

AuditManage::~AuditManage()
{
    delete ui;
}

void AuditManage::StartOperate()
{

    //获取选中行内容，依次填入界面相应控件
    int row= ui->tableView->currentIndex().row();
    //qDebug() << row;
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("post");
    model->setFilter("postAdd = '0'");
    model->select();
    //qDebug() << row;
    QModelIndex index_id = model->index(row,model->fieldIndex("personId"));
    ui->idEdit->setText(model->data(index_id).toString());

    QModelIndex index_name = model->index(row,model->fieldIndex("personName"));
    ui->nameEdit->setText(model->data(index_name).toString());

    QModelIndex index_gender = model->index(row,model->fieldIndex("personGender"));
    ui->genderEdit->setText(model->data(index_gender).toString());

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

    //将申请的评优项选中
    QModelIndex index_SHS  = model->index(row, model->fieldIndex("postSHS"));
    if(model->data(index_SHS) == 1)
        ui->SHSchkBox->setChecked(true);
    else
        ui->SHSchkBox->setChecked(false);

    QModelIndex index_GQTY  = model->index(row, model->fieldIndex("postGQTY"));
    if(model->data(index_GQTY) == 1)
        ui->GQTYchkBox->setChecked(true);
    else
           ui->GQTYchkBox->setChecked(false);

    QModelIndex index_XXGB  = model->index(row, model->fieldIndex("postXXGB"));
    if(model->data(index_XXGB) == 1)
        ui->XXGBchkBox->setChecked(true);
    else
        ui->XXGBchkBox->setChecked(false);

    //qDebug() << row;
    QModelIndex index_text = model->index(row,tabModel->fieldIndex("excelReason"));
    //qDebug() << model->data(index_text).toString();
    ui->textEdit->setPlainText(model->data(index_text).toString());

}

void AuditManage::on_okBtn_clicked()
{
    //将审核通过的评优存回users表中，并在post表中删除该条记录
    int row= ui->tableView->currentIndex().row();

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("users");
    model->setFilter(tr("personId = '%1'").arg(ui->idEdit->text()));
    model->select();

    //提取该名学生班级编号
    QModelIndex index_classId = model->index(0,model->fieldIndex("classId"));
    QString str_classId = model->data(index_classId).toString();

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

    pjpy.setData(index_id,ui->idEdit->text());
    pjpy.setData(index_name,ui->nameEdit->text());
    pjpy.setData(index_gender,ui->genderEdit->text());
    pjpy.setData(index_CLASSId,str_classId.toInt());

    if(ui->GQTYchkBox->isChecked() == true)
        pjpy.setData(index_awardId,4);
    else if(ui->SHSchkBox->isChecked() == true)
        pjpy.setData(index_awardId,5);
    else if(ui->XXGBchkBox->isChecked() == true)
        pjpy.setData(index_awardId,6);

    pjpy.submitAll();


    bool SHS = ui->SHSchkBox->isChecked();
    QModelIndex index_SHS = model->index(0,model->fieldIndex("personSHS"));
    if(SHS)
        model->setData(index_SHS,1);

    bool GQTY = ui->GQTYchkBox->isChecked();
    QModelIndex index_GQTY = model->index(0,model->fieldIndex("personGQTY"));
    if(GQTY)
        model->setData(index_GQTY,1);

    bool XXGB = ui->XXGBchkBox->isChecked();
    QModelIndex index_XXGB = model->index(0,model->fieldIndex("personXXGB"));
    if(XXGB)
        model->setData(index_XXGB,1);

    model->submitAll();


    tabModel->removeRow(row);
    tabModel->submitAll();
    ui->tableView->setModel(tabModel);
    tabModel->setTable("post");
    tabModel->setFilter("postAdd = '0'");
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
