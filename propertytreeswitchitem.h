#ifndef PROPERTYTREESWITCHITEM_H
#define PROPERTYTREESWITCHITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Switch>

class PropertyTreeSwitchItem : public PropertyTreeItem
{
public:
    PropertyTreeSwitchItem(PropertyTreeItem* parent, osg::Switch* os);
    virtual ~PropertyTreeSwitchItem();

    virtual QVariant data(int column, int role) const;

    bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index);
    bool setEditorData(QWidget* editor, const QModelIndex& index);
    bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index);
    bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index);
private:
    osg::ref_ptr<osg::Switch> m_Switch;
};

#endif // PROPERTYTREESWITCHITEM_H
