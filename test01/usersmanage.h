#ifndef USERSMANAGE_H
#define USERSMANAGE_H

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
#include "qwcomboboxdelegate.h"

namespace Ui {
class UsersManage;
}

class UsersManage : public QDialog
{
    Q_OBJECT

public:
    explicit UsersManage(QWidget *parent = 0);
    ~UsersManage();

private slots:
    void on_submit_btn_clicked();

    void on_cancel_btn_clicked();

    void on_add_btn_clicked();

    void on_del_btn_clicked();

private:
    Ui::UsersManage *ui;
    QSqlRelationalTableModel *tabModel;//数据模型
    QWComboBoxDelegate   delegateType; //自定义数据代理，管理员类别
    QWComboBoxDelegate   delegateGender; //自定义数据代理，性别
    QItemSelectionModel *theSelection; //选择模型
};


#endif // USERSMANAGE_H
