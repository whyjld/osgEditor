#include "scenetreeitem.h"
#include <QStringList>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Drawable>
#include <osg/Geometry>
#include <osg/PrimitiveSet>

SceneTreeItem::SceneTreeItem(osg::Node* node, SceneTreeItem *parentItem)
    : m_Node(node)
    , m_ParentItem(parentItem)
{
    if(node != nullptr)
    {
        osg::ref_ptr<osg::Group> group(dynamic_cast<osg::Group*>(node));
        if(!!group)
        {
            for(size_t i = 0;i < group->getNumChildren();++i)
            {
                m_ChildItems.append(new SceneTreeItem(group->getChild(i), this));
            }
        }
    }
}

SceneTreeItem::~SceneTreeItem()
{
    qDeleteAll(m_ChildItems);
}

SceneTreeItem *SceneTreeItem::child(int row)
{
    return m_ChildItems.value(row);
}

int SceneTreeItem::childCount() const
{
    return m_ChildItems.count();
}

int SceneTreeItem::columnCount() const
{
    return stcCount;
}

QVariant SceneTreeItem::data(int column, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch(column)
        {
        case stcName:
            if(nullptr != m_ParentItem)
            {
                if(m_Node->getName().length() > 0)
                {
                    return QVariant(m_Node->getName().c_str());
                }
                else
                {
                    return QVariant(QObject::tr("No name"));
                }
            }
            else
            {
                return QVariant(QObject::tr("Name"));
            }
            break;
        case stcType:
            if(nullptr != m_ParentItem)
            {
                return QVariant(m_Node->className());
            }
            else
            {
                return QVariant(QObject::tr("Type"));
            }
            break;
        default:
            return QVariant();
        }
        break;
    case Qt::EditRole:
        if(stcName == column && nullptr != m_ParentItem)
        {
            return QVariant(m_Node->getName().c_str());
        }
        break;
    case Qt::CheckStateRole:
        if(stcType == column && nullptr != m_ParentItem)
        {
            return (m_Node->getNodeMask() > 0) ? Qt::Checked : Qt::Unchecked;
        }
        break;
    case Qt::TextAlignmentRole:
        switch(column)
        {
        case stcName:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case stcType:
            return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
        default:
            break;
        }
        break;
    case Qt::SizeHintRole:
        break;
    default:
        break;
    }
    return QVariant();
}

bool SceneTreeItem::setData(int column, const QVariant &value, int role)
{
    switch (role)
    {
    case Qt::CheckStateRole:
        if(stcType == column && nullptr != m_ParentItem)
        {
            switch(value.toInt())
            {
            case Qt::Checked:
            case Qt::PartiallyChecked:
                m_Node->setNodeMask(1);
                break;
            case Qt::Unchecked:
                m_Node->setNodeMask(0);
                break;
            }
        }
        return true;
    case Qt::EditRole:
        if(stcName == column && nullptr != m_ParentItem)
        {
            m_Node->setName(value.toString().toStdString());
        }
        break;
    default:
        break;
    }
    return false;
}

SceneTreeItem *SceneTreeItem::parentItem()
{
    return m_ParentItem;
}

int SceneTreeItem::row() const
{
    if (nullptr != m_ParentItem)
    {
        return m_ParentItem->m_ChildItems.indexOf(const_cast<SceneTreeItem*>(this));
    }
    return 0;
}

void SceneTreeItem::createChild(osg::Node* node)
{
    osg::ref_ptr<osg::Group> group(m_Node->asGroup());
    if(!!group)
    {
        group->addChild(node);
        m_ChildItems.append(new SceneTreeItem(node, this));
    }
}

bool SceneTreeItem::addChild(SceneTreeItem* item)
{
    osg::ref_ptr<osg::Group> group(m_Node->asGroup());
    if(!group)
    {
        return false;
    }
    if(this == item->parentItem())
    {
        return false;
    }
    for(SceneTreeItem* i = this;i != nullptr;i = i->parentItem())
    {
        if(item == i)
        {
            return false;
        }
    }
    SceneTreeItem* opi = item->m_ParentItem;
    if(nullptr != opi)
    {
        opi->m_ChildItems.removeOne(item);
        opi->m_Node->asGroup()->removeChild(item->m_Node);
    }
    group->addChild(item->m_Node);
    m_ChildItems.append(item);
    item->m_ParentItem = this;

    return true;
}

bool SceneTreeItem::eraseChild(size_t i)
{
    osg::ref_ptr<osg::Group> group(m_Node->asGroup());
    if(!!group && i < group->getNumChildren())
    {
        group->removeChild(i);
        SceneTreeItem* item = m_ChildItems[i];
        m_ChildItems.removeAt(i);
        delete item;
        return true;
    }
    return false;
}
