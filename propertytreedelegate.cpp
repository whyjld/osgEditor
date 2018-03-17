#include "propertytreedelegate.h"
#include "propertytreeitem.h"

#include <QTreeView>

PropertyTreeDelegate::PropertyTreeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget* PropertyTreeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr != item)
    {
        QWidget* editor = nullptr;
        if(item->createEditor(editor, parent, option, index))
        {
            return editor;
        }
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void PropertyTreeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr == item || !item->setEditorData(editor, index))
    {
        return QStyledItemDelegate::setEditorData(editor, index);
    }
}

void PropertyTreeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr == item || !item->setModelData(editor, model, index))
    {
        return QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void PropertyTreeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr == item || !item->updateEditorGeometry(editor, option, index))
    {
        return QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    }
}
