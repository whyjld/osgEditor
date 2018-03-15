#ifndef PROPERTYTREENODEITEM_H
#define PROPERTYTREENODEITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Node>

class PropertyTreeNodeItem : public PropertyTreeItem
{
public:
    PropertyTreeNodeItem(PropertyTreeItem *parent, osg::Node* node);
    virtual ~PropertyTreeNodeItem();

    virtual QVariant data(int column, int role) const;
private:
};

#endif // PROPERTYTREENODEITEM_H
