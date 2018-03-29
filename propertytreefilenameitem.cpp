#include "propertytreefilenameitem.h"
#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreepropertyitem.h"
#include "propertytreemodel.h"
#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QPainter>

#include <memory>

const QString g_BtnText = QObject::tr("load");

PropertyTreeFilenameItem::PropertyTreeFilenameItem(PropertyTreeItem *parent, const QString& name, Getter_t getter, Loader_t loader)
    : PropertyTreeItem(parent)
    , m_Getter(getter)
    , m_Loader(loader)
    , m_Name(name)
    , m_State(QStyle::State_Raised)
{
}

PropertyTreeFilenameItem::~PropertyTreeFilenameItem()
{
}

void PropertyTreeFilenameItem::setDialogTitle(const QString& title)
{
    m_Title = title;
}

void PropertyTreeFilenameItem::addFileFilter(const QString& filter)
{
    m_Filter.append(filter);
}

Qt::ItemFlags PropertyTreeFilenameItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeFilenameItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            return QVariant(m_Getter());
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeFilenameItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);

    return true;
}

bool PropertyTreeFilenameItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int btnWidth = QApplication::fontMetrics().width(g_BtnText) + 26;
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

bool PropertyTreeFilenameItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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

void PropertyTreeFilenameItem::buttonClicked()
{
    //todo:Open file
    std::shared_ptr<QFileDialog> openDialog(new QFileDialog(QApplication::activeWindow()));
    openDialog->setWindowTitle(m_Title);
    openDialog->setDirectory(".");
    openDialog->setFileMode(QFileDialog::ExistingFile);
    openDialog->setNameFilters(m_Filter);
    if(QDialog::Accepted == openDialog->exec())
    {
        m_Loader(openDialog->selectedFiles()[0]);
    }
}
