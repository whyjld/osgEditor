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

    Qt::ItemFlags flag = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
    switch(index.column())
    {
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

void SceneTreeModel::setSceneNode(const osg::ref_ptr<osg::Node>& node)
{
    std::shared_ptr<SceneTreeItem> newRoot(new SceneTreeItem(node, nullptr));

    m_RootItem = newRoot;
}

QModelIndex SceneTreeModel::index(const osg::NodePath& path) const
{
    SceneTreeItem* item = nullptr;
    if(path.size() > 0)
    {
        if(path[1] == m_RootItem->getNode())
        {
            item = m_RootItem.get();
            for(size_t i = 2;i < path.size();++i)
            {
                const osg::Node* node = path[i];

                SceneTreeItem* curr = nullptr;
                for(size_t c = 0;c < item->childCount();++c)
                {
                    if(node == item->child(c)->getNode())
                    {
                        curr = item->child(c);
                        break;
                    }
                }
                item = curr;
                if(nullptr == item)
                {
                    break;
                }
            }
        }
    }
    if(nullptr != item)
    {
        return createIndex(0, 0, item);
    }
    else
    {
        return QModelIndex();
    }
}

bool SceneTreeModel::insertNode(const QModelIndex& index, osg::ref_ptr<osg::Node> node)
{
    SceneTreeItem* item;
    if(index.isValid())
    {
        item = (SceneTreeItem*)index.internalPointer();
    }
    else
    {
        item = m_RootItem.get();
    }
    osg::Group* group = item->getNode()->asGroup();
    if(group != nullptr)
    {
        size_t pos = group->getNumChildren();
        beginInsertRows(index, pos, pos);
        item->createChild(node);
        endInsertRows();
        return true;
    }
    return false;
}

bool SceneTreeModel::eraseItem(const QModelIndex& index, bool withChild)
{
    if(index.isValid())
    {
        SceneTreeItem* i = (SceneTreeItem*)index.internalPointer();
        SceneTreeItem* p = i->parentItem();
        int r = i->row();
        beginRemoveRows(createIndex(p->row(), 0, p), r, r);
        if(!withChild)
        {
            for(;i->childCount() > 0;)
            {
                p->addChild(i->child(0));
            }
        }
        p->eraseChild(r);
        endRemoveRows();
        return true;
    }
    return false;
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
