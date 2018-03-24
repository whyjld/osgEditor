#ifndef PROPERTYTREEUNIFORMLISTITEM_H
#define PROPERTYTREEUNIFORMLISTITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/StateSet>

class PropertyTreeUniformListItem : public PropertyTreeItem
{
public:
    PropertyTreeUniformListItem(PropertyTreeItem *parent, osg::StateSet::UniformList& uniformList);
    virtual ~PropertyTreeUniformListItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor,const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    osg::StateSet::UniformList& UniformList;
private slots:
    void buttonClicked(bool checked);

private:
};

#endif // PROPERTYTREEUNIFORMLISTITEM_H
