#include "propertytreeattributelistitem.h"
#include "propertytreeattributeunknownitem.h"

#include <QPushButton>

PropertyTreeAttributeListItem::PropertyTreeAttributeListItem(PropertyTreeItem *parent, osg::StateSet::AttributeList& attributeList)
    : PropertyTreeItem(parent)
    , AttributeList(attributeList)
{
    for(auto i = AttributeList.begin();i != AttributeList.end();++i)
    {
        m_ChildItems.push_back(new PropertyTreeAttributeUnknownItem(this, i->first));
    }
}

PropertyTreeAttributeListItem::~PropertyTreeAttributeListItem()
{
}

Qt::ItemFlags PropertyTreeAttributeListItem::flags(int column) const
{
    //return ((ptcValue == column) ? Qt::ItemIsEditable : 0) |
            return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeListItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("AttributeList");
        case ptcValue:
            return QVariant("...");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeListItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}
