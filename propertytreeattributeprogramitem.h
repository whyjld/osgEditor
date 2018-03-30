#ifndef PROPERTYTREEATTRIBUTEPROGRAMITEM_H
#define PROPERTYTREEATTRIBUTEPROGRAMITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Program>

class PropertyTreeAttributeProgramItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeProgramItem(PropertyTreeItem *parent, osg::Program* program);
    virtual ~PropertyTreeAttributeProgramItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    void buttonClicked();

    osg::ref_ptr<osg::Program> m_Program;
    QVariant m_Value;

    QStyle::State m_State;
    mutable QRect m_ButtonRect;
};

#endif // PROPERTYTREEATTRIBUTEPROGRAMITEM_H
