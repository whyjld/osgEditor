#ifndef PROPERTYTREEFILENAMEITEM_H
#define PROPERTYTREEFILENAMEITEM_H

#include "propertytreeitem.h"

#include <QString>

class PropertyTreeFilenameItem : public PropertyTreeItem
{
public:
    typedef std::function<void(const QString&)> Loader_t;
    typedef std::function<QString()> Getter_t;

    PropertyTreeFilenameItem(PropertyTreeItem *parent, const QString& name, Getter_t getter, Loader_t loader);
    virtual ~PropertyTreeFilenameItem();

    void setDialogTitle(const QString& title);
    void addFileFilter(const QString& filter);

    virtual Qt::ItemFlags flags(int column) const;
    virtual QVariant data(int column, int role) const;
    virtual bool setData(int column, const QVariant &value, int role);

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    void buttonClicked();

    Getter_t m_Getter;
    Loader_t m_Loader;

    QString m_Name;
    QStyle::State m_State;
    mutable QRect m_ButtonRect;

    QString m_Title;
    QStringList m_Filter;
};

#endif // PROPERTYTREEFILENAMEITEM_H
