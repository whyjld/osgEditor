#include "propertytreestatesetitem.h"
#include "propertytreepropertyitem.h"

#include <qpushbutton.h>

#include <sstream>

PropertyTreeStateSetItem::PropertyTreeStateSetItem(PropertyTreeItem *parent, const QString& name, const StateSetGetter_t& creator, const StateSetGetter_t& getter)
    : PropertyTreeItem(parent)
    , m_Name(name)
    , m_Creator(creator)
    , m_StateSet(getter())
{
    if(!!m_StateSet)
    {
        CreateStateSetProperty();
    }
}

PropertyTreeStateSetItem::~PropertyTreeStateSetItem()
{
}

Qt::ItemFlags PropertyTreeStateSetItem::flags(int column) const
{
    return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
}

QVariant PropertyTreeStateSetItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            return QVariant("...");
        };
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeStateSetItem::setData(int column, const QVariant &value, int role)
{
    return true;
}

bool PropertyTreeStateSetItem::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor = new QPushButton(parent);
    connect(dynamic_cast<QPushButton*>(editor), &QPushButton::clicked, this, &PropertyTreeStateSetItem::buttonClicked);
    return true;
}

bool PropertyTreeStateSetItem::setEditorData(QWidget* editor,const QModelIndex& index) const
{
    QPushButton* btn = dynamic_cast<QPushButton*>(editor);
    if(!!m_StateSet)
    {
        btn->setText("...");
    }
    else
    {
        btn->setText("New");
    }
    return true;
}

bool PropertyTreeStateSetItem::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    return true;
}

bool PropertyTreeStateSetItem::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QRect rect = option.rect;
    if(rect.width() > rect.height())
    {
        rect.setLeft(rect.right() - rect.height());
    }
    editor->setGeometry(rect);
    return true;
}

void PropertyTreeStateSetItem::buttonClicked(bool checked)
{
    if(!!m_StateSet)
    {
        //todo: show StateSet panel
    }
    else
    {
        if(CreateStateSet())
        {
            QPushButton* btn = dynamic_cast<QPushButton*>(sender());
            btn->setText("...");
        }
    }
}

bool PropertyTreeStateSetItem::CreateStateSet()
{
    m_StateSet = m_Creator();
    return !!m_StateSet && CreateStateSetProperty();
}

bool PropertyTreeStateSetItem::CreateStateSetProperty()
{
    return true;
}
