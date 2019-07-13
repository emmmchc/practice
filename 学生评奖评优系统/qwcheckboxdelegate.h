#ifndef QWCHECKBOXDELEGATE_H
#define QWCHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QApplication>
#include <QDebug>

class QWCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QWCheckBoxDelegate(QObject *parent = 0);
    void setColumn(int col);

protected:
    void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
    bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);

private:
    int column;         //设置复选框的列

};

#endif // QWCHECKBOXDELEGATE_H
