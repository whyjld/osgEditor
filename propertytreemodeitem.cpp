#include "propertytreemodeitem.h"
#include "propertytreemodelistitem.h"

#include <QComboBox>
#include <QStandardItemModel>

#include <memory>

GLenum c_Enums[] =
{
    GL_BLEND,
    GL_COLOR_LOGIC_OP,
    GL_CULL_FACE,
    GL_LIGHTING,
#if defined(GL_ARB_debug_output)
    GL_DEBUG_OUTPUT,
    GL_DEBUG_OUTPUT_SYNCHRONOUS,
#endif//GL_ARB_debug_output
    GL_DEPTH_CLAMP,
    GL_DEPTH_TEST,
    GL_DITHER,
    GL_FRAMEBUFFER_SRGB,
    GL_LINE_SMOOTH,
#if defined(GL_VERSION_1_3)
    GL_MULTISAMPLE,
#endif//GL_VERSION_1_3
    GL_POLYGON_OFFSET_FILL,
    GL_POLYGON_OFFSET_LINE,
    GL_POLYGON_OFFSET_POINT,
    GL_POLYGON_SMOOTH,
    GL_PRIMITIVE_RESTART,
#if defined(GL_ARB_ES3_compatibility)
    GL_PRIMITIVE_RESTART_FIXED_INDEX,
#endif//GL_ARB_ES3_compatibility
    GL_RASTERIZER_DISCARD,
#if defined(GL_ARB_multisample)
    GL_SAMPLE_ALPHA_TO_COVERAGE,
    GL_SAMPLE_ALPHA_TO_ONE,
    GL_SAMPLE_COVERAGE,
    GL_SAMPLE_SHADING,
    GL_SAMPLE_MASK,
#endif//GL_ARB_multisample
    GL_SCISSOR_TEST,
    GL_STENCIL_TEST,
    GL_TEXTURE_CUBE_MAP_SEAMLESS,
};

char* c_Names[] =
{
    "GL_BLEND",
    "GL_COLOR_LOGIC_OP",
    "GL_CULL_FACE",
    "GL_LIGHTING",
#if defined(GL_ARB_debug_output)
    "GL_DEBUG_OUTPUT",
    "GL_DEBUG_OUTPUT_SYNCHRONOUS",
#endif//GL_ARB_debug_output
    "GL_DEPTH_CLAMP",
    "GL_DEPTH_TEST",
    "GL_DITHER",
    "GL_FRAMEBUFFER_SRGB",
    "GL_LINE_SMOOTH",
#if defined(GL_VERSION_1_3)
    "GL_MULTISAMPLE",
#endif//GL_VERSION_1_3
    "GL_POLYGON_OFFSET_FILL",
    "GL_POLYGON_OFFSET_LINE",
    "GL_POLYGON_OFFSET_POINT",
    "GL_POLYGON_SMOOTH",
    "GL_PRIMITIVE_RESTART",
#if defined(GL_ARB_ES3_compatibility)
    "GL_PRIMITIVE_RESTART_FIXED_INDEX",
#endif//GL_ARB_ES3_compatibility
    "GL_RASTERIZER_DISCARD",
#if defined(GL_ARB_multisample)
    "GL_SAMPLE_ALPHA_TO_COVERAGE",
    "GL_SAMPLE_ALPHA_TO_ONE",
    "GL_SAMPLE_COVERAGE",
    "GL_SAMPLE_SHADING",
    "GL_SAMPLE_MASK",
#endif//GL_ARB_multisample
    "GL_SCISSOR_TEST",
    "GL_STENCIL_TEST",
    "GL_TEXTURE_CUBE_MAP_SEAMLESS",
};

char* c_Hints[] =
{
    "If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc.",
    "If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values. See glLogicOp.",
    "If enabled, cull polygons based on their winding in window coordinates. See glCullFace.",
    "",
#if defined(GL_ARB_debug_output)
    "If enabled, debug messages are produced by a debug context. When disabled, the debug message log is silenced. Note that in a non-debug context, very few, if any messages might be produced, even when GL_DEBUG_OUTPUT is enabled.",
    "If enabled, debug messages are produced synchronously by a debug context. If disabled, debug messages may be produced asynchronously. In particular, they may be delayed relative to the execution of GL commands, and the debug callback function may be called from a thread other than that in which the commands are executed. See glDebugMessageCallback.",
#endif//GL_ARB_debug_output
    "If enabled, the -wc <= zc <= wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping). See glDepthRange.",
    "If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled. See glDepthFunc and glDepthRange.",
    "If enabled, dither color components or indices before they are written to the color buffer.",
    "If enabled and the value of GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING for the framebuffer attachment corresponding to the destination buffer is GL_SRGB, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending.",
    "If enabled, draw lines with correct filtering. Otherwise, draw aliased lines. See glLineWidth.",
#if defined(GL_VERSION_1_3)
    "If enabled, use multiple fragment samples in computing the final color of a pixel. See glSampleCoverage.",
#endif//GL_VERSION_1_3
    "If enabled, and if the polygon is rendered in GL_FILL mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.",
    "If enabled, and if the polygon is rendered in GL_LINE mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.",
    "If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in GL_POINT mode. See glPolygonOffset.",
    "If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back.",
    "Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index. See glPrimitiveRestartIndex.",
#if defined(GL_ARB_ES3_compatibility)
    "Enables primitive restarting with a fixed index. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the fixed primitive index for the specified index type. The fixed index is equal to 2n-1 where n is equal to 8 for GL_UNSIGNED_BYTE, 16 for GL_UNSIGNED_SHORT and 32 for GL_UNSIGNED_INT.",
#endif//GL_ARB_ES3_compatibility
    "If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization. Furthermore, when enabled, glClear, glClearBufferData, glClearBufferSubData, glClearTexImage, and glClearTexSubImage are ignored.",
#if defined(GL_ARB_multisample)
    "If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value.",
    "If enabled, each sample alpha value is replaced by the maximum representable alpha value.",
    "If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage.",
    "If enabled, the active fragment shader is run once for each covered sample, or at fraction of this rate as determined by the current value of GL_MIN_SAMPLE_SHADING_VALUE. See glMinSampleShading.",
    "If enabled, the sample coverage mask generated for a fragment during rasterization will be ANDed with the value of GL_SAMPLE_MASK_VALUE before shading occurs. See glSampleMaski.",
#endif//GL_ARB_multisample
    "If enabled, discard fragments that are outside the scissor rectangle. See glScissor.",
    "If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp.",
    "If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value.",
};

