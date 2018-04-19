#ifndef PROPERTYTREEMODELISTITEM_H
#define PROPERTYTREEMODELISTITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Node>

class PropertyTreeModeListItem : public PropertyTreeItem
{
public:
    PropertyTreeModeListItem(PropertyTreeItem *parent, const QString& name, osg::StateSet::ModeList& modeList);
    virtual ~PropertyTreeModeListItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor,const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    osg::StateSet::ModeList& ModeList;
private slots:
    void buttonClicked(bool checked);

private:
    QVariant m_Name;
};

#endif // PROPERTYTREEMODELISTITEM_H
