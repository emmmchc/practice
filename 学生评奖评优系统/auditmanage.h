#ifndef AUDITMANAGE_H
#define AUDITMANAGE_H

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
class AuditManage;
}

class AuditManage : public QDialog
{
    Q_OBJECT

public:
    explicit AuditManage(QWidget *parent = 0);
    ~AuditManage();

private:
    Ui::AuditManage *ui;
    QSqlRelationalTableModel * tabModel;
private slots:
    void StartOperate();
    void on_okBtn_clicked();
    void on_cancleBtn_clicked();
};

#endif // AUDITMANAGE_H
