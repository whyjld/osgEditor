#include "propertytreenodeitem.h"
#include "propertytreebaseitem.h"
#include "propertytreepropertyitem.h"
#include "propertytreenodemask.h"
#include "propertytreeboundingsphereitem.h"
#include "propertytreestatesetitem.h"

PropertyTreeNodeItem::PropertyTreeNodeItem(PropertyTreeItem *parent, osg::Node* node)
    : PropertyTreeItem(parent)
{
    //CullingActive
    auto CullingActiveSetter = [node](bool v)
    {
        node->setCullingActive(v);
    };
    auto CullingActiveGetter = [node]()->bool
    {
        return node->getCullingActive();
    };
    m_ChildItems.append(new PropertyTreeBaseItem<bool>(this, "CullingActive", CullingActiveGetter, CullingActiveSetter));

    //getNumChildrenWithCullingDisabled
    auto getNumChildrenWithCullingDisabledGetter = [node]()->QVariant
    {
        return QVariant(node->getNumChildrenWithCullingDisabled());
    };
    m_ChildItems.append(new PropertyTreePropertyItem(this, "getNumChildrenWithCullingDisabled", getNumChildrenWithCullingDisabledGetter));

    //isCullingActive
    auto isCullingActiveGetter = [node]()->QVariant
    {
        return QVariant(node->isCullingActive());
    };
    m_ChildItems.append(new PropertyTreePropertyItem(this, "isCullingActive", isCullingActiveGetter));

    //getNumChildrenWithOccluderNodes
    auto getNumChildrenWithOccluderNodesGetter = [node]()->QVariant
    {
        return QVariant(node->getNumChildrenWithOccluderNodes());
    };
    m_ChildItems.append(new PropertyTreePropertyItem(this, "getNumChildrenWithOccluderNodes", getNumChildrenWithOccluderNodesGetter));

    //containsOccluderNodes
    auto containsOccluderNodesGetter = [node]()->QVariant
    {
        return QVariant(node->containsOccluderNodes());
    };
    m_ChildItems.append(new PropertyTreePropertyItem(this, "containsOccluderNodes", containsOccluderNodesGetter));

    //NodeMask
    m_ChildItems.append(new PropertyTreeNodeMask(this, node));

    //getBound
    auto getBoundGetter = [node]()->osg::BoundingSphere
    {
        return node->getBound();
    };
    m_ChildItems.append(new PropertyTreeBoundingSphereItem(this, "getBound", getBoundGetter));

    //StateSet
    auto getStateSet = [node]()->osg::StateSet*
    {
        return node->getStateSet();
    };
    auto createStateSet = [node]()->osg::StateSet*
    {
        return node->getOrCreateStateSet();
    };
    m_ChildItems.append(new PropertyTreeStateSetItem(this, "StateSet", createStateSet, getStateSet));
}

PropertyTreeNodeItem::~PropertyTreeNodeItem()
{
}

QVariant PropertyTreeNodeItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role && ptcProperty == column)
    {
        return QVariant("osg::Node");
    }
    return PropertyTreeItem::data(column, role);
}
