#include "propertytreematrixtransformitem.h"
#include "propertytreeattributematrixitem.h"

PropertyTreeMatrixTransformItem::PropertyTreeMatrixTransformItem(PropertyTreeItem *parent, osg::MatrixTransform* transform)
    : PropertyTreeItem(parent)
{
    //Matrix
    auto getMatrix = [transform]()->const osg::Matrix&
    {
        return transform->getMatrix();
    };
    auto setMatrix = [transform](const osg::Matrix& m)
    {
        return transform->setMatrix(m);
    };
    m_ChildItems.append(new PropertyTreeAttributeMatrixItem(this, "Matrix", getMatrix, setMatrix));
}

PropertyTreeMatrixTransformItem::~PropertyTreeMatrixTransformItem()
{
}

QVariant PropertyTreeMatrixTransformItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role && ptcProperty == column)
    {
        return QVariant("osg::MatrixTransform");
    }
    return PropertyTreeItem::data(column, role);
}
