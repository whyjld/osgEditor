#include "propertytreepositionattitudetransformitem.h"
#include "propertytreevectoritem.h"

PropertyTreePositionAttitudeTransformItem::PropertyTreePositionAttitudeTransformItem(PropertyTreeItem *parent, osg::PositionAttitudeTransform* transform)
    : PropertyTreeItem(parent)
{
    //Position
    auto getPosition = [transform](size_t e)->double
    {
        auto pos = transform->getPosition();
        return pos[e];
    };
    auto setPosition = [transform](size_t e, double v)
    {
        osg::Vec3d pos = transform->getPosition();
        pos[e] = v;
        transform->setPosition(pos);
    };
    m_ChildItems.append(new PropertyTreeVectorItem<double>(this, "Position", getPosition, setPosition, 3));

    //Attitude
    auto getAttitude = [transform](size_t e)->double
    {
        auto att = transform->getAttitude();
        return att[e];
    };
    auto setAttitude = [transform](size_t e, double v)
    {
        osg::Quat att = transform->getAttitude();
        att[e] = v;
        transform->setAttitude(att);
    };
    m_ChildItems.append(new PropertyTreeVectorItem<double>(this, "Attitude", getAttitude, setAttitude, 4));

    //Scale
    auto getScale = [transform](size_t e)->double
    {
        auto scale = transform->getScale();
        return scale[e];
    };
    auto setScale = [transform](size_t e, double v)
    {
        osg::Vec3d scale = transform->getScale();
        scale[e] = v;
        transform->setScale(scale);
    };
    m_ChildItems.append(new PropertyTreeVectorItem<double>(this, "Scale", getScale, setScale, 3));

    //PivotPoint
    auto getPivotPoint = [transform](size_t e)->double
    {
        auto pp = transform->getPivotPoint();
        return pp[e];
    };
    auto setPivotPoint = [transform](size_t e, double v)
    {
        osg::Vec3d pp = transform->getPivotPoint();
        pp[e] = v;
        transform->setPivotPoint(pp);
    };
    m_ChildItems.append(new PropertyTreeVectorItem<double>(this, "PivotPoint", getPivotPoint, setPivotPoint, 3));
}

PropertyTreePositionAttitudeTransformItem::~PropertyTreePositionAttitudeTransformItem()
{
}

QVariant PropertyTreePositionAttitudeTransformItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role && ptcProperty == column)
    {
        return QVariant("osg::PositionAttitudeTransform");
    }
    return PropertyTreeItem::data(column, role);
}
