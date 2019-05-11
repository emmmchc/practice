#ifndef PERSONADD_H
#define PERSONADD_H

#include <QDialog>
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
#include "qwcheckboxdelegate.h"
#include "noeditdelegate.h"

namespace Ui {
class PersonAdd;
}

class PersonAdd : public QDialog
{
    Q_OBJECT

public:
    explicit PersonAdd(QWidget *parent = 0);
    ~PersonAdd();

private slots:
    void on_submit_btn_clicked();

    void on_cancel_btn_clicked();


    void on_backBtn_clicked();

private:
    Ui::PersonAdd *ui;
    QSqlRelationalTableModel *tabModel;//数据模型
    QWComboBoxDelegate   delegateGender; //自定义数据代理，性别
    QWCheckBoxDelegate   delegateParty; //自定义数据代理，党员
    QWCheckBoxDelegate   delegateSHS; //自定义数据代理，三好生
    QWCheckBoxDelegate   delegateGQTY; //自定义数据代理，优秀共青团员
    QWCheckBoxDelegate   delegateXXGB; //自定义数据代理，优秀学生干部
    QWCheckBoxDelegate   delegateLastFail; //自定义数据代理，挂科记录(上)
    QWCheckBoxDelegate   delegateNextFail; //自定义数据代理，挂科记录(下)
    NoEditDelegate   delegateNoEdit; //自定义代理，设置某行或者某列不可编辑
};

#endif // PERSONADD_H
