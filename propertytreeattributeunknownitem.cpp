#include "propertytreeattributeunknownitem.h"

const char* c_TypeName[] =
{
    "TEXTURE",

    "POLYGONMODE",
    "POLYGONOFFSET",
    "MATERIAL",
    "ALPHAFUNC",
    "ANTIALIAS",
    "COLORTABLE",
    "CULLFACE",
    "FOG",
    "FRONTFACE",

    "LIGHT",

    "POINT",
    "LINEWIDTH",
    "LINESTIPPLE",
    "POLYGONSTIPPLE",
    "SHADEMODEL",
    "TEXENV",
    "TEXENVFILTER",
    "TEXGEN",
    "TEXMAT",
    "LIGHTMODEL",
    "BLENDFUNC",
    "BLENDEQUATION",
    "LOGICOP",
    "STENCIL",
    "COLORMASK",
    "DEPTH",
    "VIEWPORT",
    "SCISSOR",
    "BLENDCOLOR",
    "MULTISAMPLE",
    "CLIPPLANE",
    "COLORMATRIX",
    "VERTEXPROGRAM",
    "FRAGMENTPROGRAM",
    "POINTSPRITE",
    "PROGRAM",
    "CLAMPCOLOR",
    "HINT",
    "SAMPLEMASKI",
    "PRIMITIVERESTARTINDEX",
    "CLIPCONTROL",

    /// osgFX namespace
    "VALIDATOR",
    "VIEWMATRIXEXTRACTOR",

    /// osgNV namespace
    "OSGNV_PARAMETER_BLOCK",

    /// osgNVExt namespace
    "OSGNVEXT_TEXTURE_SHADER",
    "OSGNVEXT_VERTEX_PROGRAM",
    "OSGNVEXT_REGISTER_COMBINERS",

    /// osgNVCg namespace
    "OSGNVCG_PROGRAM",

    /// osgNVSlang namespace
    "OSGNVSLANG_PROGRAM",

    /// osgNVParse
    "OSGNVPARSE_PROGRAM_PARSER",

    "UNIFORMBUFFERBINDING",
    "TRANSFORMFEEDBACKBUFFERBINDING",

    "ATOMICCOUNTERBUFFERBINDING",

    "PATCH_PARAMETER",

    "FRAME_BUFFER_OBJECT",

    "VERTEX_ATTRIB_DIVISOR",

    "SHADERSTORAGEBUFFERBINDING",
};

const size_t c_MaxAttributeType = osg::StateAttribute::SHADERSTORAGEBUFFERBINDING + 1;

PropertyTreeAttributeUnknownItem::PropertyTreeAttributeUnknownItem(PropertyTreeItem *parent, const osg::StateAttribute::TypeMemberPair& attribute)
    : PropertyTreeItem(parent)
    , m_Attribute(attribute)
{
    QString name;
    if(m_Attribute.first < c_MaxAttributeType)
    {
        name.sprintf("%s[%d]", c_TypeName[m_Attribute.first], m_Attribute.second);
    }
    else
    {
        name.sprintf("%s:%x[%d]", tr("Unknown attribute"), m_Attribute.first, m_Attribute.second);
    }
    m_Name = name;
}

PropertyTreeAttributeUnknownItem::~PropertyTreeAttributeUnknownItem()
{
}

Qt::ItemFlags PropertyTreeAttributeUnknownItem::flags(int column) const
{
    return PropertyTreeItem::flags(column);
}

QVariant PropertyTreeAttributeUnknownItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            return QVariant("Unknown value");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeAttributeUnknownItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}
