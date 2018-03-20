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

    void setObject(const osg::ref_ptr<osg::Object>& obj);

    QObject* Window;
private:
    std::shared_ptr<PropertyTreeItem> m_RootItem;
};

#endif // PROPERTYTREEMODEL_H
