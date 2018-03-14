#ifndef SCENETREEMODEL_H
#define SCENETREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <osg/ref_ptr>
#include <osg/Node>
#include <osg/Geode>
#include <osg/MatrixTransform>

#include <memory>
#include <hash_map>

class SceneTreeItem;

class SceneTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SceneTreeModel(QObject *parent = 0);
    ~SceneTreeModel();

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

    QModelIndex index(const osg::Geode* geode);
    void setSceneNode(const osg::ref_ptr<osg::Node>& node);

    void ShowAll();
    void HideAllExpect(size_t i);
private:
    void buildGeodeIndex(osg::Node* node, SceneTreeItem* item, std::hash_map<const osg::Geode*, SceneTreeItem*>& index);

    std::shared_ptr<SceneTreeItem> m_RootItem;
    std::hash_map<const osg::Geode*, SceneTreeItem*> m_Index;
};

#endif // SCENETREEMODEL_H
