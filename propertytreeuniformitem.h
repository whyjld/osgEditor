#ifndef PROPERTYTREEUNIFORMITEM_H
#define PROPERTYTREEUNIFORMITEM_H

#include "propertytreeitem.h"

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

    QVariant m_Name;

    osg::StateSet::RefUniformPair& m_Uniform;
};

#endif // PROPERTYTREEUNIFORMITEM_H
