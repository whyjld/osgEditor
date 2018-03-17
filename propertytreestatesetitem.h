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

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    bool setData(int column, const QVariant &value, int role);

    virtual bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor,const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private slots:
    void buttonClicked(bool checked);

private:
    bool CreateStateSet();
    bool CreateStateSetProperty();

    QVariant m_Name;

    StateSetGetter_t m_Creator;

    osg::ref_ptr<osg::StateSet> m_StateSet;
};

#endif // PROPERTYTREESTATESETITEM_H
