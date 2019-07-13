#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "personinformation.h"
#include "usersmanage.h"
#include "person.h"
#include "classmanage.h"
#include "zwmanage.h"
#include "qdlglogin.h"
#include "about.h"
#include "pjpyresult.h"
#include "regulation.h"
#include "cjimport.h"
#include "addscore.h"
#include "excellenceapply.h"
#include "auditaddscore.h"
#include "auditmanage.h"
#include "pjpyresult.h"
#include "importrange.h"
#include "qdlglogin.h"
#include "editpwd.h"
#include <QAxObject>
#include <QFileDialog>


static const int EXIT_CODE_REBOOT = -123456789;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actManage_triggered();

    void on_actDetail_triggered();

    void on_actSearchPerson_triggered();

    void on_actClass_triggered();

    void on_actExit_triggered();


    void on_actAbout_triggered();

    void on_actResult_triggered();

    void on_actCJImport_triggered();

    void on_actAddScore_triggered();

    void on_actZW_triggered();

    void on_actExcel_triggered();

    void on_actAudit_triggered();

    void on_actAuditExcel_triggered();

    void on_actImport_triggered();

    void on_actChange_triggered();

    void on_actEditPwd_triggered();

private:
    Ui::MainWindow *ui;
    UsersManage *ui_usersManage;
    Person *ui_person;
    ClassManage *ui_class;
    ZWManage *ui_zw;
    about *ui_about;
    PJPYResult *ui_result;
    Regulation *ui_reg;
    CJImport *ui_cj_import;
    AddScore *ui_add_score;
    ExcellenceApply *ui_excel_apply;
    AuditAddScore *ui_audit_add_score;
    AuditManage *ui_audit_excel;
    PJPYResult *ui_pjpy_result;
    ImportRange *ui_rang;
    EditPwd *ui_edit_pwd;
};

#endif // MAINWINDOW_H
