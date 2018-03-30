#include "propertytreeattributeprogramitem.h"
#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"
#include "addshaderdialog.h"

#include <QApplication>

#include <memory>

const QString g_BtnText(QObject::tr("create"));

PropertyTreeAttributeProgramItem::PropertyTreeAttributeProgramItem(PropertyTreeItem *parent, osg::Program* program)
    : PropertyTreeItem(parent)
    , m_Program(program)
    , m_State(QStyle::State_Raised)
{
    {
        PropertyTreeAttributeListItem* parent = dynamic_cast<PropertyTreeAttributeListItem*>(m_ParentItem);
        if(nullptr != parent)
        {
            if(nullptr != program)
            {
                for(size_t i = 0;i < m_Program->getNumShaders();++i)
                {
                    m_ChildItems.push_back(new PropertyTreeAttributeShaderItem(this, m_Program->getShader(i)));
                }
            }
            else
            {
                m_Value = tr("Invalid program attribute.");
            }
        }
        else
        {
            m_Value = tr("Invalid attribute tree data.");
        }
    }
}

PropertyTreeAttributeProgramItem::~PropertyTreeAttributeProgramItem()
{
}

Qt::ItemFlags PropertyTreeAttributeProgramItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeProgramItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("Program");
        case ptcValue:
            return QVariant("...");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeProgramItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}

bool PropertyTreeAttributeProgramItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

bool PropertyTreeAttributeProgramItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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

void PropertyTreeAttributeProgramItem::buttonClicked()
{
    bool shader[AddShaderDialog::ShaderCount] =
    {
        false,
        false,
        false,
        false,
        false,
        false,
    };
    size_t sc = m_ChildItems.size();
    for(size_t i = 0;i < sc;++i)
    {
        switch(dynamic_cast<PropertyTreeAttributeShaderItem*>(m_ChildItems[i])->Shader->getType())
        {
        case osg::Shader::VERTEX:
            shader[0] = true;
            break;
        case osg::Shader::TESSCONTROL:
            shader[1] = true;
            break;
        case osg::Shader::TESSEVALUATION:
            shader[2] = true;
            break;
        case osg::Shader::GEOMETRY:
            shader[3] = true;
            break;
        case osg::Shader::FRAGMENT:
            shader[4] = true;
            break;
        case osg::Shader::COMPUTE:
            shader[5] = true;
            break;
        default:
            break;
        }
    }
    std::shared_ptr<AddShaderDialog> dialog(new AddShaderDialog(nullptr));
    if(QDialog::Accepted == dialog->exec(shader))
    {
        if(shader[0])
        {
            m_Program->addShader(new osg::Shader(osg::Shader::VERTEX));
        }
        if(shader[1])
        {
            m_Program->addShader(new osg::Shader(osg::Shader::TESSCONTROL));
        }
        if(shader[2])
        {
            m_Program->addShader(new osg::Shader(osg::Shader::TESSEVALUATION));
        }
        if(shader[3])
        {
            m_Program->addShader(new osg::Shader(osg::Shader::GEOMETRY));
        }
        if(shader[4])
        {
            m_Program->addShader(new osg::Shader(osg::Shader::FRAGMENT));
        }
        if(shader[5])
        {
            m_Program->addShader(new osg::Shader(osg::Shader::COMPUTE));
        }
        for(size_t i = sc;i < m_Program->getNumShaders();++i)
        {
            m_ChildItems.push_back(new PropertyTreeAttributeShaderItem(this, m_Program->getShader(i)));
        }
    }
}
