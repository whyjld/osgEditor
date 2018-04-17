#include "propertytreeattributeprogramitem.h"
#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreeattributeprogramshaderdefinesitem.h"
#include "propertytreepropertyitem.h"
#include "addshaderdialog.h"
#include "propertytreemodel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

#include <memory>

const QString g_BtnText(QObject::tr("create"));

PropertyTreeAttributeProgramItem::PropertyTreeAttributeProgramItem(PropertyTreeItem *parent, osg::Program* program)
    : PropertyTreeItem(parent)
    , m_Program(program)
    , m_UniformCount(0)
    , m_AttributeCount(0)
    , m_UniformBlockCount(0)
    , m_State(QStyle::State_Raised)
{
    if(nullptr != dynamic_cast<PropertyTreeAttributeListItem*>(m_ParentItem))
    {
        if(nullptr != program)
        {
            m_ChildItems.push_back(new PropertyTreePropertyItem(this, "Info log", [this](const PropertyTreePropertyItem*)->QVariant
            {
                return QVariant(this->m_InfoLog);
            }));
            m_ChildItems.push_back(new PropertyTreePropertyItem(this, "Attribute count", [this](const PropertyTreePropertyItem*)->QVariant
            {
                return QVariant(this->m_AttributeCount);
            }));
            m_ChildItems.push_back(new PropertyTreePropertyItem(this, "Uniform count", [this](const PropertyTreePropertyItem*)->QVariant
            {
                return QVariant(this->m_UniformCount);
            }));
            m_ChildItems.push_back(new PropertyTreePropertyItem(this, "Uniform block count", [this](const PropertyTreePropertyItem*)->QVariant
            {
                return QVariant(this->m_UniformBlockCount);
            }));
            for(size_t i = 0;i < m_Program->getNumShaders();++i)
            {
                m_ChildItems.push_back(new PropertyTreeAttributeShaderItem(this, m_Program->getShader(i)));
            }
            m_ChildItems.push_back(new PropertyTreeAttributeProgramShaderDefinesItem(this, m_Program));

            checkProgramStatus();
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

void PropertyTreeAttributeProgramItem::checkProgramStatus()
{
    osgViewer::Viewer::Contexts contexts;
    osgViewer::Viewer* viewer = dynamic_cast<MainWindow*>(m_Model->Window)->getUI()->owSceneViewer->getViewer();
    viewer->getContexts(contexts);
    if(contexts.size() > 0)
    {
        osg::State* state = contexts[0]->getState();
        osg::Program::PerContextProgram* pcp = m_Program->getPCP(*state);

        if(nullptr != pcp)
        {
            if(pcp->needsLink())
            {
                pcp->linkProgram(*state);
            }
            std::string infoLog;
            bool ret = pcp->getInfoLog(infoLog);
            if(ret)
            {
                m_InfoLog = infoLog.c_str();
            }
            else
            {
                m_InfoLog.clear();
            }
            m_UniformCount = pcp->getActiveUniforms().size();
            m_AttributeCount = pcp->getActiveAttribs().size();
            m_UniformBlockCount = pcp->getUniformBlocks().size();
        }
    }
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
    size_t sc = m_Program->getNumShaders();
    for(size_t i = 0;i < sc;++i)
    {
        switch(m_Program->getShader(i)->getType())
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
        for(size_t i = 0;i < sc;++i)
        {
            switch(m_Program->getShader(i)->getType())
            {
            case osg::Shader::VERTEX:
                shader[0] = false;
                break;
            case osg::Shader::TESSCONTROL:
                shader[1] = false;
                break;
            case osg::Shader::TESSEVALUATION:
                shader[2] = false;
                break;
            case osg::Shader::GEOMETRY:
                shader[3] = false;
                break;
            case osg::Shader::FRAGMENT:
                shader[4] = false;
                break;
            case osg::Shader::COMPUTE:
                shader[5] = false;
                break;
            default:
                break;
            }
        }

        osg::Shader::Type shaderTypes[] =
        {
            osg::Shader::VERTEX,
            osg::Shader::TESSCONTROL,
            osg::Shader::TESSEVALUATION,
            osg::Shader::GEOMETRY,
            osg::Shader::FRAGMENT,
            osg::Shader::COMPUTE,
        };

        size_t nsc = 0;
        for(size_t i = 0;i < AddShaderDialog::ShaderCount;++i)
        {
            if(shader[i])
            {
                m_Program->addShader(new osg::Shader(shaderTypes[i]));
                ++nsc;
            }
        }
        m_Model->beginInsertRows(m_Model->createIndex(m_ParentItem->row(), 0, m_ParentItem), sc, sc + nsc - 1);
        for(size_t i = sc;i < m_Program->getNumShaders();++i)
        {
            m_ChildItems.push_back(new PropertyTreeAttributeShaderItem(this, m_Program->getShader(i)));
        }
        m_Model->endInsertRows();
        checkProgramStatus();
    }
}
