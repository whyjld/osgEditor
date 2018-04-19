#ifndef PROPERTYTREEMODEL_H
#define PROPERTYTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <osg/ref_ptr>
#include <osg/Node>
#include <osg/Geode>
#include <osg/MatrixTransform>

#include <memory>
#include <hash_map>

class PropertyTreeItem;

class PropertyTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit PropertyTreeModel(QObject *window);
    ~PropertyTreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setRoot(const std::shared_ptr<PropertyTreeItem>& root);

    QModelIndex createIndex(int row, int col, void* data) const
    {
        return QAbstractItemModel::createIndex(row, col, data);
    }

    void beginResetModel()
    {
        QAbstractItemModel::beginResetModel();
    }
    void endResetModel()
    {
        QAbstractItemModel::endResetModel();
    }

    void beginInsertRows(const QModelIndex &parent, int first, int last)
    {
        QAbstractItemModel::beginInsertRows(parent, first, last);
    }
    void endInsertRows()
    {
        QAbstractItemModel::endInsertRows();
    }

    void beginRemoveRows(const QModelIndex &parent, int first, int last)
    {
        QAbstractItemModel::beginRemoveRows(parent, first, last);
    }
    void endRemoveRows()
    {
        QAbstractItemModel::endRemoveRows();
    }

    bool beginMoveRows(const QModelIndex &sourceParent, int sourceFirst, int sourceLast, const QModelIndex &destinationParent, int destinationRow)
    {
        QAbstractItemModel::beginMoveRows(sourceParent, sourceFirst, sourceLast, destinationParent, destinationRow);
    }

    void endMoveRows()
    {
        QAbstractItemModel::endMoveRows();
    }

    QObject* Window;
private:
    std::shared_ptr<PropertyTreeItem> m_RootItem;
};

#endif // PROPERTYTREEMODEL_H
