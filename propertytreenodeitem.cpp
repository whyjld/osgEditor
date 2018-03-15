#include "propertytreenodeitem.h"

PropertyTreeNodeItem::PropertyTreeNodeItem(PropertyTreeItem *parentItem, osg::ref_ptr<osg::Node>& node)
    : PropertyTreeItem(parentItem)
    , m_Node(node)
{
}

PropertyTreeNodeItem::~PropertyTreeNodeItem()
{
}
