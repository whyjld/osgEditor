#ifndef SCENETREEITEM_H
#define SCENETREEITEM_H

#include <QList>
#include <QVariant>

#include <osg/ref_ptr>
#include <osg/Node>

enum SceneTreeColumn
{
    stcName,
    stcType,
    stcCount,
};

class SceneTreeItem
{
public:
    SceneTreeItem(osg::Node* node, SceneTreeItem *parentItem = 0);
    ~SceneTreeItem();

    SceneTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int role) const;
    bool setData(int column, const QVariant &value, int role);
    int row() const;
    SceneTreeItem *parentItem();

    void addChild(osg::Node* node);
    bool eraseChild(size_t i);

    osg::Node* getNode() const
    {
        return m_Node;
    }
private:
    osg::ref_ptr<osg::Node> m_Node;

    SceneTreeItem *m_ParentItem;
    QList<SceneTreeItem*> m_ChildItems;
};
#endif // SCENETREEITEM_H
