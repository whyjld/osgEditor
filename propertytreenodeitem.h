#ifndef PROPERTYTREENODEITEM_H
#define PROPERTYTREENODEITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Node>

class PropertyTreeNodeItem : public PropertyTreeItem
{
public:
    PropertyTreeNodeItem(PropertyTreeItem *parentItem, osg::ref_ptr<osg::Node>& node);
    virtual ~PropertyTreeNodeItem();
private:
    osg::ref_ptr<osg::Node> m_Node;
};

#endif // PROPERTYTREENODEITEM_H
