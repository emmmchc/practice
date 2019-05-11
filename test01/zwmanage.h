#ifndef ZWMANAGE_H
#define ZWMANAGE_H

#include <QDialog>
#include "ui_zwmanage.h"
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
#include <QTableView>
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

namespace Ui {
class ZWManage;
}

class ZWManage : public QDialog
{
    Q_OBJECT

public:
    explicit ZWManage(QWidget *parent = 0);
    ~ZWManage();

private slots:
    void on_submit_btn_clicked();

    void on_cancel_btn_clicked();

    void on_add_btn_clicked();

    void on_del_btn_clicked();

private:
    Ui::ZWManage *ui;
    QSqlRelationalTableModel *tabModel;//数据模型
};

#endif // ZWMANAGE_H
