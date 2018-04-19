#include "propertytreeitem.h"
#include "propertytreeobjectitem.h"
#include "propertytreenodeitem.h"
#include "propertytreematrixtransformitem.h"
#include "propertytreepositionattitudetransformitem.h"
#include <QStringList>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Drawable>
#include <osg/Geometry>
#include <osg/PrimitiveSet>

PropertyTreeItem::PropertyTreeItem(PropertyTreeItem *parent)
    : m_Model((nullptr != parent) ? parent->m_Model : nullptr)
    , m_ParentItem(parent)
{
}

PropertyTreeItem::PropertyTreeItem(PropertyTreeModel* model, osg::Object* object)
    : m_Model(model)
    , m_ParentItem(nullptr)
{
    if(object != nullptr)
    {
        m_ChildItems.append(new PropertyTreeObjectItem(this, object));
        osg::Node* node = dynamic_cast<osg::Node*>(object);
        if(node != nullptr)
        {
            m_ChildItems.append(new PropertyTreeNodeItem(this, node));
        }
        osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(object);
        if(mt != nullptr)
        {
            m_ChildItems.append(new PropertyTreeMatrixTransformItem(this, mt));
        }
        osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(object);
        if(pat != nullptr)
        {
            m_ChildItems.append(new PropertyTreePositionAttitudeTransformItem(this, pat));
        }
    }
}

PropertyTreeItem::~PropertyTreeItem()
{
    qDeleteAll(m_ChildItems);
}

PropertyTreeItem *PropertyTreeItem::child(int row)
{
    return m_ChildItems.value(row);
}

int PropertyTreeItem::childCount() const
{
    return m_ChildItems.count();
}

int PropertyTreeItem::columnCount() const
{
    return ptcCount;
}

int PropertyTreeItem::row() const
{
    if (nullptr != m_ParentItem)
    {
        return m_ParentItem->m_ChildItems.indexOf(const_cast<PropertyTreeItem*>(this));
    }
    return 0;
}

PropertyTreeItem *PropertyTreeItem::parentItem()
{
    return m_ParentItem;
}

Qt::ItemFlags PropertyTreeItem::flags(int column) const
{
    (column);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant PropertyTreeItem::data(int column, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch(column)
        {
        case ptcProperty:
            if(nullptr == m_ParentItem)
            {
                return QVariant(QObject::tr("Property"));
            }
            break;
        case ptcValue:
            if(nullptr == m_ParentItem)
            {
                return QVariant(QObject::tr("Value"));
            }
            break;
        default:
            return QVariant();
        }
        break;
    case Qt::TextAlignmentRole:
        switch(column)
        {
        case ptcProperty:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case ptcValue:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        default:
            break;
        }
        break;
    default:
        break;
    }
    return QVariant();
}

bool PropertyTreeItem::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (painter);
    (option);
    (index);
    return false;
}

bool PropertyTreeItem::afterPaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (painter);
    (option);
    (index);
    return false;
}

bool PropertyTreeItem::sizeHint(QSize& size, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (size);
    (option);
    (index);
    return false;
}

bool PropertyTreeItem::setData(int column, const QVariant &value, int role)
{
    (column);
    (value);
    (role);
    return false;
}

bool PropertyTreeItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    (event);
    (model);
    (option);
    (index);
    return false;
}

bool PropertyTreeItem::createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (editor);
    (parent);
    (option);
    (index);
    return false;
}

bool PropertyTreeItem::setEditorData(QWidget* editor,const QModelIndex& index) const
{
    (editor);
    (index);
    return false;
}

bool PropertyTreeItem::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    (editor);
    (model);
    (index);
    return false;
}

bool PropertyTreeItem::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (editor);
    (option);
    (index);
    return false;
}
