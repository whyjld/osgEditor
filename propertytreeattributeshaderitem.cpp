#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreepropertyitem.h"

PropertyTreeAttributeShaderItem::PropertyTreeAttributeShaderItem(PropertyTreeItem *parent, osg::Shader* shader)
    : PropertyTreeItem(parent)
    , m_Shader(shader)
{
    //Filename
    {
        auto getter = [this]()->QVariant
        {
            return QVariant(m_Shader->getFileName().c_str());
        };
        auto setter = [this](const QVariant& value)
        {
            m_Shader->setFileName(value.toString().toStdString());
        };
        m_ChildItems.push_back(new PropertyTreePropertyItem(this, "FileName", setter, getter));
    }
    //ShaderSource
    {
        auto getter = [this]()->QVariant
        {
            return QVariant(m_Shader->getShaderSource().c_str());
        };
        auto setter = [this](const QVariant& value)
        {
            m_Shader->setShaderSource(value.toString().toStdString());
        };
        m_ChildItems.push_back(new PropertyTreePropertyItem(this, "ShaderSource", setter, getter));
    }
}

PropertyTreeAttributeShaderItem::~PropertyTreeAttributeShaderItem()
{
}

Qt::ItemFlags PropertyTreeAttributeShaderItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeShaderItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("Shader");
        case ptcValue:
            return QVariant(m_Shader->getTypename());
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeShaderItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}
