#ifndef EXCELLENCEAPPLY_H
#define EXCELLENCEAPPLY_H

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
class ExcellenceApply;
}

class ExcellenceApply : public QDialog
{
    Q_OBJECT

public:
    explicit ExcellenceApply(QWidget *parent = 0);
    ~ExcellenceApply();

private slots:
    void on_okBtn_clicked();

    void on_XXGBchkBox_clicked(bool checked);

    void on_SHSchkBox_clicked(bool checked);

    void on_GQTYchkBox_clicked(bool checked);

private:
    Ui::ExcellenceApply *ui;
    QSqlTableModel *tabModel;
};

#endif // EXCELLENCEAPPLY_H
