#ifndef SCENETREEVIEW_H
#define SCENETREEVIEW_H

#include <osg/Node>

#include <QTreeView>
#include <QMenu>

class SceneTreeView : public QTreeView
{
    Q_OBJECT
public:
    SceneTreeView(QWidget *parent = Q_NULLPTR);

    void setSceneNode(osg::Node* node);
    void onSelectNode(const osg::NodePath& path);

signals:
    void createChild(const QModelIndex &index);
    void eraseNode(const QModelIndex &index);
    void eraseNodeButChildren(const QModelIndex &index);

private slots:
    void onCustomContextMenuRequested(const QPoint& pos);

    void onCreateChild();
    void onEraseNode();
    void onEraseNodeButChildren();
private:
    void createContextMenu();

    QMenu* m_ContextMenu;
    QModelIndex m_MenuIndex;
};

#endif // SCENETREEVIEW_H
