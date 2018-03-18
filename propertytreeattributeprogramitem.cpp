#include "propertytreeattributeprogramitem.h"
#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"

PropertyTreeAttributeProgramItem::PropertyTreeAttributeProgramItem(PropertyTreeItem *parent, const osg::StateAttribute::TypeMemberPair& attribute)
    : PropertyTreeItem(parent)
    , m_Attribute(attribute)
{
    {
        PropertyTreeAttributeListItem* parent = dynamic_cast<PropertyTreeAttributeListItem*>(m_ParentItem);
        if(nullptr != parent)
        {
            osg::StateSet::RefAttributePair value = parent->AttributeList[m_Attribute];
            osg::Program* program = dynamic_cast<osg::Program*>(value.first.get());
            if(nullptr != program)
            {
                for(size_t i = 0;i < program->getNumShaders();++i)
                {
                    m_ChildItems.push_back(new PropertyTreeAttributeShaderItem(this, program->getShader(i)));
                }
            }
            else
            {
                m_Value = tr("Invalid program node.");
            }
        }
        else
        {
            m_Value = tr("Invalid attribute tree data.");
        }
    }
}

PropertyTreeAttributeProgramItem::~PropertyTreeAttributeProgramItem()
{
}

Qt::ItemFlags PropertyTreeAttributeProgramItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeProgramItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("Program");
        case ptcValue:
            return QVariant("...");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeProgramItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}
