#ifndef MANAGERLISTITEM_H
#define MANAGERLISTITEM_H

#include <osg/ref_ptr>

#include <QIcon>
#include <QString>
#include <QStandardItem>

template<typename _T>
class ManagerListItem : public QStandardItem
{
public:
    ManagerListItem(const QIcon& icon, const QString& text, _T* v)
        : QStandardItem(icon, text)
        , m_Value(v)
    {

    }

    ~ManagerListItem()
    {

    }

    virtual void setData(const QVariant &value, int role = Qt::UserRole + 1)
    {
        QStandardItem::setData(value, role);
        if(Qt::EditRole == role)
        {
            m_Value->setName(text().toStdString());
        }
    }
private:
    osg::ref_ptr<_T> m_Value;
};
#endif // MANAGERLISTITEM_H
