#ifndef NOEDITDELEGATE_H
#define NOEDITDELEGATE_H

#include <QStyledItemDelegate>

class NoEditDelegate:public QStyledItemDelegate
{
public:
    NoEditDelegate(QObject *parent=0);
    ~NoEditDelegate();
    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // NOEDITDELEGATE_H
