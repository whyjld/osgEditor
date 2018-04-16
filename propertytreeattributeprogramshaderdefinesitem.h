#ifndef PROPERTYTREEATTRIBUTEPROGRAMSHADERDEFINESITEM_H
#define PROPERTYTREEATTRIBUTEPROGRAMSHADERDEFINESITEM_H

#include "propertytreeitem.h"

#include <osg/Program>

class PropertyTreeAttributeProgramShaderDefinesItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeProgramShaderDefinesItem(PropertyTreeItem *parent, osg::Program* program);
    virtual ~PropertyTreeAttributeProgramShaderDefinesItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    void buttonClicked();

    osg::ShaderDefines& m_ShaderDefines;

    QStyle::State m_State;
    mutable QRect m_ButtonRect;
};

#endif // PROPERTYTREEATTRIBUTEPROGRAMSHADERDEFINESITEM_H
