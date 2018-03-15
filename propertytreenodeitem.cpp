#include "propertytreenodeitem.h"
#include "propertytreepropertyitem.h"

PropertyTreeNodeItem::PropertyTreeNodeItem(PropertyTreeItem *parent, osg::Node* node)
    : PropertyTreeItem(parent)
{
    //CullingActive
    auto CullingActiveSetter = [node](const QVariant& v)
    {
        node->setCullingActive(v.toBool());
    };
    auto CullingActiveGetter = [node]()->QVariant
    {
        return QVariant(node->getCullingActive());
    };
    m_ChildItems.append(new PropertyTreePropertyItem(this, "CullingActive", CullingActiveSetter, CullingActiveGetter));

    //getNumChildrenWithCullingDisabled
    auto getNumChildrenWithCullingDisabledGetter = [node]()->QVariant
    {
        return QVariant(node->getNumChildrenWithCullingDisabled());
    };
    m_ChildItems.append(new PropertyTreeDisplayItem(this, "getNumChildrenWithCullingDisabled", getNumChildrenWithCullingDisabledGetter));

    //isCullingActive
    auto isCullingActiveGetter = [node]()->QVariant
    {
        return QVariant(node->isCullingActive());
    };
    m_ChildItems.append(new PropertyTreeDisplayItem(this, "isCullingActive", isCullingActiveGetter));

    //getNumChildrenWithOccluderNodes
    auto getNumChildrenWithOccluderNodesGetter = [node]()->QVariant
    {
        return QVariant(node->getNumChildrenWithOccluderNodes());
    };
    m_ChildItems.append(new PropertyTreeDisplayItem(this, "getNumChildrenWithOccluderNodes", getNumChildrenWithOccluderNodesGetter));

    //containsOccluderNodes
    auto containsOccluderNodesGetter = [node]()->QVariant
    {
        return QVariant(node->containsOccluderNodes());
    };
    m_ChildItems.append(new PropertyTreeDisplayItem(this, "containsOccluderNodes", containsOccluderNodesGetter));

    //NodeMask
    auto NodeMaskSetter = [node](const QVariant& v)
    {
        node->setNodeMask(v.toUInt());
    };
    auto NodeMaskGetter = [node]()->QVariant
    {
        return QVariant(node->getNodeMask());
    };
    m_ChildItems.append(new PropertyTreePropertyItem(this, "NodeMask", NodeMaskSetter, NodeMaskGetter));
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
