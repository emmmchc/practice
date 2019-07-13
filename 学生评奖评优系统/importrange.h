#ifndef IMPORTRANGE_H
#define IMPORTRANGE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QModelIndex>
#include <QAxObject>
#include <QFileDialog>

#include "regulation.h"  //引入综测计算函数

namespace Ui {
class ImportRange;
}

class ImportRange : public QDialog
{
    Q_OBJECT

public:
    explicit ImportRange(QWidget *parent = 0);
    ~ImportRange();
    void readExcel(QString filePath);
    void castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res);
private slots:
    void on_okBtn_clicked();

private:
    Ui::ImportRange *ui;
    QSqlTableModel *tabModel;
};

#endif // IMPORTRANGE_H
