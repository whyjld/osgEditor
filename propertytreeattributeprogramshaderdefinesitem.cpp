#include "propertytreeattributeprogramshaderdefinesitem.h"
#include "propertytreepropertyitem.h"
#include "propertytreemodel.h"

#include <QInputDialog>
#include <QMessageBox>

#include <memory>

const QString g_BtnText(QObject::tr("create"));

PropertyTreeAttributeProgramShaderDefinesItem::PropertyTreeAttributeProgramShaderDefinesItem(PropertyTreeItem *parent, osg::Program* program)
    : PropertyTreeItem(parent)
    , m_ShaderDefines(program->getShaderDefines())
    , m_State(QStyle::State_Raised)
{
    for(auto i = m_ShaderDefines.begin();i != m_ShaderDefines.end();++i)
    {
        m_ChildItems.push_back(new PropertyTreePropertyItem(this, "", [i](const PropertyTreePropertyItem*)->QVariant
        {
            return QVariant(i->c_str());
        }));
    }
}

PropertyTreeAttributeProgramShaderDefinesItem::~PropertyTreeAttributeProgramShaderDefinesItem()
{
}

Qt::ItemFlags PropertyTreeAttributeProgramShaderDefinesItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeProgramShaderDefinesItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("Shader Defines");
        case ptcValue:
            return QVariant("...");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeProgramShaderDefinesItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}

bool PropertyTreeAttributeProgramShaderDefinesItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

bool PropertyTreeAttributeProgramShaderDefinesItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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

void PropertyTreeAttributeProgramShaderDefinesItem::buttonClicked()
{
    QString define = QInputDialog::getText(nullptr, tr("New Shader Define"), tr("please input new shader define:"));
    if(!define.isEmpty() && m_ShaderDefines.find(define.toStdString()) == m_ShaderDefines.end())
    {
        m_Model->beginInsertRows(m_Model->createIndex(this->row(), 0, this), m_ChildItems.size(), m_ChildItems.size());

        std::vector<QString> buttons;
        buttons.push_back(tr("delete"));
        m_ChildItems.push_back(new PropertyTreePropertyItem(this,
                                                            "",
                                                            [define](const PropertyTreePropertyItem*)->QVariant
                                                            {
                                                                return QVariant(define);
                                                            },
                                                            buttons,
                                                            [define, this](PropertyTreePropertyItem* sender, size_t button)
                                                            {
                                                                if(0 == button)
                                                                {
                                                                    if(QMessageBox::Yes == QMessageBox::question(nullptr, tr("Warning"), tr("Delete this shader define?"), QMessageBox::Yes | QMessageBox::Cancel))
                                                                    {
                                                                        m_Model->beginRemoveRows(m_Model->createIndex(row(), 0, this), sender->row(), 1);
                                                                        m_ChildItems.erase(m_ChildItems.begin() + m_ChildItems.indexOf(sender));
                                                                        m_Model->endRemoveRows();
                                                                    }
                                                                }
                                                            }));
        m_Model->endInsertRows();
    }
}
