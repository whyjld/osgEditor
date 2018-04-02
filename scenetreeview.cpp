#include "scenetreeview.h"
#include "scenetreemodel.h"
#include "scenetreeitem.h"

SceneTreeView::SceneTreeView(QWidget *parent)
 : QTreeView(parent)
 , m_ContextMenu(new QMenu(this))
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setModel(new SceneTreeModel());
    createContextMenu();
}

void SceneTreeView::setSceneNode(osg::Node* node)
{
    ((SceneTreeModel*)model())->setSceneNode(node);
    reset();
}

void SceneTreeView::onSelectNode(const osg::NodePath& path)
{
    selectionModel()->setCurrentIndex(((SceneTreeModel*)model())->index(path), QItemSelectionModel::SelectCurrent);
}

bool SceneTreeView::insertNode(const QModelIndex& index, osg::ref_ptr<osg::Node> node)
{
    return ((SceneTreeModel*)model())->insertNode(index, node);
}

bool SceneTreeView::eraseItem(const QModelIndex& index, bool withChild)
{
    return ((SceneTreeModel*)model())->eraseItem(index, withChild);
}

void SceneTreeView::onCustomContextMenuRequested(const QPoint& pos)
{
    m_MenuIndex = indexAt(pos);
    if(m_MenuIndex.isValid())
    {
        SceneTreeItem* item = (SceneTreeItem*)m_MenuIndex.internalPointer();
        m_ContextMenu->actions()[0]->setEnabled((item != nullptr) && (dynamic_cast<osg::Group*>(item->getNode()) != nullptr));
    }
    else
    {
        m_ContextMenu->actions()[0]->setEnabled(false);
    }
    m_ContextMenu->actions()[1]->setEnabled(m_MenuIndex.isValid());
    m_ContextMenu->actions()[2]->setEnabled(m_MenuIndex.isValid());
    m_ContextMenu->exec(mapToGlobal(pos));
}

void SceneTreeView::createContextMenu()
{
    m_ContextMenu->addAction(tr("&Create child node"), this, &SceneTreeView::onCreateChild);
    m_ContextMenu->addAction(tr("&Erase node"), this, &SceneTreeView::onEraseNode);
    m_ContextMenu->addAction(tr("Erase node but &children"), this, &SceneTreeView::onEraseNodeButChildren);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenuRequested(const QPoint &)));
}

void SceneTreeView::onCreateChild()
{
    emit createChild(m_MenuIndex);
}

void SceneTreeView::onEraseNode()
{
    emit eraseNode(m_MenuIndex);
}

void SceneTreeView::onEraseNodeButChildren()
{
    emit eraseNodeButChildren(m_MenuIndex);
}
