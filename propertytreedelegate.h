#ifndef PROPERTYTREEDELEGATE_H
#define PROPERTYTREEDELEGATE_H

#include <QStyledItemDelegate>

class PropertyTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit PropertyTreeDelegate(QObject *parent = nullptr);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
#endif // PROPERTYTREEDELEGATE_H
