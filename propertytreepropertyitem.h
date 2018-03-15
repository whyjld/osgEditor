#ifndef PROPERTYTREEPROPERTYITEM_H
#define PROPERTYTREEPROPERTYITEM_H

#include "propertytreeitem.h"

#include <functional>

typedef std::function<void(const QVariant&)> Setter_t;
typedef std::function<QVariant()> Getter_t;

class PropertyTreePropertyItem : public PropertyTreeItem
{
public:
    PropertyTreePropertyItem(PropertyTreeItem *parentItem, const QString& name, const Setter_t& setter, const Getter_t& getter)
        : PropertyTreeItem(parentItem)
        , m_Name(name)
        , m_Setter(setter)
        , m_Getter(getter)
    {

    }

    virtual ~PropertyTreePropertyItem()
    {

    }

    virtual Qt::ItemFlags flags(int column) const
    {
        return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
    }

    virtual QVariant data(int column, int role) const
    {
        if (Qt::DisplayRole == role)
        {
            switch(column)
            {
            case ptcProperty:
                return QVariant(m_Name);
            case ptcValue:
                return QVariant(m_Getter());
            default:
                break;
            }
        }
        return QVariant();
    }

    virtual bool setData(int column, const QVariant &value, int role)
    {
        if(Qt::EditRole == role && ptcValue == column)
        {
            m_Setter(value);
            return true;
        }
        return PropertyTreeItem::setData(column, value, role);
    }
private:
    QString m_Name;
    Setter_t m_Setter;
    Getter_t m_Getter;
};

#endif // PROPERTYTREEPROPERTYITEM_H
