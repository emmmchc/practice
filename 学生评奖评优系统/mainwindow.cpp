#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(flag==1)
    {
        ;
    }
    else if(flag==2)
    {
        ui->actManage->setEnabled(false);//账户管理
        ui->actAddScore->setEnabled(false);//加分申请
        ui->actExcel->setEnabled(false);//评优申请
        ui->actImport->setEnabled(false);//批量导入
    }
    else
    {
        ui->actManage->setEnabled(false);//账户管理
        ui->actClass->setEnabled(false);//班级管理
        ui->actAuditExcel->setEnabled(false);//评优审核
        ui->actAudit->setEnabled(false);//加分审核
        ui->actZW->setEnabled(false);//职务管理
        ui->actCJImport->setEnabled(false);//成绩录入
        ui->actImport->setEnabled(false);//批量导入
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actManage_triggered()
{
    //创建窗口对象，this指定新窗口父类为MainWindow
    ui_usersManage = new UsersManage(this);
    ui_usersManage->setModal(true);//设置窗口为模态，未关闭前不能与该应用其他窗口交互。
    ui_usersManage->show();
}

void MainWindow::on_actDetail_triggered()
{
    ui_reg = new Regulation(this);
    ui_reg->setModal(true);
    ui_reg->show();
}

void MainWindow::on_actSearchPerson_triggered()
{
    ui_person = new Person(this);
    ui_person->setModal(true);
    ui_person->show();
}

void MainWindow::on_actClass_triggered()
{
    ui_class = new ClassManage(this);
    ui_class->setModal(true);
    ui_class->show();
}

void MainWindow::on_actExit_triggered()
{
    this->close();
}


void MainWindow::on_actAbout_triggered()
{
    ui_about = new about(this);
    ui_about->setModal(true);
    ui_about->show();
}

void MainWindow::on_actResult_triggered()
{
    ui_result = new PJPYResult(this);
    ui_result->setModal(true);
    ui_result->show();
}

void MainWindow::on_actCJImport_triggered()
{
    ui_cj_import = new CJImport(this);
    ui_cj_import->setModal(true);
    ui_cj_import->show();
}

void MainWindow::on_actAddScore_triggered()
{
    ui_add_score = new AddScore(this);
    ui_add_score->setModal(true);
    ui_add_score->show();
}

void MainWindow::on_actZW_triggered()
{
    ui_zw = new ZWManage(this);
    ui_zw->setModal(true);
    ui_zw->show();
}

void MainWindow::on_actExcel_triggered()
{
    ui_excel_apply = new ExcellenceApply(this);
    ui_excel_apply->setModal(true);
    ui_excel_apply->show();
}


void MainWindow::on_actAudit_triggered()
{
    ui_audit_add_score = new AuditAddScore(this);
    ui_audit_add_score->setModal(true);
    ui_audit_add_score->show();
}

void MainWindow::on_actAuditExcel_triggered()
{
    ui_audit_excel = new AuditManage(this);
    ui_audit_excel->setModal(true);
    ui_audit_excel->show();
}

void MainWindow::on_actImport_triggered()
{
    ui_rang = new ImportRange(this);
    ui_rang->setModal(true);
    ui_rang->show();
}


void MainWindow::on_actChange_triggered()
{
    qApp->exit(888);//设置重启程序 返回888
}

void MainWindow::on_actEditPwd_triggered()
{
    ui_edit_pwd = new EditPwd(this);
    ui_edit_pwd->setModal(true);
    ui_edit_pwd->show();
}
