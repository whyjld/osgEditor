#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributeshadersourceitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreepropertyitem.h"

PropertyTreeAttributeShaderItem::PropertyTreeAttributeShaderItem(PropertyTreeItem *parent, osg::Shader* shader)
    : PropertyTreeItem(parent)
    , Shader(shader)
{
    //Filename
    {
        auto getter = [this]()->QVariant
        {
            return QVariant(Shader->getFileName().c_str());
        };
        auto setter = [this](const QVariant& value)
        {
            Shader->setFileName(value.toString().toStdString());
        };
        m_ChildItems.push_back(new PropertyTreePropertyItem(this, "FileName", setter, getter));
    }
    //ShaderSource
    m_ChildItems.push_back(new PropertyTreeAttributeShaderSourceItem(this));
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
            return QVariant(Shader->getTypename());
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
