#include "propertytreedelegate.h"
#include "propertytreeitem.h"

#include <QTreeView>

PropertyTreeDelegate::PropertyTreeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void PropertyTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr != item)
    {
       if(!item->paint(painter, option, index))
       {
           QStyledItemDelegate::paint(painter, option, index);
           item->afterPaint(painter, option, index);
       }
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}


QSize PropertyTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr != item)
    {
        QSize size;
        if(item->sizeHint(size, option, index))
        {
            return size;
        }
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

bool PropertyTreeDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    PropertyTreeItem* item = (PropertyTreeItem*)index.internalPointer();
    if(nullptr != item)
    {
        if(item->editorEvent(event, model, option, index))
        {
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
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
