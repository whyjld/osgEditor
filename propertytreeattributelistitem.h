#ifndef PROPERTYTREEATTRIBUTELISTITEM_H
#define PROPERTYTREEATTRIBUTELISTITEM_H

#include "propertytreeitem.h"

#include <osg/StateSet>
#include <osg/Program>

class PropertyTreeAttributeListItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeListItem(PropertyTreeItem *parent, const QString& name, osg::StateSet::AttributeList& attributeList);
    virtual ~PropertyTreeAttributeListItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    osg::StateSet::AttributeList& AttributeList;
private:
    void buttonClicked();
    void addProgramItem(osg::Program* program);

    QVariant m_Name;

    QStyle::State m_State;
    mutable QRect m_ButtonRect;
};

#endif // PROPERTYTREEATTRIBUTELISTITEM_H
