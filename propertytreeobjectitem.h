#ifndef PROPERTYTREEOBJECTITEM_H
#define PROPERTYTREEOBJECTITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Object>

class PropertyTreeObjectItem : public PropertyTreeItem
{
public:
    PropertyTreeObjectItem(PropertyTreeItem *parentItem, osg::Object* obj);
    virtual ~PropertyTreeObjectItem();

    virtual QVariant data(int column, int role) const;
private:
};

#endif // PROPERTYTREEOBJECTITEM_H
