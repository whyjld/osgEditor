#ifndef PROPERTYTREEATTRIBUTEBASEITEM_H
#define PROPERTYTREEATTRIBUTEBASEITEM_H

#include "propertytreeitem.h"

template<typename Type_t>
class PropertyTreeAttributeBaseItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeBaseItem(PropertyTreeItem *parent, const QString& name, Type_t& value)
        : PropertyTreeItem(parent)
        , m_Value(value)
        , m_Name(name)
    {

    }
    virtual ~PropertyTreeAttributeBaseItem()
    {

    }

    virtual Qt::ItemFlags flags(int column) const
    {
        return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
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
                return QVariant(m_Value);
            }
        }
        return PropertyTreeItem::data(column, role);

    }
    virtual bool setData(int column, const QVariant& value, int role)
    {
        if(Qt::EditRole == role && ptcValue == column)
        {
            m_Value = qvariant_cast<Type_t>(value);
            return true;
        }
        return PropertyTreeItem::setData(column, value, role);
    }

    Type_t value() const
    {
        return m_Value;
    }
private:
    Type_t& m_Value;

    QVariant m_Name;
};

#endif // PROPERTYTREEATTRIBUTEBASEITEM_H
