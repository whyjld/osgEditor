#include "propertytreestatesetitem.h"
#include "propertytreemodelistitem.h"
#include "propertytreeuniformlistitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreemodel.h"

#include <QApplication>

PropertyTreeStateSetItem::PropertyTreeStateSetItem(PropertyTreeItem *parent, const QString& name, const StateSetGetter_t& creator, const StateSetGetter_t& getter)
    : PropertyTreeItem(parent)
    , m_Name(name)
    , m_Creator(creator)
    , m_Button(tr("create"))
    , m_StateSet(getter())
{
    if(!!m_StateSet)
    {
        m_Button = tr("...");
        CreateStateSetProperty();
    }
}

PropertyTreeStateSetItem::~PropertyTreeStateSetItem()
{
}

QVariant PropertyTreeStateSetItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            return QVariant("...");
        };
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeStateSetItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}

bool PropertyTreeStateSetItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int btnWidth = QApplication::fontMetrics().width(m_Button) + 26;
    if(ptcValue == index.column())
    {
        m_ButtonRect = option.rect;
        if(m_ButtonRect.width() > btnWidth)
        {
            m_ButtonRect.setX(m_ButtonRect.right() - btnWidth);
        }

        QStyleOptionButton opt;
        opt.palette = QPalette(Qt::red);
        opt.state = m_State | QStyle::State_Enabled;
        opt.text = m_Button;
        opt.rect = m_ButtonRect;
        QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
    }

    return true;
}

bool PropertyTreeStateSetItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    (index);
    (model);
    (option);
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if(nullptr != mouseEvent)
    {
        if(Qt::LeftButton == mouseEvent->button() && m_ButtonRect.contains(mouseEvent->pos()))
        {
            switch(event->type())
            {
            case QEvent::MouseButtonPress:
                m_State = QStyle::State_Sunken;
                break;
            case QEvent::MouseButtonRelease:
                m_State = QStyle::State_Raised;
                buttonClicked();
                break;
            default:
                m_State = QStyle::State_Raised;
                break;
            }
            return true;
        }
    }
    m_State = QStyle::State_Raised;
    return false;
}

void PropertyTreeStateSetItem::buttonClicked()
{
    if(!!m_StateSet)
    {
        //todo: show StateSet panel
    }
    else
    {
        if(CreateStateSet())
        {
            m_Button = tr("...");
        }
    }
}

bool PropertyTreeStateSetItem::CreateStateSet()
{
    m_StateSet = m_Creator();
    if(!!m_StateSet)
    {
        m_Model->beginInsertRows(m_Model->createIndex(this->row(), 0, this), 0, 2);
        CreateStateSetProperty();
        m_Model->endInsertRows();
        return true;
    }
    return false;
}

bool PropertyTreeStateSetItem::CreateStateSetProperty()
{
    if(!!m_StateSet)
    {
        m_ChildItems.push_back(new PropertyTreeModeListItem(this, m_StateSet->getModeList()));
        m_ChildItems.push_back(new PropertyTreeAttributeListItem(this, m_StateSet->getAttributeList()));
        m_ChildItems.push_back(new PropertyTreeUniformListItem(this, m_StateSet->getUniformList()));

        return true;
    }
    return false;
}
