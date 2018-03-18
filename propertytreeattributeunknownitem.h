#ifndef PROPERTYTREEATTRIBUTEUNKNOWNITEM_H
#define PROPERTYTREEATTRIBUTEUNKNOWNITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Node>

class PropertyTreeAttributeUnknownItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeUnknownItem(PropertyTreeItem *parent, const osg::StateAttribute::TypeMemberPair& attribute);
    virtual ~PropertyTreeAttributeUnknownItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);
private slots:

private:
    osg::StateAttribute::TypeMemberPair m_Attribute;

    QVariant m_Name;
};

#endif // PROPERTYTREEATTRIBUTEUNKNOWNITEM_H
