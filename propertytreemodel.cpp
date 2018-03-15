#include "propertytreemodel.h"
#include "propertytreeitem.h"
#include <QStringList>
#include <QColor>
#include <QBrush>
#include <QFont>

#include <osg/Geode>
#include <osg/Group>

PropertyTreeModel::PropertyTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_RootItem(new PropertyTreeItem())
{
}

PropertyTreeModel::~PropertyTreeModel()
{
}

int PropertyTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<PropertyTreeItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_RootItem->columnCount();
    }
}

QVariant PropertyTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    PropertyTreeItem *item = static_cast<PropertyTreeItem*>(index.internalPointer());

    return item->data(index.column(), role);
}

bool PropertyTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }

    PropertyTreeItem *item = static_cast<PropertyTreeItem*>(index.internalPointer());

    return item->setData(index.column(), value, role);
}

Qt::ItemFlags PropertyTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QAbstractItemModel::flags(index);
    }

    PropertyTreeItem *item = static_cast<PropertyTreeItem*>(index.internalPointer());

    return item->flags(index.column());
}

QVariant PropertyTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal)
    {
        return m_RootItem->data(section, role);
    }
    return QVariant();
}

QModelIndex PropertyTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex ret;
    if (hasIndex(row, column, parent))
    {
        PropertyTreeItem *parentItem;

        if (!parent.isValid())
        {
            parentItem = m_RootItem.get();
        }
        else
        {
            parentItem = static_cast<PropertyTreeItem*>(parent.internalPointer());
        }

        PropertyTreeItem *childItem = parentItem->child(row);
        if (childItem != nullptr)
        {
            ret = createIndex(row, column, childItem);
        }
    }
    return ret;
}

QModelIndex PropertyTreeModel::parent(const QModelIndex &index) const
{
    QModelIndex ret;
    if (index.isValid())
    {
        PropertyTreeItem *childItem = static_cast<PropertyTreeItem*>(index.internalPointer());
        PropertyTreeItem *parentItem = childItem->parentItem();

        if (parentItem != nullptr && parentItem != m_RootItem.get())
        {
            ret = createIndex(parentItem->row(), 0, parentItem);
        }
    }
    return ret;
}

int PropertyTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }
    PropertyTreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = m_RootItem.get();
    }
    else
    {
        parentItem = static_cast<PropertyTreeItem*>(parent.internalPointer());
    }
    return parentItem->childCount();
}

void PropertyTreeModel::setObject(const osg::ref_ptr<osg::Object>& obj)
{
    std::shared_ptr<PropertyTreeItem> newRoot(new PropertyTreeItem(obj));

    m_RootItem = newRoot;
}
