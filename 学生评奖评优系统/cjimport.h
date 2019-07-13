#ifndef CJIMPORT_H
#define CJIMPORT_H

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
#include "regulation.h"
#include <QCloseEvent>
namespace Ui {
class CJImport;
}

class CJImport : public QDialog
{
    Q_OBJECT

public:
    explicit CJImport(QWidget *parent = 0);
    ~CJImport();

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

    void on_searchBtn_clicked();

protected:					//添加
     void closeEvent(QCloseEvent *event);//函数重载，作用是在该窗口关闭所要执行的操作
private:
    Ui::CJImport *ui;
    QSqlTableModel *tabModel;

};

#endif // CJIMPORT_H
