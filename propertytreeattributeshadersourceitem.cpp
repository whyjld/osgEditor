#include "propertytreeattributeshadersourceitem.h"
#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreepropertyitem.h"
#include "propertytreemodel.h"
#include "mainwindow.h"

#include <QApplication>
#include <QPainter>
#include <QPushButton>

#include <sstream>

const QString g_BtnText = QObject::tr("edit");

PropertyTreeAttributeShaderSourceItem::PropertyTreeAttributeShaderSourceItem(PropertyTreeItem *parent)
    : PropertyTreeItem(parent)
    , m_State(QStyle::State_Raised)
{
    ChangeValue();
}

PropertyTreeAttributeShaderSourceItem::~PropertyTreeAttributeShaderSourceItem()
{
}

Qt::ItemFlags PropertyTreeAttributeShaderSourceItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeShaderSourceItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("ShaderSource");
        case ptcValue:
            return m_Value;
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeShaderSourceItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);

    ChangeValue();
    return true;
}

bool PropertyTreeAttributeShaderSourceItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int btnWidth = QApplication::fontMetrics().width(g_BtnText) + 6;
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
        opt.text = g_BtnText;
        opt.rect = m_ButtonRect;
        QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter);
    }

    return true;
}

bool PropertyTreeAttributeShaderSourceItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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

void PropertyTreeAttributeShaderSourceItem::buttonClicked()
{
    MainWindow* mw = dynamic_cast<MainWindow*>(m_Model->Window);
    PropertyTreeAttributeShaderItem* parent = dynamic_cast<PropertyTreeAttributeShaderItem*>(m_ParentItem);
    if(nullptr != mw && nullptr != parent)
    {
        mw->editShader(parent->Shader);
    }
}

void PropertyTreeAttributeShaderSourceItem::ChangeValue()
{
    PropertyTreeAttributeShaderItem* parent = dynamic_cast<PropertyTreeAttributeShaderItem*>(m_ParentItem);
    if(nullptr != parent)
    {
        m_Value.clear();

        std::stringstream ss(parent->Shader->getShaderSource());
        std::string line;
        for(std::getline(ss, line);!ss.eof();std::getline(ss, line))
        {
            m_Value += line.c_str();
            m_Value += " ";
        }
    }
}