PropertyTreeModeItem::PropertyTreeModeItem(PropertyTreeItem *parent, osg::StateAttribute::GLMode mode)
    : PropertyTreeItem(parent)
    , m_Mode(mode)
{
    for(size_t i = 0;i < sizeof(c_Enums) / sizeof(c_Enums[0]);++i)
    {
        if(mode == c_Enums[i])
        {
            m_Name = QVariant(c_Names[i]);
            break;
        }
    }
    if(!m_Name.isValid())
    {
        m_Name = QVariant(tr("Unknown:0x") + QString::number(mode, 16));
    }
}

PropertyTreeModeItem::~PropertyTreeModeItem()
{
}

Qt::ItemFlags PropertyTreeModeItem::flags(int column) const
{
    return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
}

QVariant PropertyTreeModeItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            if(true)
            {
                PropertyTreeModeListItem* p = dynamic_cast<PropertyTreeModeListItem*>(m_ParentItem);
                if(nullptr != p)
                {
                    QString value;

                    auto state = p->ModeList[m_Mode];
                    if((state & osg::StateAttribute::ON) != 0)
                    {
                        value = QString("ON");
                    }
                    else
                    {
                        value = QString("OFF");
                    }
                    if((state & osg::StateAttribute::OVERRIDE) != 0)
                    {
                        value += QString(", OVERRIDE");
                    }
                    if((state & osg::StateAttribute::PROTECTED) != 0)
                    {
                        value += QString(", PROTECTED");
                    }
                    if((state & osg::StateAttribute::INHERIT) != 0)
                    {
                        value += QString(", INHERIT");
                    }
                    return QVariant(value);
                }
            }
            break;
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeModeItem::setData(int column, const QVariant &value, int role)
{
    return true;
}

bool PropertyTreeModeItem::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (option);
    (index);
    QComboBox* cb = new QComboBox(parent);

    QStandardItemModel* model = new QStandardItemModel(cb);

    {
        QStandardItem* item = new QStandardItem("ON");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->appendRow(item);
    }

    {
        QStandardItem* item = new QStandardItem("OVERRIDE");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->appendRow(item);
    }

    {
        QStandardItem* item = new QStandardItem("PROTECTED");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->appendRow(item);
    }

    {
        QStandardItem* item = new QStandardItem("INHERIT");
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->appendRow(item);
    }
    cb->setModel(model);

    editor = cb;
    return true;
}

bool PropertyTreeModeItem::setEditorData(QWidget* editor,const QModelIndex& index) const
{
    PropertyTreeModeItem* mi = (PropertyTreeModeItem*)index.internalPointer();
    if(nullptr != mi)
    {
        PropertyTreeModeListItem* ml = dynamic_cast<PropertyTreeModeListItem*>(mi->m_ParentItem);
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);
        if(nullptr != ml && nullptr != cb)
        {
            QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(cb->model());
            if(nullptr != model)
            {
                auto value = ml->ModeList[mi->m_Mode];
                for(size_t i = 0;i < model->rowCount();++i)
                {
                    model->item(i)->setData(((value & (1 << i)) ? Qt::Checked : Qt::Unchecked), Qt::CheckStateRole);
                }
            }
        }
    }

    return true;
}

bool PropertyTreeModeItem::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    PropertyTreeModeItem* mi = (PropertyTreeModeItem*)index.internalPointer();
    if(nullptr != mi)
    {
        PropertyTreeModeListItem* ml = dynamic_cast<PropertyTreeModeListItem*>(mi->m_ParentItem);
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);
        if(nullptr != ml && nullptr != cb)
        {
            QStandardItemModel* cbm = dynamic_cast<QStandardItemModel*>(cb->model());
            if(nullptr != cbm)
            {
                osg::StateAttribute::GLModeValue value = 0;
                for(size_t i = 0;i < cbm->rowCount();++i)
                {
                    if(Qt::Checked == cbm->item(i)->data(Qt::CheckStateRole))
                    {
                        value |= (1 << i);
                    }
                }
                ml->ModeList[mi->m_Mode] = value;
            }
        }
    }

    return true;
}

bool PropertyTreeModeItem::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (index);
    editor->setGeometry(option.rect);
    return true;
}
