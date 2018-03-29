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

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    void buttonClicked();
    void ChangeValue();

    QString m_Value;
    QStyle::State m_State;
    mutable QRect m_ButtonRect;
};

#endif // PROPERTYTREEATTRIBUTESHADERSOURCEITEM_H
