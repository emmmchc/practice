#ifndef AUDITADDSCORE_H
#define AUDITADDSCORE_H

#include <QDialog>
#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QSqlError>
#include "qdlglogin.h"
#include <QLineEdit>
#include <QCompleter>
#include <QObject>
#include <QSqlTableModel>
#include <QTableView> // show table
#include <QItemDelegate>
#include <QComboBox>
#include <QCheckBox>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QStyledItemDelegate>
#include <QRect>
#include <QApplication>
#include <QStyleOptionButton>
#include <QPushButton>
#include <QCloseEvent>
#include "regulation.h"

namespace Ui {
class AuditAddScore;
}

class AuditAddScore : public QDialog
{
    Q_OBJECT

public:
    explicit AuditAddScore(QWidget *parent = 0);
    ~AuditAddScore();

private:
    Ui::AuditAddScore *ui;
    QSqlRelationalTableModel * tabModel;
    //NoEditDelegate   delegateNoEdit; //自定义代理，设置某行或者某列不可编辑

protected:					//添加
     void closeEvent(QCloseEvent *event);//函数重载，作用是在该窗口关闭所要执行的操作

private slots:
    void StartOperate();//自定义槽函数，执行点击tableView后的操作

    void on_okBtn_clicked();
};

#endif // AUDITADDSCORE_H
