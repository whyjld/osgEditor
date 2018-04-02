#include "propertytreeswitchitem.h"
#include "propertytreevectoritem.h"

#include <QStandardItemModel>

PropertyTreeSwitchItem::PropertyTreeSwitchItem(PropertyTreeItem* parent, osg::Switch* os)
    : PropertyTreeItem(parent)
    , m_Switch(os)
{
}

PropertyTreeSwitchItem::~PropertyTreeSwitchItem()
{
}

QVariant PropertyTreeSwitchItem::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("osg::Switch");
        case ptcValue:
            if(m_Switch->getNumChildren() > 0)
            {
                QString value("(");
                value += (m_Switch->getValue(0) ? "true" : "false");
                for(size_t i = 1;i < m_Switch->getNumChildren();++i)
                {
                    value += (m_Switch->getValue(0) ? ", true" : ", false");
                }
                value += QString(")");
                return QVariant(value);
            }
            else
            {
                return QVariant("()");
            }
        };
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeSwitchItem::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    (option);
    (index);
    QComboBox* cb = new QComboBox(parent);
    QStandardItemModel* model = new QStandardItemModel(cb);

    for(size_t i = 0;i < m_Switch->getNumChildren();++i)
    {
        QStandardItem* item = new QStandardItem(QString("%1%2").arg(tr("Child:").arg(i)));
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->appendRow(item);
    }
    cb->setModel(model);
    editor = cb;
    return true;
}

bool PropertyTreeSwitchItem::setEditorData(QWidget* editor, const QModelIndex& index)
{
    QComboBox* cb = dynamic_cast<QComboBox*>(editor);
    if(nullptr != cb)
    {
        QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(cb->model());
        PropertyTreeSwitchItem* item = static_cast<PropertyTreeSwitchItem*>(index.internalPointer());
        for(size_t i = 0;i < item->m_Switch->getNumChildren();++i)
        {
            model->item(i)->setData((item->m_Switch->getValue(i) ? Qt::Checked : Qt::Unchecked), Qt::CheckStateRole);
        }
    }
    return true;
}

bool PropertyTreeSwitchItem::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
{
    (model);
    PropertyTreeSwitchItem* item = (PropertyTreeSwitchItem*)index.internalPointer();
    if(nullptr != item)
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);
        if(nullptr != item && nullptr != cb)
        {
            QStandardItemModel* cbm = dynamic_cast<QStandardItemModel*>(cb->model());
            if(nullptr != cbm)
            {
                for(size_t i = 0;i < cbm->rowCount();++i)
                {
                    bool value = (Qt::Checked == cbm->item(i)->data(Qt::CheckStateRole));
                    if(item->m_Switch->getValue(i) != value)
                    {
                        item->m_Switch->setValue(i, value);
                    }
                }
            }
        }
    }
    return true;
}

bool PropertyTreeSwitchItem::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    (index);
    editor->setGeometry(option.rect);
    return true;
}
