#ifndef PJPYRESULT_H
#define PJPYRESULT_H

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


namespace Ui {
class PJPYResult;
}

class PJPYResult : public QDialog
{
    Q_OBJECT

public:
    explicit PJPYResult(QWidget *parent = 0);
    ~PJPYResult();

private slots:
    void on_searchBtn_clicked();

private:
    Ui::PJPYResult *ui;
    QSqlRelationalTableModel * tabModel;
};

#endif // PJPYRESULT_H
