#ifndef PROPERTYTREEMATRIXTRANSFORMITEM_H
#define PROPERTYTREEMATRIXTRANSFORMITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/MatrixTransform>

class PropertyTreeMatrixTransformItem : public PropertyTreeItem
{
public:
    PropertyTreeMatrixTransformItem(PropertyTreeItem *parent, osg::MatrixTransform* transform);
    virtual ~PropertyTreeMatrixTransformItem();

    virtual QVariant data(int column, int role) const;
private:
};

#endif // PROPERTYTREEMATRIXTRANSFORMITEM_H
