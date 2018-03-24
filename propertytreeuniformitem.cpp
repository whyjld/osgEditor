#include "propertytreeuniformitem.h"
#include "propertytreepropertyitem.h"
#include "propertytreebaseitem.h"
#include "propertytreeuniformunknownitem.h"

PropertyTreeUniformItem::PropertyTreeUniformItem(PropertyTreeItem *parent, const osg::StateSet::UniformList::iterator& i)
    : PropertyTreeItem(parent)
    , m_Name(i->first.c_str())
    , m_Uniform(i->second)
{
    {
        QVariant type(osg::Uniform::getTypename(m_Uniform.first->getType()));
        auto getter = [type]()->QVariant
        {
            return type;
        };
        m_ChildItems.push_back(new PropertyTreePropertyItem(this, "Type", getter));
    }
    {
        auto getter = [this](void)->int
        {
            return m_Uniform.first->getNumElements();
        };
        auto setter = [this](int e)
        {
            m_Uniform.first->setNumElements(e);
            UpdateChildProperty();
        };
        m_ChildItems.push_back(new PropertyTreeBaseItem<int>(this, "NumElement", getter, setter));
    }
    UpdateChildProperty();
}

PropertyTreeUniformItem::~PropertyTreeUniformItem()
{
}

Qt::ItemFlags PropertyTreeUniformItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeUniformItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            return QVariant();
        }
    }
    return PropertyTreeItem::data(column, role);
}

