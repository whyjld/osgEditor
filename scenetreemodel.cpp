#include "scenetreemodel.h"
#include "scenetreeitem.h"
#include <QStringList>
#include <QColor>
#include <QBrush>
#include <QFont>

#include <osg/Geode>
#include <osg/Group>

SceneTreeModel::SceneTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_RootItem(new SceneTreeItem(nullptr))
{
}

SceneTreeModel::~SceneTreeModel()
{
}

int SceneTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<SceneTreeItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_RootItem->columnCount();
    }
}

QVariant SceneTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    SceneTreeItem *item = static_cast<SceneTreeItem*>(index.internalPointer());

    return item->data(index.column(), role);
}

bool SceneTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }

    SceneTreeItem *item = static_cast<SceneTreeItem*>(index.internalPointer());

    return item->setData(index.column(), value, role);
}

Qt::ItemFlags SceneTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QAbstractItemModel::flags(index);
    }

    Qt::ItemFlags flag = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    switch(index.column())
    {
    case stcName:
        flag |= Qt::ItemIsEditable;
        break;
    case stcType:
        flag |= Qt::ItemIsUserCheckable;
        break;
    default:
        break;
    }
    return flag;
}

QVariant SceneTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal)
    {
        return m_RootItem->data(section, role);
    }
    return QVariant();
}

QModelIndex SceneTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex ret;
    if (hasIndex(row, column, parent))
    {
        SceneTreeItem *parentItem;

        if (!parent.isValid())
        {
            parentItem = m_RootItem.get();
        }
        else
        {
            parentItem = static_cast<SceneTreeItem*>(parent.internalPointer());
        }

        SceneTreeItem *childItem = parentItem->child(row);
        if (childItem != nullptr)
        {
            ret = createIndex(row, column, childItem);
        }
    }
    return ret;
}

QModelIndex SceneTreeModel::parent(const QModelIndex &index) const
{
    QModelIndex ret;
    if (index.isValid())
    {
        SceneTreeItem *childItem = static_cast<SceneTreeItem*>(index.internalPointer());
        SceneTreeItem *parentItem = childItem->parentItem();

        if (parentItem != nullptr && parentItem != m_RootItem.get())
        {
            ret = createIndex(parentItem->row(), 0, parentItem);
        }
    }
    return ret;
}

int SceneTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }
    SceneTreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = m_RootItem.get();
    }
    else
    {
        parentItem = static_cast<SceneTreeItem*>(parent.internalPointer());
    }
    return parentItem->childCount();
}

QModelIndex SceneTreeModel::index(const osg::Geode* geode)
{
    QModelIndex ret;
    if(nullptr != geode)
    {
        auto i = m_Index.find(geode);
        if(i != m_Index.end())
        {
            ret = createIndex(i->second->row(), 0, i->second);
        }
    }
    return ret;
}

void SceneTreeModel::setSceneNode(const osg::ref_ptr<osg::Node>& node)
{
    osg::Group* group = node->asGroup();
    if(nullptr != group)
    {
        std::hash_map<const osg::Geode*, SceneTreeItem*> newIndex;
        std::shared_ptr<SceneTreeItem> newRoot(new SceneTreeItem(node, nullptr));

        m_RootItem = newRoot;
        m_Index = newIndex;
    }
}

void SceneTreeModel::ShowAll()
{
    for(size_t i = 0;i < m_RootItem->childCount();++i)
    {
        m_RootItem->child(i)->getNode()->setNodeMask(1);
    }
}

void SceneTreeModel::HideAllExpect(size_t i)
{
    for(size_t c = 0;c < m_RootItem->childCount();++c)
    {
        m_RootItem->child(c)->getNode()->setNodeMask(c == i);
    }
}

void SceneTreeModel::buildGeodeIndex(osg::Node* node, SceneTreeItem* item, std::hash_map<const osg::Geode*, SceneTreeItem*>& index)
{
    osg::Geode* geode = node->asGeode();
    if(nullptr != geode)
    {
        index[geode] = item;
    }
    osg::Group* group = node->asGroup();
    if(nullptr != group)
    {
        for(size_t i = 0;i < group->getNumChildren();++i)
        {
            buildGeodeIndex(group->getChild(i), item, index);
        }
    }
}
