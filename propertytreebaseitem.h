#ifndef PROPERTYTREEBASEITEM_H
#define PROPERTYTREEBASEITEM_H

#include "propertytreeitem.h"

#include <functional>

template<typename Type_t>
class PropertyTreeBaseItem : public PropertyTreeItem
{
public:
    typedef std::function<Type_t()> Getter_t;
    typedef std::function<void(Type_t v)> Setter_t;

    PropertyTreeBaseItem(PropertyTreeItem *parent, const QString& name, Getter_t getter, Setter_t setter)
        : PropertyTreeItem(parent)
        , m_Getter(getter)
        , m_Setter(setter)
        , m_Name(name)
    {

    }

    PropertyTreeBaseItem(PropertyTreeItem *parent, const QString& name, Type_t& value)
        : PropertyTreeItem(parent)
        , m_Getter([value]()->Type_t
                    {
                        return value;
                    })
        , m_Setter([&value](Type_t v)
                    {
                        value = v;
                    })
        , m_Name(name)
    {

    }
    virtual ~PropertyTreeBaseItem()
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
                return QVariant(m_Getter());
            }
        }
        return PropertyTreeItem::data(column, role);

    }
    virtual bool setData(int column, const QVariant& value, int role)
    {
        if(Qt::EditRole == role && ptcValue == column)
        {
            m_Setter(qvariant_cast<Type_t>(value));
            return true;
        }
        return PropertyTreeItem::setData(column, value, role);
    }

    Type_t value() const
    {
        return m_Getter();
    }
private:
    Getter_t m_Getter;
    Setter_t m_Setter;

    QVariant m_Name;
};

#endif // PROPERTYTREEBASEITEM_H
