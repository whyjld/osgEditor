#ifndef PROPERTYTREEATTRIBUTESHADERITEM_H
#define PROPERTYTREEATTRIBUTESHADERITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Shader>

class PropertyTreeAttributeShaderItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeShaderItem(PropertyTreeItem *parent, osg::Shader* shader);
    virtual ~PropertyTreeAttributeShaderItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);
private slots:

private:
    osg::ref_ptr<osg::Shader> m_Shader;
};

#endif // PROPERTYTREEATTRIBUTESHADERITEM_H
