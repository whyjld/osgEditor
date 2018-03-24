#ifndef PROPERTYTREEUNIFORMUNKNOWNITEM_H
#define PROPERTYTREEUNIFORMUNKNOWNITEM_H

#include "propertytreeitem.h"

class PropertyTreeUniformUnknownItem : public PropertyTreeItem
{
public:
    PropertyTreeUniformUnknownItem(PropertyTreeItem *parent, const QString& name)
        : PropertyTreeItem(parent)
        , m_Name(name)
    {

    }
    virtual ~PropertyTreeUniformUnknownItem()
    {

    }

    virtual QVariant data(int column, int role) const
    {
        if(Qt::DisplayRole == role)
        {
            switch(column)
            {
            case ptcProperty:
                return m_Name;
            case ptcValue:
                return c_Value;
            }
        }
        return PropertyTreeItem::data(column, role);

    }
private:
    QVariant m_Name;

    const QVariant c_Value = QVariant("Unknown");
};

#endif // PROPERTYTREEUNIFORMUNKNOWNITEM_H
