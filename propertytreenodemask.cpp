#include "propertytreenodemask.h"

#include <QComboBox>
#include <QStandardItemModel>

PropertyTreeNodeMask::PropertyTreeNodeMask(PropertyTreeItem *parent, osg::Node* node)
    : PropertyTreeItem(parent)
    , m_Node(node)
{
}

PropertyTreeNodeMask::~PropertyTreeNodeMask()
{
}

Qt::ItemFlags PropertyTreeNodeMask::flags(int column) const
{
    return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
}

QVariant PropertyTreeNodeMask::data(int column, int role) const
{
    if(Qt::DisplayRole == role)
    {
        switch(column)
        {
        case ptcProperty:
            return QVariant("NodeMask");
        case ptcValue:
            return QVariant(m_Node->getNodeMask());
        default:
            break;
        };
    }
    return PropertyTreeItem::data(column, role);
}

bool PropertyTreeNodeMask::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (option);
    (index);

    QComboBox* cb = new QComboBox(parent);
    QStandardItemModel* model = new QStandardItemModel(cb);
    for(size_t i = 0;i < sizeof(osg::Node::NodeMask) * 8;++i)
    {
        QStandardItem* item = new QStandardItem(QString("Layer:%1").arg(i));
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        model->appendRow(item);
    }
    cb->setModel(model);

    editor = cb;
    return true;
}

bool PropertyTreeNodeMask::setEditorData(QWidget* editor,const QModelIndex& index) const
{
    PropertyTreeNodeMask* nm = (PropertyTreeNodeMask*)index.internalPointer();
    if(nullptr != nm)
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);
        if(nullptr != cb)
        {
            QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(cb->model());
            if(nullptr != model)
            {
                osg::Node::NodeMask mask = nm->m_Node->getNodeMask();
                for(size_t i = 0;i < sizeof(osg::Node::NodeMask) * 8;++i)
                {
                    model->item(i)->setData(((mask & (1 << i)) ? Qt::Checked : Qt::Unchecked), Qt::CheckStateRole);
                }
            }
        }
    }

    return true;
}

bool PropertyTreeNodeMask::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    (model);
    PropertyTreeNodeMask* nm = (PropertyTreeNodeMask*)index.internalPointer();
    if(nullptr != nm)
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);
        if(nullptr != cb)
        {
            QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(cb->model());
            if(nullptr != model)
            {
                osg::Node::NodeMask mask = 0;
                for(size_t i = 0;i < model->rowCount();++i)
                {
                    if(Qt::Checked == model->item(i)->data(Qt::CheckStateRole))
                    {
                        mask |= (1 << i);
                    }
                }
                nm->m_Node->setNodeMask(mask);
            }
        }
    }

    return true;
}

bool PropertyTreeNodeMask::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (index);
    editor->setGeometry(option.rect);
    return true;
}
