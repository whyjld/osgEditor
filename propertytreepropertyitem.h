#ifndef PROPERTYTREEPROPERTYITEM_H
#define PROPERTYTREEPROPERTYITEM_H

#include "propertytreeitem.h"

#include <QApplication>

#include <functional>
#include <vector>

class PropertyTreePropertyItem : public PropertyTreeItem
{
public:
    enum Button
    {
        bNone = 0x00,
        bDelete = 0x01,
    };

    typedef std::function<void(PropertyTreePropertyItem*, const QVariant&)> Setter_t;
    typedef std::function<QVariant(const PropertyTreePropertyItem*)> Getter_t;
    typedef std::function<void(PropertyTreePropertyItem*, Button)> OnClick_t;

    PropertyTreePropertyItem(PropertyTreeItem *parentItem, const QString& name, const Setter_t& setter, const Getter_t& getter, size_t buttons = bNone, const OnClick_t& onClick = OnClick_t())
        : PropertyTreeItem(parentItem)
        , m_Name(name)
        , m_Setter(setter)
        , m_Getter(getter)
        , m_OnClick(onClick)
        , m_Buttons(buttons)
    {
        Initialize();
    }

    PropertyTreePropertyItem(PropertyTreeItem *parentItem, const QString& name, const Getter_t& getter, size_t buttons = bNone, const OnClick_t& onClick = OnClick_t())
        : PropertyTreeItem(parentItem)
        , m_Name(name)
        , m_Getter(getter)
        , m_OnClick(onClick)
        , m_Buttons(buttons)
    {
        Initialize();
    }

    virtual ~PropertyTreePropertyItem()
    {

    }

    virtual Qt::ItemFlags flags(int column) const
    {
        return ((!!m_Setter && ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
    }

    virtual QVariant data(int column, int role) const
    {
        if (Qt::DisplayRole == role)
        {
            switch(column)
            {
            case ptcProperty:
                return QVariant(m_Name);
            case ptcValue:
                return QVariant(m_Getter(this));
            default:
                break;
            }
        }
        return QVariant();
    }

    virtual bool setData(int column, const QVariant &value, int role)
    {
        if(Qt::EditRole == role && ptcValue == column)
        {
            m_Setter(this, value);
            return true;
        }
        return PropertyTreeItem::setData(column, value, role);
    }

    virtual bool afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if(ptcValue == index.column())
        {
            size_t index = 0;
            QRect rect = option.rect;
            if(0 != (m_Buttons & bDelete))
            {
                const QString btnText = tr("delete");
                QRect btnRect = drawButton(painter, btnText, rect, m_ButtonStates[index]);
                m_ButtonRects[index] = btnRect;
                rect.setRight(btnRect.left());
                ++index;
            }
            return (index > 0);
        }
        return false;
    }

    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        (index);
        (model);
        (option);
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if(nullptr != mouseEvent)
        {
            if(Qt::LeftButton == mouseEvent->button())
            {
                for(size_t i = 0;i < m_ButtonNames.size();++i)
                {
                    if(m_ButtonRects[i].contains(mouseEvent->pos()))
                    {
                        switch(event->type())
                        {
                        case QEvent::MouseButtonPress:
                            m_ButtonStates[i] = QStyle::State_Sunken;
                            break;
                        case QEvent::MouseButtonRelease:
                            m_ButtonStates[i] = QStyle::State_Raised;
                            if(!!m_OnClick)
                            {
                                m_OnClick(this, m_ButtonNames[i]);
                            }
                            break;
                        default:
                            m_ButtonStates[i] = QStyle::State_Raised;
                            break;
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }
private:
    void Initialize()
    {
        if(0 != (bDelete & m_Buttons))
        {
            m_ButtonNames.push_back(bDelete);
        }
        if(m_ButtonNames.size() > 0)
        {
            m_ButtonStates.resize(m_ButtonNames.size(), QStyle::State_Raised);
            m_ButtonRects.resize(m_ButtonNames.size());
        }
    }

    QRect drawButton(QPainter* painter, const QString& text, QRect rect, QStyle::State state) const
    {
        if(rect.width() > 0)
        {
            int btnWidth = QApplication::fontMetrics().width(text) + 26;

            if(rect.width() > btnWidth)
            {
                rect.setX(rect.right() - btnWidth);
            }

            QStyleOptionButton opt;
            opt.palette = QPalette(Qt::red);
            opt.state = state | QStyle::State_Enabled;
            opt.text = text;
            opt.rect = rect;
            QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
        }

        return rect;
    }

    QString m_Name;
    Setter_t m_Setter;
    Getter_t m_Getter;

    size_t m_Buttons;
    OnClick_t m_OnClick;
    std::vector<Button> m_ButtonNames;
    std::vector<QStyle::State> m_ButtonStates;
    mutable std::vector<QRect> m_ButtonRects;
};

#endif // PROPERTYTREEPROPERTYITEM_H
