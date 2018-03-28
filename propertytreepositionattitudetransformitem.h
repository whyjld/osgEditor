#ifndef PROPERTYTREEPOSITIONATTITUDETRANSFORMITEM_H
#define PROPERTYTREEPOSITIONATTITUDETRANSFORMITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/PositionAttitudeTransform>

class PropertyTreePositionAttitudeTransformItem : public PropertyTreeItem
{
public:
    PropertyTreePositionAttitudeTransformItem(PropertyTreeItem *parent, osg::PositionAttitudeTransform* transform);
    virtual ~PropertyTreePositionAttitudeTransformItem();

    virtual QVariant data(int column, int role) const;
private:
};

#endif // PROPERTYTREEPOSITIONATTITUDETRANSFORMITEM_H
