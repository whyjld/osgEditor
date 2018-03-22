#ifndef PROPERTYTREEATTRIBUTEVECTORITEM_H
#define PROPERTYTREEATTRIBUTEVECTORITEM_H

#include "propertytreeitem.h"
#include "propertytreeattributebaseitem.h"

#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>

#include <ostream>
#include <sstream>

template<typename Value_t>
class PropertyTreeAttributeVectorItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeVectorItem(PropertyTreeItem *parent, const QString& name, Value_t* v, size_t e)
        : PropertyTreeItem(parent)
        , m_Name(name)
    {
        char* titles[] =
        {
            "X",
            "Y",
            "Z",
            "W",
        };
        for(size_t i = 0;i < e;++i)
        {
            m_ChildItems.push_back(new PropertyTreeAttributeBaseItem<Value_t>(this, titles[i], v[i]));
        }
    }

    PropertyTreeAttributeVectorItem(PropertyTreeItem *parent, const QString& name, Value_t& x, Value_t& y)
        : PropertyTreeItem(parent)
        , m_Name(name)
    {
        m_ChildItems.push_back(new PropertyTreeAttributeBaseItem<Value_t>(this, "X", x));
        m_ChildItems.push_back(new PropertyTreeAttributeBaseItem<Value_t>(this, "Y", y));
    }

    PropertyTreeAttributeVectorItem(PropertyTreeItem *parent, const QString& name, Value_t& x, Value_t& y, Value_t& z)
        : PropertyTreeAttributeVectorItem(parent, name, x, y)
    {
        m_ChildItems.push_back(new PropertyTreeAttributeBaseItem<Value_t>(this, "Z", z));
    }

    PropertyTreeAttributeVectorItem(PropertyTreeItem *parent, const QString& name, Value_t& x, Value_t& y, Value_t& z, Value_t& w)
        : PropertyTreeAttributeVectorItem(parent, name, x, y, z)
    {
        m_ChildItems.push_back(new PropertyTreeAttributeBaseItem<Value_t>(this, "W", w));
    }

    virtual ~PropertyTreeAttributeVectorItem()
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
                if(true)
                {
                    std::stringstream ss;
                    ss.flags(std::ios::fixed);
                    ss.precision(4);

                    ss << "("
                       << dynamic_cast<PropertyTreeAttributeBaseItem<Value_t>*>(m_ChildItems[0])->value();
                    for(size_t i = 1;i < m_ChildItems.size();++i)
                    {
                        ss << ", "
                           << dynamic_cast<PropertyTreeAttributeBaseItem<Value_t>*>(m_ChildItems[i])->value();
                    }
                    ss << ")";
                    return QVariant(ss.str().c_str());
                }
            }
        }
        return PropertyTreeItem::data(column, role);
    }
private:
    QVariant m_Name;
};

#endif // PROPERTYTREEATTRIBUTEVECTORITEM_H
