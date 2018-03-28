#ifndef PROPERTYTREEBASEITEM_H
#define PROPERTYTREEBASEITEM_H

#include "propertytreeitem.h"

#include <QComboBox>

#include <functional>

template<typename Type_t>
class PropertyTreeBaseItem : public PropertyTreeItem
{
public:
    typedef std::function<Type_t()> Getter_t;
    typedef std::function<void(Type_t v)> Setter_t;

    template<typename Type_t>
    class ItemEditor
    {
    public:
        static bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index)
        {
            (editor);
            (parent);
            (option);
            (index);
            return false;
        }
        static bool setEditorData(QWidget* editor,const QModelIndex& index)
        {
            (editor);
            (index);
            return false;
        }
        static bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
        {
            (editor);
            (model);
            (index);
            return false;
        }
        static bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index)
        {
            (editor);
            (option);
            (index);
            return false;
        }
    };

    template<>
    class ItemEditor<bool>
    {
    public:
        static bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index)
        {
            (option);
            (index);
            QComboBox* cb = new QComboBox(parent);
            cb->addItem(tr("true"), true);
            cb->addItem(tr("false"), false);
            editor = cb;
            return true;
        }
        static bool setEditorData(QWidget* editor, const QModelIndex& index)
        {
            QComboBox* cb = dynamic_cast<QComboBox*>(editor);
            if(nullptr != cb)
            {
                PropertyTreeBaseItem* item = static_cast<PropertyTreeBaseItem*>(index.internalPointer());
                if(item->value())
                {
                    cb->setCurrentIndex(0);
                }
                else
                {
                    cb->setCurrentIndex(1);
                }
            }
            return true;
        }
        static bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index)
        {
            (model);
            QComboBox* cb = dynamic_cast<QComboBox*>(editor);
            if(nullptr != cb)
            {
                PropertyTreeBaseItem* item = static_cast<PropertyTreeBaseItem*>(index.internalPointer());
                switch(cb->currentIndex())
                {
                case 0:
                    item->setValue(true);
                    break;
                case 1:
                    item->setValue(false);
                    break;
                default:
                    break;
                }
            }
            return true;
        }
        static bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index)
        {
            (index);
            editor->setGeometry(option.rect);
            return true;
        }
    };

    PropertyTreeBaseItem(PropertyTreeItem *parent, const QString& name, Getter_t getter, Setter_t setter)
        : PropertyTreeItem(parent)
        , m_Getter(getter)
        , m_Setter(setter)
        , m_Name(name)
    {

    }

    PropertyTreeBaseItem(PropertyTreeItem *parent, const QString& name, Type_t& value)
        : PropertyTreeItem(parent)
        , m_Getter([value]()->Type_t
                    {
                        return value;
                    })
        , m_Setter([&value](Type_t v)
                    {
                        value = v;
                    })
        , m_Name(name)
    {

    }
    virtual ~PropertyTreeBaseItem()
    {

    }

    virtual Qt::ItemFlags flags(int column) const
    {
        return ((ptcValue == column) ? Qt::ItemIsEditable : 0) | PropertyTreeItem::flags(column);
    }

    virtual QVariant data(int column, int role) const
    {
        if(Qt::DisplayRole == role)
        {
            switch(column)
            {
            case ptcProperty:
                return m_Name;
            case ptcValue:
                return QVariant(m_Getter());
            }
        }
        return PropertyTreeItem::data(column, role);

    }
    virtual bool setData(int column, const QVariant& value, int role)
    {
        if(Qt::EditRole == role && ptcValue == column)
        {
            setValue(qvariant_cast<Type_t>(value));
            return true;
        }
        return PropertyTreeItem::setData(column, value, role);
    }

    Type_t value() const
    {
        return m_Getter();
    }

    void setValue(Type_t v)
    {
        m_Setter(v);
    }

    bool createEditor(QWidget*& editor, QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        return ItemEditor<Type_t>::createEditor(editor, parent, option, index);
    }

    virtual bool setEditorData(QWidget* editor, const QModelIndex& index) const
    {
        return ItemEditor<Type_t>::setEditorData(editor, index);
    }

    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
    {
        return ItemEditor<Type_t>::setModelData(editor, model, index);
    }

    virtual bool updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        return ItemEditor<Type_t>::updateEditorGeometry(editor, option, index);
    }
private:
    Getter_t m_Getter;
    Setter_t m_Setter;

    QVariant m_Name;
};

#endif // PROPERTYTREEBASEITEM_H
