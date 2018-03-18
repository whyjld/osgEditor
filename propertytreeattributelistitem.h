#ifndef PROPERTYTREEATTRIBUTELISTITEM_H
#define PROPERTYTREEATTRIBUTELISTITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Node>

class PropertyTreeAttributeListItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeListItem(PropertyTreeItem *parent, osg::StateSet::AttributeList& attributeList);
    virtual ~PropertyTreeAttributeListItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    osg::StateSet::AttributeList& AttributeList;
private slots:

private:
};

#endif // PROPERTYTREEATTRIBUTELISTITEM_H
