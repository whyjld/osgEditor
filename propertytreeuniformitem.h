#ifndef PROPERTYTREEUNIFORMITEM_H
#define PROPERTYTREEUNIFORMITEM_H

#include "propertytreeitem.h"
#include "propertytreebaseitem.h"
#include "propertytreevectoritem.h"

#include <osg/ref_ptr>
#include <osg/StateSet>

class PropertyTreeUniformItem : public PropertyTreeItem
{
public:
    PropertyTreeUniformItem(PropertyTreeItem *parent, const osg::StateSet::UniformList::iterator& i);
    virtual ~PropertyTreeUniformItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
private:
    void UpdateChildProperty();

    template<typename Type_t> PropertyTreeItem* CreateBaseItem(unsigned int index)
    {
        auto getter = [this, index]()->Type_t
        {
            Type_t ret;
            if(m_Uniform.first->getElement(index, ret))
            {
                return ret;
            }
            else
            {
                return Type_t(0);
            }
        };

        auto setter = [this, index](Type_t v)
        {
            m_Uniform.first->setElement(index, v);
        };

        return new PropertyTreeBaseItem<Type_t>(this, QString::number(index + 1, 10), getter, setter);
    }

    template<typename Type_t> PropertyTreeItem* CreateVectorItem(unsigned int index)
    {
        auto getter = [this, index](size_t i)->Type_t::value_type
        {
            Type_t ret;
            if(m_Uniform.first->getElement(index, ret))
            {
                return ret[i];
            }
            else
            {
                return Type_t::value_type(0);
            }
        };

        auto setter = [this, index](size_t i, Type_t::value_type v)
        {
            Type_t ret;
            if(m_Uniform.first->getElement(index, ret))
            {
                ret[i] = v;
                m_Uniform.first->setElement(index, ret);
            }
        };

        return new PropertyTreeVectorItem<Type_t::value_type>(this, QString::number(index + 1, 10), getter, setter, Type_t::num_components);
    }

    template<typename Type_t> PropertyTreeItem* CreateVector2Item(unsigned int index)
    {
        auto getter = [this, index](size_t i)->Type_t
        {
            Type_t ret[2];
            if(m_Uniform.first->getElement(index, ret[0], ret[1]))
            {
                return ret[i];
            }
            else
            {
                return Type_t(0);
            }
        };

        auto setter = [this, index](size_t i, Type_t v)
        {
            Type_t ret[2];
            if(m_Uniform.first->getElement(index, ret[0], ret[1]))
            {
                ret[i] = v;
                m_Uniform.first->setElement(index, ret[0], ret[1]);
            }
        };

        return new PropertyTreeVectorItem<Type_t>(this, QString::number(index + 1, 10), getter, setter, 2);
    }

    template<typename Type_t> PropertyTreeItem* CreateVector3Item(unsigned int index)
    {
        auto getter = [this, index](size_t i)->Type_t
        {
            Type_t ret[3];
            if(m_Uniform.first->getElement(index, ret[0], ret[1], ret[2]))
            {
                return ret[i];
            }
            else
            {
                return Type_t(0);
            }
        };

        auto setter = [this, index](size_t i, Type_t v)
        {
            Type_t ret[3];
            if(m_Uniform.first->getElement(index, ret[0], ret[1], ret[2]))
            {
                ret[i] = v;
                m_Uniform.first->setElement(index, ret[0], ret[1], ret[2]);
            }
        };

        return new PropertyTreeVectorItem<Type_t>(this, QString::number(index + 1, 10), getter, setter, 3);
    }

    template<typename Type_t> PropertyTreeItem* CreateVector4Item(unsigned int index)
    {
        auto getter = [this, index](size_t i)->Type_t
        {
            Type_t ret[4];
            if(m_Uniform.first->getElement(index, ret[0], ret[1], ret[2], ret[3]))
            {
                return ret[i];
            }
            else
            {
                return Type_t(0);
            }
        };

        auto setter = [this, index](size_t i, Type_t v)
        {
            Type_t ret[4];
            if(m_Uniform.first->getElement(index, ret[0], ret[1], ret[2], ret[3]))
            {
                ret[i] = v;
                m_Uniform.first->setElement(index, ret[0], ret[1], ret[2], ret[3]);
            }
        };

        return new PropertyTreeVectorItem<Type_t>(this, QString::number(index + 1, 10), getter, setter, 3);
    }

    QVariant m_Name;

    osg::StateSet::RefUniformPair& m_Uniform;
};

#endif // PROPERTYTREEUNIFORMITEM_H
