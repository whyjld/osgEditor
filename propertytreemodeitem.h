#ifndef PROPERTYTREEMODEITEM_H
#define PROPERTYTREEMODEITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Node>

class PropertyTreeModeItem : public PropertyTreeItem
{
public:
    PropertyTreeModeItem(PropertyTreeItem *parent, osg::StateAttribute::GLMode mode);
    virtual ~PropertyTreeModeItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor,const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    osg::StateAttribute::GLMode m_Mode;
    QVariant m_Name;
};

#endif // PROPERTYTREEMODEITEM_H
