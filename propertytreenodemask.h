#ifndef PROPERTYTREENODEMASK_H
#define PROPERTYTREENODEMASK_H

#include "propertytreeitem.h"

#include <osg/Node>

class PropertyTreeNodeMask : public PropertyTreeItem
{
public:
    PropertyTreeNodeMask(PropertyTreeItem *parent, osg::Node* node);
    virtual ~PropertyTreeNodeMask();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;

    virtual bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor,const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    osg::ref_ptr<osg::Node> m_Node;
};

#endif // PROPERTYTREENODEMASK_H
