#ifndef PROPERTYTREEATTRIBUTESHADERSOURCEITEM_H
#define PROPERTYTREEATTRIBUTESHADERSOURCEITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Shader>

class PropertyTreeAttributeShaderSourceItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeShaderSourceItem(PropertyTreeItem *parent);
    virtual ~PropertyTreeAttributeShaderSourceItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor,const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private slots:
    void buttonClicked();

private:
    void ChangeValue();
    QVariant m_Value;
};

#endif // PROPERTYTREEATTRIBUTESHADERSOURCEITEM_H
