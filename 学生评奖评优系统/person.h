#ifndef PERSON_H
#define PERSON_H

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

namespace Ui {
class Person;
}

class Person : public QDialog
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = 0);
    ~Person();

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::Person *ui;
    QSqlTableModel *tabModel;//数据模型
};

#endif // PERSON_H
