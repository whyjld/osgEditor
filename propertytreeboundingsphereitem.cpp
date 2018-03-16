#include "propertytreeboundingsphereitem.h"
#include "propertytreepropertyitem.h"

#include <sstream>

PropertyTreeBoundingSphereItem::PropertyTreeBoundingSphereItem(PropertyTreeItem *parent, const QString& name, const BoundingSphereGetter_t& getter)
    : PropertyTreeItem(parent)
    , m_Getter(getter)
    , m_Name(name)
{
    {
        auto getter = [this]()->QVariant
        {
            std::stringstream ss;
            ss.flags(std::ios::fixed);
            ss.precision(4);

            osg::BoundingSphere bs = this->m_Getter();
            auto& c = bs.center();
            ss << c.x() << ", " << c.y() << ", " << c.z();

            return QVariant(ss.str().c_str());
        };
        m_ChildItems.append(new PropertyTreePropertyItem(this, "Center", getter));
    }

    {
        auto getter = [this]()->QVariant
        {
            std::stringstream ss;
            ss.flags(std::ios::fixed);
            ss.precision(4);

            osg::BoundingSphere bs = this->m_Getter();
            ss << bs.radius();

            return QVariant(ss.str().c_str());
        };
        m_ChildItems.append(new PropertyTreePropertyItem(this, "Radius", getter));
    }
}

PropertyTreeBoundingSphereItem::~PropertyTreeBoundingSphereItem()
{
}

QVariant PropertyTreeBoundingSphereItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            {
                std::stringstream ss;
                ss.flags(std::ios::fixed);
                ss.precision(4);

                osg::BoundingSphere bs = this->m_Getter();
                auto& c = bs.center();
                ss << "(" << c.x() << ", " << c.y() << ", " << c.z() << ") - " << bs.radius();

                return QVariant(ss.str().c_str());
            }
        }
    }
    return PropertyTreeItem::data(column, role);
}
