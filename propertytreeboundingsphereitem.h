#ifndef PROPERTYTREEBOUNDINGSPHEREITEM_H
#define PROPERTYTREEBOUNDINGSPHEREITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/BoundingSphere>

class PropertyTreeBoundingSphereItem : public PropertyTreeItem
{
public:
    typedef std::function<osg::BoundingSphere()> BoundingSphereGetter_t;

    PropertyTreeBoundingSphereItem(PropertyTreeItem *parent, const QString& name, const BoundingSphereGetter_t& getter);
    virtual ~PropertyTreeBoundingSphereItem();

    virtual QVariant data(int column, int role) const;
private:
    BoundingSphereGetter_t m_Getter;

    QVariant m_Name;
};

#endif // PROPERTYTREEBOUNDINGSPHEREITEM_H
