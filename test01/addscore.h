#ifndef ADDSCORE_H
#define ADDSCORE_H

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
class AddScore;
}

class AddScore : public QDialog
{
    Q_OBJECT

public:
    explicit AddScore(QWidget *parent = 0);
    ~AddScore();

private slots:
    void on_okBtn_clicked();

private:
    Ui::AddScore *ui;
    QSqlTableModel *tabModel;

};

#endif // ADDSCORE_H
