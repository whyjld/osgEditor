#ifndef PROPERTYTREESTATESETITEM_H
#define PROPERTYTREESTATESETITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/StateSet>

typedef std::function<osg::StateSet*()> StateSetGetter_t;

class PropertyTreeStateSetItem : public PropertyTreeItem
{
public:
    PropertyTreeStateSetItem(PropertyTreeItem *parent, const QString& name, const StateSetGetter_t& creator, const StateSetGetter_t& getter);
    virtual ~PropertyTreeStateSetItem();

    virtual QVariant data(int column, int role) const;
    bool setData(int column, const QVariant &value, int role);

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);


private:
    void buttonClicked();
    bool CreateStateSet();
    bool CreateStateSetProperty();

    QVariant m_Name;

    StateSetGetter_t m_Creator;

    osg::ref_ptr<osg::StateSet> m_StateSet;

    QString m_Button;
    QStyle::State m_State;
    mutable QRect m_ButtonRect;
};

#endif // PROPERTYTREESTATESETITEM_H
