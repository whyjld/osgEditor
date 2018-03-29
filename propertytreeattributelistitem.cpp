#include "propertytreeattributelistitem.h"
#include "propertytreeattributeunknownitem.h"
#include "propertytreeattributeprogramitem.h"

#include <QApplication>

const QString g_BtnText = QObject::tr("add");

PropertyTreeAttributeListItem::PropertyTreeAttributeListItem(PropertyTreeItem *parent, osg::StateSet::AttributeList& attributeList)
    : PropertyTreeItem(parent)
    , AttributeList(attributeList)
    , m_State(QStyle::State_Raised)
{
    for(auto i = AttributeList.begin();i != AttributeList.end();++i)
    {
        switch(i->first.first)
        {
//        case TEXTURE:
//            break;
//        case POLYGONMODE:
//            break;
//        case POLYGONOFFSET:
//            break;
//        case MATERIAL:
//            break;
//        case ALPHAFUNC:
//            break;
//        case ANTIALIAS:
//            break;
//        case COLORTABLE:
//            break;
//        case CULLFACE:
//            break;
//        case FOG:
//            break;
//        case FRONTFACE:
//            break;
//        case LIGHT:
//            break;
//        case POINT:
//            break;
//        case LINEWIDTH:
//            break;
//        case LINESTIPPLE:
//            break;
//        case POLYGONSTIPPLE:
//            break;
//        case SHADEMODEL:
//            break;
//        case TEXENV:
//            break;
//        case TEXENVFILTER:
//            break;
//        case TEXGEN:
//            break;
//        case TEXMAT:
//            break;
//        case LIGHTMODEL:
//            break;
//        case BLENDFUNC:
//            break;
//        case BLENDEQUATION:
//            break;
//        case LOGICOP:
//            break;
//        case STENCIL:
//            break;
//        case COLORMASK:
//            break;
//        case DEPTH:
//            break;
//        case VIEWPORT:
//            break;
//        case SCISSOR:
//            break;
//        case BLENDCOLOR:
//            break;
//        case MULTISAMPLE:
//            break;
//        case CLIPPLANE:
//            break;
//        case COLORMATRIX:
//            break;
//        case VERTEXPROGRAM:
//            break;
//        case FRAGMENTPROGRAM:
//            break;
//        case POINTSPRITE:
//            break;
        case osg::StateAttribute::PROGRAM:
            m_ChildItems.push_back(new PropertyTreeAttributeProgramItem(this, i->first));
            break;
//        case CLAMPCOLOR:
//            break;
//        case HINT:
//            break;
//        case SAMPLEMASKI:
//            break;
//        case PRIMITIVERESTARTINDEX:
//            break;
//        case CLIPCONTROL:
//            break;
///// osgFX namespace
//        case VALIDATOR:
//            break;
//        case VIEWMATRIXEXTRACTOR:
//            break;
///// osgNV namespace
//        case OSGNV_PARAMETER_BLOCK:
//            break;
///// osgNVExt namespace
//        case OSGNVEXT_TEXTURE_SHADER:
//            break;
//        case OSGNVEXT_VERTEX_PROGRAM:
//            break;
//        case OSGNVEXT_REGISTER_COMBINERS:
//            break;
///// osgNVCg namespace
//        case OSGNVCG_PROGRAM:
//            break;
///// osgNVSlang namespace
//        case OSGNVSLANG_PROGRAM:
//            break;
///// osgNVParse
//        case OSGNVPARSE_PROGRAM_PARSER:
//            break;
//        case UNIFORMBUFFERBINDING:
//            break;
//        case TRANSFORMFEEDBACKBUFFERBINDING:
//            break;
//        case ATOMICCOUNTERBUFFERBINDING:
//            break;
//        case PATCH_PARAMETER:
//            break;
//        case FRAME_BUFFER_OBJECT:
//            break;
//        case VERTEX_ATTRIB_DIVISOR:
//            break;
//        case SHADERSTORAGEBUFFERBINDING:
//            break;
        default:
            m_ChildItems.push_back(new PropertyTreeAttributeUnknownItem(this, i->first));
            break;
        }
    }
}

PropertyTreeAttributeListItem::~PropertyTreeAttributeListItem()
{
}

Qt::ItemFlags PropertyTreeAttributeListItem::flags(int column) const
{
    //return ((ptcValue == column) ? Qt::ItemIsEditable : 0) |
            return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeListItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("AttributeList");
        case ptcValue:
            return QVariant("...");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeListItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}

bool PropertyTreeAttributeListItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

bool PropertyTreeAttributeListItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
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

void PropertyTreeAttributeListItem::buttonClicked()
{

}
