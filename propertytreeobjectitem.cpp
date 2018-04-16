#include "propertytreeobjectitem.h"
#include "propertytreepropertyitem.h"


PropertyTreeObjectItem::PropertyTreeObjectItem(PropertyTreeItem *parentItem, osg::Object* obj)
    : PropertyTreeItem(parentItem)
{
    auto setter = [obj](PropertyTreePropertyItem*, const QVariant& v)
    {
        obj->setName(v.toString().toStdString());
    };

    auto getter = [obj](const PropertyTreePropertyItem*)->QVariant
    {
        if(obj->getName().length() > 0)
        {
            return QVariant(obj->getName().c_str());
        }
        else
        {
            return QVariant(QObject::tr("No Name"));
        }
    };

    m_ChildItems.append(new PropertyTreePropertyItem(this, "Name", setter, getter));
}

PropertyTreeObjectItem::~PropertyTreeObjectItem()
{
}

QVariant PropertyTreeObjectItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role && ptcProperty == column)
    {
        return QVariant("osg::Object");
    }
    return PropertyTreeItem::data(column, role);
}
