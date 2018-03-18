#ifndef PROPERTYTREEATTRIBUTEPROGRAMITEM_H
#define PROPERTYTREEATTRIBUTEPROGRAMITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Program>

class PropertyTreeAttributeProgramItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeProgramItem(PropertyTreeItem *parent, const osg::StateAttribute::TypeMemberPair& attribute);
    virtual ~PropertyTreeAttributeProgramItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);
private slots:

private:
    osg::StateAttribute::TypeMemberPair m_Attribute;
    QVariant m_Value;
};

#endif // PROPERTYTREEATTRIBUTEPROGRAMITEM_H
