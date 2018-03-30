#include "addattributedialog.h"
#include "ui_addattributedialog.h"

#include <QCompleter>

const osg::StateAttribute::Type c_Types[] =
{
    osg::StateAttribute::TEXTURE,
    osg::StateAttribute::POLYGONMODE,
    osg::StateAttribute::POLYGONOFFSET,
    osg::StateAttribute::MATERIAL,
    osg::StateAttribute::ALPHAFUNC,
    osg::StateAttribute::ANTIALIAS,
    osg::StateAttribute::COLORTABLE,
    osg::StateAttribute::CULLFACE,
    osg::StateAttribute::FOG,
    osg::StateAttribute::FRONTFACE,
    osg::StateAttribute::LIGHT,
    osg::StateAttribute::POINT,
    osg::StateAttribute::LINEWIDTH,
    osg::StateAttribute::LINESTIPPLE,
    osg::StateAttribute::POLYGONSTIPPLE,
    osg::StateAttribute::SHADEMODEL,
    osg::StateAttribute::TEXENV,
    osg::StateAttribute::TEXENVFILTER,
    osg::StateAttribute::TEXGEN,
    osg::StateAttribute::TEXMAT,
    osg::StateAttribute::LIGHTMODEL,
    osg::StateAttribute::BLENDFUNC,
    osg::StateAttribute::BLENDEQUATION,
    osg::StateAttribute::LOGICOP,
    osg::StateAttribute::STENCIL,
    osg::StateAttribute::COLORMASK,
    osg::StateAttribute::DEPTH,
    osg::StateAttribute::VIEWPORT,
    osg::StateAttribute::SCISSOR,
    osg::StateAttribute::BLENDCOLOR,
    osg::StateAttribute::MULTISAMPLE,
    osg::StateAttribute::CLIPPLANE,
    osg::StateAttribute::COLORMATRIX,
    osg::StateAttribute::VERTEXPROGRAM,
    osg::StateAttribute::FRAGMENTPROGRAM,
    osg::StateAttribute::POINTSPRITE,
    osg::StateAttribute::PROGRAM,
    osg::StateAttribute::CLAMPCOLOR,
    osg::StateAttribute::HINT,
    osg::StateAttribute::SAMPLEMASKI,
    osg::StateAttribute::PRIMITIVERESTARTINDEX,
    osg::StateAttribute::CLIPCONTROL,
    osg::StateAttribute::VALIDATOR,
    osg::StateAttribute::VIEWMATRIXEXTRACTOR,
    osg::StateAttribute::OSGNV_PARAMETER_BLOCK,
    osg::StateAttribute::OSGNVEXT_TEXTURE_SHADER,
    osg::StateAttribute::OSGNVEXT_VERTEX_PROGRAM,
    osg::StateAttribute::OSGNVEXT_REGISTER_COMBINERS,
    osg::StateAttribute::OSGNVCG_PROGRAM,
    osg::StateAttribute::OSGNVSLANG_PROGRAM,
    osg::StateAttribute::OSGNVPARSE_PROGRAM_PARSER,
    osg::StateAttribute::UNIFORMBUFFERBINDING,
    osg::StateAttribute::TRANSFORMFEEDBACKBUFFERBINDING,
    osg::StateAttribute::ATOMICCOUNTERBUFFERBINDING,
    osg::StateAttribute::PATCH_PARAMETER,
    osg::StateAttribute::FRAME_BUFFER_OBJECT,
    osg::StateAttribute::VERTEX_ATTRIB_DIVISOR,
    osg::StateAttribute::SHADERSTORAGEBUFFERBINDING,
};

const char* c_Typenames[] =
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
    "VALIDATOR",
    "VIEWMATRIXEXTRACTOR",
    "OSGNV_PARAMETER_BLOCK",
    "OSGNVEXT_TEXTURE_SHADER",
    "OSGNVEXT_VERTEX_PROGRAM",
    "OSGNVEXT_REGISTER_COMBINERS",
    "OSGNVCG_PROGRAM",
    "OSGNVSLANG_PROGRAM",
    "OSGNVPARSE_PROGRAM_PARSER",
    "UNIFORMBUFFERBINDING",
    "TRANSFORMFEEDBACKBUFFERBINDING",
    "ATOMICCOUNTERBUFFERBINDING",
    "PATCH_PARAMETER",
    "FRAME_BUFFER_OBJECT",
    "VERTEX_ATTRIB_DIVISOR",
    "SHADERSTORAGEBUFFERBINDING",
};

const size_t c_TypeElements[] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

AddAttributeDialog::AddAttributeDialog(osg::StateSet::AttributeList& list, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddAttributeDialog)
    , m_AttributeList(list)
{
    ui->setupUi(this);

    QStringList items;
    for(size_t i = 0;i < sizeof(c_Typenames) / sizeof(c_Typenames[0]);++i)
    {
        items << c_Typenames[i];
    }
    QCompleter *completer = new QCompleter(items, ui->cbAttribute);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->cbAttribute->addItems(items);
    ui->cbAttribute->setCompleter(completer);
}

AddAttributeDialog::~AddAttributeDialog()
{
    delete ui;
}

int AddAttributeDialog::exec(osg::StateAttribute::Type& type)
{
    int ret = QDialog::exec();
    int index = ui->cbAttribute->currentIndex();
    if(index >= 0 && index < sizeof(c_Types) / sizeof(c_Types[0]))
    {
        type = c_Types[index];
    }
    else
    {
        type = osg::StateAttribute::CAPABILITY;
    }
    return ret;
}

void AddAttributeDialog::on_cbAttribute_currentIndexChanged(int index)
{
    if(index >= 0
            && index < sizeof(c_TypeElements) / sizeof(c_TypeElements[0])
            && c_TypeElements[index] > 0)
    {
        ui->sbElement->setMinimum(0);
        ui->sbElement->setMaximum(c_TypeElements[index]);
        ui->sbElement->setEnabled(true);
    }
    else
    {
        ui->sbElement->setEnabled(false);
    }
}
