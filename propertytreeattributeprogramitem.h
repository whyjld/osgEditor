#ifndef PROPERTYTREEATTRIBUTEPROGRAMITEM_H
#define PROPERTYTREEATTRIBUTEPROGRAMITEM_H

#include "propertytreeitem.h"

#include <osg/ref_ptr>
#include <osg/Program>

class PropertyTreeAttributeProgramItem : public PropertyTreeItem
{
public:
    PropertyTreeAttributeProgramItem(PropertyTreeModel* model, osg::Program* program);
    virtual ~PropertyTreeAttributeProgramItem();

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    void checkProgramStatus();
    void buttonClicked();

    osg::ref_ptr<osg::Program> m_Program;
    QVariant m_Value;

    QString m_InfoLog;
    size_t m_UniformCount;
    size_t m_AttributeCount;
    size_t m_UniformBlockCount;

    QStyle::State m_State;
    mutable QRect m_ButtonRect;
};

#endif // PROPERTYTREEATTRIBUTEPROGRAMITEM_H
