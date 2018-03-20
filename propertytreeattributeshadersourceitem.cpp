#include "propertytreeattributeshadersourceitem.h"
#include "propertytreeattributeshaderitem.h"
#include "propertytreeattributelistitem.h"
#include "propertytreepropertyitem.h"
#include "propertytreemodel.h"
#include "mainwindow.h"

#include <QPushButton>

#include <sstream>

PropertyTreeAttributeShaderSourceItem::PropertyTreeAttributeShaderSourceItem(PropertyTreeItem *parent)
    : PropertyTreeItem(parent)
{
    ChangeValue();
}

PropertyTreeAttributeShaderSourceItem::~PropertyTreeAttributeShaderSourceItem()
{
}

Qt::ItemFlags PropertyTreeAttributeShaderSourceItem::flags(int column) const
{
    return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
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

bool PropertyTreeAttributeShaderSourceItem::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (option);
    (index);
    QPushButton* btn = new QPushButton(parent);
    btn->setText("...");
    connect(btn, &QPushButton::released, this, &PropertyTreeAttributeShaderSourceItem::buttonClicked);

    editor = btn;
    return true;
}

bool PropertyTreeAttributeShaderSourceItem::setEditorData(QWidget* editor,const QModelIndex& index) const
{
    (editor);
    (index);
    return true;
}

bool PropertyTreeAttributeShaderSourceItem::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    (editor);
    (model);
    (index);
    return true;
}

bool PropertyTreeAttributeShaderSourceItem::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (index);
    QRect rect = option.rect;
    if(rect.width() > rect.height())
    {
        rect.setLeft(rect.right() - rect.height());
    }
    editor->setGeometry(rect);
    return true;
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
        std::stringstream ss(parent->Shader->getShaderSource());
        std::string line;
        for(std::getline(ss, line);!ss.eof();std::getline(ss, line))
        {
            if(line.length() > 0)
            {
                break;
            }
        }
        m_Value = (line + " ...").c_str();
    }
}
