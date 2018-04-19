#include "propertytreemodelistitem.h"
#include "propertytreemodeitem.h"

#include <QPushButton>

PropertyTreeModeListItem::PropertyTreeModeListItem(PropertyTreeItem *parent, const QString& name, osg::StateSet::ModeList& modeList)
    : PropertyTreeItem(parent)
    , ModeList(modeList)
    , m_Name(name)
{
    for(auto i = ModeList.begin();i != ModeList.end();++i)
    {
        m_ChildItems.push_back(new PropertyTreeModeItem(this, i->first));
    }
}

PropertyTreeModeListItem::~PropertyTreeModeListItem()
{
}

Qt::ItemFlags PropertyTreeModeListItem::flags(int column) const
{
    return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
}

QVariant PropertyTreeModeListItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return m_Name;
        case ptcValue:
            return QVariant("...");
        }
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeModeListItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return true;
}

bool PropertyTreeModeListItem::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (option);
    (index);
    editor = new QPushButton(parent);
    dynamic_cast<QPushButton*>(editor)->setText(tr("Add"));
    connect(dynamic_cast<QPushButton*>(editor), &QPushButton::clicked, this, &PropertyTreeModeListItem::buttonClicked);
    return true;
}

bool PropertyTreeModeListItem::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    (editor);
    (index);
    return true;
}

bool PropertyTreeModeListItem::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    (editor);
    (model);
    (index);
    return true;
}

bool PropertyTreeModeListItem::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (index);
    QRect rect = option.rect;
    if(rect.width() > editor->width())
    {
        rect.setLeft(rect.right() - editor->width());
    }
    editor->setGeometry(rect);
    return true;
}

void PropertyTreeModeListItem::buttonClicked(bool checked)
{
    (checked);
    //todo: Add a mode item.
}
