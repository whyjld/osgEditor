#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributeshadersourceitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreefilenameitem.h"

PropertyTreeAttributeShaderItem::PropertyTreeAttributeShaderItem(PropertyTreeItem *parent, osg::Shader* shader)
    : PropertyTreeItem(parent)
    , Shader(shader)
{
    //Filename
    {
        auto getter = [this]()->QString
        {
            return QString(Shader->getFileName().c_str());
        };
        auto setter = [this](const QString& value)
        {
            Shader->setFileName(value.toStdString());
        };
        m_ChildItems.push_back(new PropertyTreeFilenameItem(this, "FileName", getter, setter));
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