void PropertyTreeUniformItem::UpdateChildProperty()
{
    const size_t c_NotValueElement = 2;//Type, NumElement
    auto e = m_Uniform.first->getNumElements() + c_NotValueElement;
    auto s = m_ChildItems.size();
    if(s > e)
    {
        m_ChildItems.erase(m_ChildItems.begin() + e, m_ChildItems.begin() + s);
    }
    else if(s < e)
    {
        QString name;
        for(auto i = s; i < e;++i)
        {
            name.sprintf("%d", i - 1);
            PropertyTreeItem* item = nullptr;
            switch(m_Uniform.first->getType())
            {
            case osg::Uniform::FLOAT:
            case osg::Uniform::FLOAT_VEC2:
            case osg::Uniform::FLOAT_VEC3:
            case osg::Uniform::FLOAT_VEC4:
            case osg::Uniform::DOUBLE:
            case osg::Uniform::DOUBLE_VEC2:
            case osg::Uniform::DOUBLE_VEC3:
            case osg::Uniform::DOUBLE_VEC4:
            case osg::Uniform::INT:
            case osg::Uniform::INT_VEC2:
            case osg::Uniform::INT_VEC3:
            case osg::Uniform::INT_VEC4:
            case osg::Uniform::UNSIGNED_INT:
            case osg::Uniform::UNSIGNED_INT_VEC2:
            case osg::Uniform::UNSIGNED_INT_VEC3:
            case osg::Uniform::UNSIGNED_INT_VEC4:
            case osg::Uniform::BOOL:
            case osg::Uniform::BOOL_VEC2:
            case osg::Uniform::BOOL_VEC3:
            case osg::Uniform::BOOL_VEC4:
            case osg::Uniform::FLOAT_MAT2:
            case osg::Uniform::FLOAT_MAT3:
            case osg::Uniform::FLOAT_MAT4:
            case osg::Uniform::FLOAT_MAT2x3:
            case osg::Uniform::FLOAT_MAT2x4:
            case osg::Uniform::FLOAT_MAT3x2:
            case osg::Uniform::FLOAT_MAT3x4:
            case osg::Uniform::FLOAT_MAT4x2:
            case osg::Uniform::FLOAT_MAT4x3:
            case osg::Uniform::DOUBLE_MAT2:
            case osg::Uniform::DOUBLE_MAT3:
            case osg::Uniform::DOUBLE_MAT4:
            case osg::Uniform::DOUBLE_MAT2x3:
            case osg::Uniform::DOUBLE_MAT2x4:
            case osg::Uniform::DOUBLE_MAT3x2:
            case osg::Uniform::DOUBLE_MAT3x4:
            case osg::Uniform::DOUBLE_MAT4x2:
            case osg::Uniform::DOUBLE_MAT4x3:
            case osg::Uniform::SAMPLER_1D:
            case osg::Uniform::SAMPLER_2D:
            case osg::Uniform::SAMPLER_3D:
            case osg::Uniform::SAMPLER_CUBE:
            case osg::Uniform::SAMPLER_1D_SHADOW:
            case osg::Uniform::SAMPLER_2D_SHADOW:
            case osg::Uniform::SAMPLER_1D_ARRAY:
            case osg::Uniform::SAMPLER_2D_ARRAY:
            case osg::Uniform::SAMPLER_CUBE_MAP_ARRAY:
            case osg::Uniform::SAMPLER_1D_ARRAY_SHADOW:
            case osg::Uniform::SAMPLER_2D_ARRAY_SHADOW:
            case osg::Uniform::SAMPLER_2D_MULTISAMPLE:
            case osg::Uniform::SAMPLER_2D_MULTISAMPLE_ARRAY:
            case osg::Uniform::SAMPLER_CUBE_SHADOW:
            case osg::Uniform::SAMPLER_CUBE_MAP_ARRAY_SHADOW:
            case osg::Uniform::SAMPLER_BUFFER:
            case osg::Uniform::SAMPLER_2D_RECT:
            case osg::Uniform::SAMPLER_2D_RECT_SHADOW:
            case osg::Uniform::INT_SAMPLER_1D:
            case osg::Uniform::INT_SAMPLER_2D:
            case osg::Uniform::INT_SAMPLER_3D:
            case osg::Uniform::INT_SAMPLER_CUBE:
            case osg::Uniform::INT_SAMPLER_1D_ARRAY:
            case osg::Uniform::INT_SAMPLER_2D_ARRAY:
            case osg::Uniform::INT_SAMPLER_CUBE_MAP_ARRAY:
            case osg::Uniform::INT_SAMPLER_2D_MULTISAMPLE:
            case osg::Uniform::INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
            case osg::Uniform::INT_SAMPLER_BUFFER:
            case osg::Uniform::INT_SAMPLER_2D_RECT:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_1D:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_2D:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_3D:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_CUBE:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_1D_ARRAY:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_2D_ARRAY:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_BUFFER:
            case osg::Uniform::UNSIGNED_INT_SAMPLER_2D_RECT:
            case osg::Uniform::IMAGE_1D:
            case osg::Uniform::IMAGE_2D:
            case osg::Uniform::IMAGE_3D:
            case osg::Uniform::IMAGE_2D_RECT:
            case osg::Uniform::IMAGE_CUBE:
            case osg::Uniform::IMAGE_BUFFER:
            case osg::Uniform::IMAGE_1D_ARRAY:
            case osg::Uniform::IMAGE_2D_ARRAY:
            case osg::Uniform::IMAGE_CUBE_MAP_ARRAY:
            case osg::Uniform::IMAGE_2D_MULTISAMPLE:
            case osg::Uniform::IMAGE_2D_MULTISAMPLE_ARRAY:
            case osg::Uniform::INT_IMAGE_1D:
            case osg::Uniform::INT_IMAGE_2D:
            case osg::Uniform::INT_IMAGE_3D:
            case osg::Uniform::INT_IMAGE_2D_RECT:
            case osg::Uniform::INT_IMAGE_CUBE:
            case osg::Uniform::INT_IMAGE_BUFFER:
            case osg::Uniform::INT_IMAGE_1D_ARRAY:
            case osg::Uniform::INT_IMAGE_2D_ARRAY:
            case osg::Uniform::INT_IMAGE_CUBE_MAP_ARRAY:
            case osg::Uniform::INT_IMAGE_2D_MULTISAMPLE:
            case osg::Uniform::INT_IMAGE_2D_MULTISAMPLE_ARRAY:
            case osg::Uniform::UNSIGNED_INT_IMAGE_1D:
            case osg::Uniform::UNSIGNED_INT_IMAGE_2D:
            case osg::Uniform::UNSIGNED_INT_IMAGE_3D:
            case osg::Uniform::UNSIGNED_INT_IMAGE_2D_RECT:
            case osg::Uniform::UNSIGNED_INT_IMAGE_CUBE:
            case osg::Uniform::UNSIGNED_INT_IMAGE_BUFFER:
            case osg::Uniform::UNSIGNED_INT_IMAGE_1D_ARRAY:
            case osg::Uniform::UNSIGNED_INT_IMAGE_2D_ARRAY:
            case osg::Uniform::UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY:
            case osg::Uniform::UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
            case osg::Uniform::UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
            default:
                item = new PropertyTreeUniformUnknownItem(this, name);
                break;
            }
            m_ChildItems.push_back(item);
        }
    }
}
