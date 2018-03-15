#ifndef PROPERTYTREEITEM_H
#define PROPERTYTREEITEM_H

#include <osg/Object>

#include <QList>
#include <QVariant>

enum PropertyTreeColumn
{
    ptcProperty,
    ptcValue,
    stcCount,
};

class PropertyTreeItem
{
public:
    PropertyTreeItem(PropertyTreeItem *parent = nullptr);
    PropertyTreeItem(osg::Object* object);
    virtual ~PropertyTreeItem();

    PropertyTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;

    int row() const;
    PropertyTreeItem *parentItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);
protected:
    PropertyTreeItem *m_ParentItem;
    QList<PropertyTreeItem*> m_ChildItems;
};

#endif // PROPERTYTREEITEM_H
