#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scenetreeitem.h"
#include "propertytreeitem.h"
#include "propertytreemodel.h"
#include "propertytreedelegate.h"
#include "managerlistitem.h"

#include "createnodedialog.h"

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/Camera>
#include <osg/Switch>
#include <osg/Geode>
#include <osg/Node>
#include <osg/Program>
#include <osg/Texture>

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>

#include <memory>
#include <set>

class ResourceVisitor : public osg::NodeVisitor
{
public:
    ResourceVisitor(std::set<osg::Program*>& programs, std::set<osg::Texture*>& textures)
        : osg::NodeVisitor(TRAVERSE_ALL_CHILDREN)
        , m_Programs(programs)
        , m_Textures(textures)
    {

    }

    virtual void apply(osg::Node& node)
    {
        osg::StateSet* ss = node.getStateSet();
        if(nullptr != ss)
        {
            osg::Program* program = dynamic_cast<osg::Program*>(ss->getAttribute(osg::StateAttribute::PROGRAM));
            if(nullptr != program)
            {
                m_Programs.insert(program);
            }

            size_t tc = ss->getNumTextureAttributeLists();
            for(size_t i = 0;i < tc;++i)
            {
                osg::Texture* texture = dynamic_cast<osg::Texture*>(ss->getTextureAttribute(i, osg::StateAttribute::TEXTURE));
                if(nullptr != texture)
                {
                    m_Textures.insert(texture);
                }
            }
        }
        traverse(node);
    }
private:
    std::set<osg::Program*>& m_Programs;
    std::set<osg::Texture*>& m_Textures;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Settings("./config.ini", QSettings::IniFormat)
    , m_Manipulator(new osgGA::TrackballManipulator())
    , m_SelectScribe(new osgFX::Scribe())
{
    ui->setupUi(this);

    ui->tvProperty->setModel(new PropertyTreeModel(this));
    ui->tvProperty->setItemDelegate(new PropertyTreeDelegate(ui->tvProperty));

    ui->wSearch->setVisible(false);
    ui->wReplace->setVisible(false);

    ui->qsShaderSource->setSearchWidget(ui->wSearch, ui->leSearch, ui->leReplace);
    connect(ui->pbNext, SIGNAL(clicked()), ui->qsShaderSource, SLOT(searchNext()));
    connect(ui->pbReplace, SIGNAL(clicked()), ui->qsShaderSource, SLOT(replace()));
    connect(ui->pbReplaceAll, SIGNAL(clicked()), ui->qsShaderSource, SLOT(replaceAll()));

    ui->tvProgramProperty->setModel(new PropertyTreeModel(this));
    ui->tvProgramProperty->setItemDelegate(new PropertyTreeDelegate(ui->tvProgramProperty));
    ui->lvProgramManager->setModel(new QStandardItemModel(ui->lvProgramManager));

    ui->tvTextureProperty->setModel(new PropertyTreeModel(this));
    ui->tvTextureProperty->setItemDelegate(new PropertyTreeDelegate(ui->tvTextureProperty));
    ui->lvTextureManager->setModel(new QStandardItemModel(ui->lvTextureManager));

    ui->menu_Window->addAction(ui->dwSceneTree->toggleViewAction());
    ui->menu_Window->addAction(ui->dwNodeProperty->toggleViewAction());
    ui->menu_Window->addAction(ui->dwProgramProperty->toggleViewAction());
    ui->menu_Window->addAction(ui->dwProgramManager->toggleViewAction());
    ui->menu_Window->addAction(ui->dwTextureManager->toggleViewAction());

    tabifyDockWidget(ui->dwTextureManager, ui->dwProgramManager);
    ui->dwTextureManager->raise();

    tabifyDockWidget(ui->dwNodeProperty, ui->dwTextureProperty);
    tabifyDockWidget(ui->dwNodeProperty, ui->dwProgramProperty);
    ui->dwNodeProperty->raise();

    m_SelectScribe->setEnabled(true);
    m_SelectScribe->setWireframeColor(osg::Vec4(0.0, 0.0, 1.0, 1.0));

    initializeRecentItem();
    QStringList files = m_Settings.value("recentFileList").toStringList();
    updateRecentItem(files);

    m_Manipulator->setAllowThrow(false);
    ui->owSceneViewer->getViewer()->setCameraManipulator(m_Manipulator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRecent(const QString& file)
{
    QStringList files = m_Settings.value("recentFileList").toStringList();

    int index = files.indexOf(file);
    if(0 == index)
    {
        return;
    }
    else if(-1 == index)
    {
        files.insert(files.begin(), file);
        if(files.size() > c_MaxRecentFile)
        {
            files.erase(files.begin() + c_MaxRecentFile);
        }
    }
    else
    {
        files.erase(files.begin() + index);
        files.insert(files.begin(), file);
    }
    m_Settings.setValue("recentFileList", files);

    updateRecentItem(files);
}

void MainWindow::initializeRecentItem()
{
    for(int i = 0;i < c_MaxRecentFile;++i)
    {
        QAction* recentAction = new QAction(this);
        connect(recentAction, SIGNAL(triggered()), this, SLOT(openRecentFile()));

        ui->menu_Recent_Files->insertAction(ui->actionNone, recentAction);
    }
}

void MainWindow::updateRecentItem(const QStringList& files)
{
    int i;
    int count = std::min(c_MaxRecentFile, files.size());

    for(i = 0;i < count;++i)
    {
        QString text = tr("&%1. %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());

        QAction* recentFileAction = ui->menu_Recent_Files->actions()[i];
        recentFileAction->setVisible(true);
        recentFileAction->setText(text);
        recentFileAction->setData(files[i]);
    }
    for(;i < c_MaxRecentFile;++i)
    {
        QAction* recentFileAction = ui->menu_Recent_Files->actions()[i];
        recentFileAction->setVisible(false);
    }

    if(files.size() > 0)
    {
        ui->actionNone->setVisible(false);
        ui->action_Clear_files->setEnabled(true);
    }
    else
    {
        ui->actionNone->setVisible(true);
        ui->actionNone->setEnabled(false);
        ui->action_Clear_files->setEnabled(false);
    }
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action != nullptr)
    {
        loadSceneFile(action->data().toString());
    }
}

void MainWindow::loadSceneFile(const QString& file)
{
    osg::ref_ptr<osg::Node> newNode(osgDB::readNodeFile(file.toStdString().c_str()));
    if(!!newNode)
    {
        ui->owSceneViewer->getViewer()->setSceneData(newNode);
        ui->tvSceneTree->setSceneNode(newNode);

        std::set<osg::Program*> programs;
        std::set<osg::Texture*> textures;

        newNode->accept(ResourceVisitor(programs, textures));

        if(programs.size() > 0)
        {
            QIcon icon("./glsl.png");
            QStandardItemModel* pm = dynamic_cast<QStandardItemModel*>(ui->lvProgramManager->model());
            for(auto i = programs.begin();i != programs.end();++i)
            {
                const std::string& name = (*i)->getName();
                pm->insertRow(pm->rowCount(), new ManagerListItem<osg::Program>(icon, QString(name.length() > 0 ? name.c_str() : tr("No name")), *i));
            }
        }

        if(textures.size() > 0)
        {
            QIcon icon("./glsl.png");
            QStandardItemModel* pm = dynamic_cast<QStandardItemModel*>(ui->lvTextureManager->model());
            for(auto i = textures.begin();i != textures.end();++i)
            {
                const std::string& name = (*i)->getName();
                pm->insertRow(pm->rowCount(), new ManagerListItem<osg::Texture>(icon, QString(name.length() > 0 ? name.c_str() : tr("No name")), *i));
            }
        }

        m_File = file;
        setWindowTitle(tr("osgEditor ") + m_File);
        addRecent(file);
    }
    else
    {
        QMessageBox::information(NULL, tr("Error"), tr("Can't load scene file."));
    }
}

void MainWindow::editShader(osg::Shader* shader)
{
    ui->qsShaderSource->setShader(shader);
}

void MainWindow::onSelectNode(const osg::NodePath& path)
{
    if(!path.empty())
    {
        ui->tvSceneTree->onSelectNode(path);
        osg::ref_ptr<osg::Node> node(path[path.size() - 1]);
        if(m_SelectScribe->getNumChildren() > 0)
        {
            osg::ref_ptr<osg::Node> old(m_SelectScribe->getChild(0));
            if(node.get() != old.get())
            {
                osg::Node::ParentList pl = m_SelectScribe->getParents();
                for(auto i = pl.begin();i != pl.end();++i)
                {
                    (*i)->replaceChild(m_SelectScribe.get(), old.get());
                }
                m_SelectScribe->removeChildren(0, m_SelectScribe->getNumChildren());
            }
            else
            {
                return;
            }
        }
        if(path.size() > 2)
        {
            osg::ref_ptr<osg::Geode> geode(dynamic_cast<osg::Geode*>(node.get()));
            if(!!geode)
            {
                osg::ref_ptr<osg::Group> parent(dynamic_cast<osg::Group*>(path[path.size() - 2]));
                parent->replaceChild(geode, m_SelectScribe);
                m_SelectScribe->addChild(geode);
            }
        }
        QString name = node->getName().length() > 0 ? node->getName().c_str() : tr("No Name");
        ui->lblNode->setText(name + QString(" : ") + QString(node->className()));\

        PropertyTreeModel* pm = (PropertyTreeModel*)ui->tvProperty->model();
        std::shared_ptr<PropertyTreeItem> pr(new PropertyTreeItem(pm, node));
        pm->setRoot(pr);
    }
}

osg::NodePath MainWindow::treePath(const QModelIndex &index)
{
    osg::NodePath ns;
    for(SceneTreeItem* i = (SceneTreeItem*)index.internalPointer();
        i != nullptr;
        i = i->parentItem())
    {
        ns.push_back(i->getNode());
    }

    osg::NodePath np;
    auto h = ns.rbegin();
    if((*h)->getNumParents() > 0)
    {
        np.push_back((*h)->getParents()[0]);
    }
    for(auto i = ns.rbegin();i != ns.rend();++i)
    {
        if(nullptr == *i)
        {
            np.clear();
            break;
        }
        np.push_back(*i);
    }
    return np;
}

void MainWindow::on_action_Open_triggered()
{
    //todo:Open file
    std::shared_ptr<QFileDialog> openDialog(new QFileDialog(this));
    openDialog->setWindowTitle(tr("Open Project"));
    openDialog->setDirectory(".");
    openDialog->setFileMode(QFileDialog::ExistingFile);

    QStringList filters;
    filters << tr("Scene Files(*.osg *.osgb *.osgt)") << tr("OSG Files(*.osg)") << tr("OSG Binary Files(*.osgb)") << tr("OSG ASCII Files(*.osgt)") << tr("All Files(*.*)");
    openDialog->setNameFilters(filters);
    if(QDialog::Accepted == openDialog->exec())
    {
        loadSceneFile(openDialog->selectedFiles()[0]);
    }
}

void MainWindow::on_action_Clear_files_triggered()
{
    //todo:clear recent files
    QStringList files;
    m_Settings.setValue("recentFileList", files);

    updateRecentItem(files);
}

void MainWindow::on_actionE_xit_triggered()
{
    //todo:Quit
    close();
}

void MainWindow::on_tvSceneTree_clicked(const QModelIndex &index)
{
    //todo:选中节点
    osg::NodePath np = treePath(index);
    if(!np.empty())
    {
        onSelectNode(np);
    }
}

void MainWindow::on_tvSceneTree_doubleClicked(const QModelIndex &index)
{
    //todo:转到节点
    osg::NodePath np = treePath(index);
    if(!np.empty())
    {
        onSelectNode(np);

        float dis = m_Manipulator->getDistance();

        osg::Vec3f ctr = m_Manipulator->getCenter();
        osg::Vec3f dir = np[np.size() - 1]->getBound().center() * osg::computeLocalToWorld(np) - ctr;
        dir.normalize();
        osg::Vec3f eye = dir * dis + ctr;
        dir *= -1.0f;

        osg::Vec3f up(0.0f, 0.0f, 1.0f);
        osg::Vec3f right = dir ^ up;

        up = right ^ dir;

        m_Manipulator->setTransformation(eye, ctr, up);
    }
}

void MainWindow::on_owSceneViewer_nodeClicked(QVariant i)
{
    //todo:转到节点
    auto intersection = i.value<osgUtil::LineSegmentIntersector::Intersection>();
    if(intersection.nodePath.size() > 0)
    {
        onSelectNode(intersection.nodePath);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    std::shared_ptr<QFileDialog> saveDialog(new QFileDialog(this));
    saveDialog->setWindowTitle(tr("Save As"));
    saveDialog->setDirectory(".");
    saveDialog->setDefaultSuffix(".osgb");
    saveDialog->setFileMode(QFileDialog::AnyFile);

    QStringList filters;
    filters << tr("Scene Files(*.osg *.osgb)") << tr("OSG Files(*.osg)") << tr("OSG Binary Files(*.osgb)") << tr("All Files(*.*)");
    saveDialog->setNameFilters(filters);
    if(QDialog::Accepted == saveDialog->exec())
    {
        QString file = saveDialog->selectedFiles()[0];

        if(!!osgDB::writeNodeFile(*ui->owSceneViewer->getViewer()->getSceneData(), file.toStdString()))
        {
            addRecent(file);
        }
        else
        {
            QMessageBox::information(NULL, tr("Error"), tr("Can't write scene file."));
        }
    }
}

void MainWindow::on_action_Save_triggered()
{
    osgDB::writeNodeFile(*ui->owSceneViewer->getViewer()->getSceneData(), m_File.toStdString());
}

void MainWindow::on_pbSSSave_clicked()
{
    ui->qsShaderSource->apply();
}

void MainWindow::on_action_Find_toggled(bool arg1)
{
    if(ui->wSearch->isVisible() != arg1)
    {
        if(arg1)
        {
            if(ui->wReplace->isVisible())
            {
                ui->wReplace->setVisible(false);
            }
        }
        ui->wSearch->setVisible(arg1);
        ui->leSearch->setFocus();
    }
}

void MainWindow::on_actionReplace_toggled(bool arg1)
{
    if(ui->wReplace->isVisible() != arg1)
    {
        ui->wReplace->setVisible(arg1);
        if(ui->wSearch->isVisible() != arg1)
        {
            ui->wSearch->setVisible(arg1);
        }
        ui->leSearch->setFocus();
    }
}

void MainWindow::on_pbClose_clicked()
{
    ui->action_Find->setChecked(false);
}

void MainWindow::on_tvSceneTree_createChild(const QModelIndex &index)
{
    CreateNodeDialog::NodeType type;
    std::shared_ptr<CreateNodeDialog> dialog(new CreateNodeDialog(this));
    if(dialog->exec(type))
    {
        osg::ref_ptr<osg::Node> node;
        switch(type)
        {
        case CreateNodeDialog::ntGroup:
            node = new osg::Group();
            break;
        case CreateNodeDialog::ntMatrixTransform:
            node = new osg::MatrixTransform();
            break;
        case CreateNodeDialog::ntPositionAttitudeTransform:
            node = new osg::PositionAttitudeTransform();
            break;
        case CreateNodeDialog::ntCamera:
            node = new osg::Camera();
            break;
        case CreateNodeDialog::ntSwitch:
            node = new osg::Switch();
            break;
        case CreateNodeDialog::ntGeode:
            node = new osg::Geode();
            break;
        default:
            QMessageBox::warning(this, tr("Warning"), tr("Invalid node type"));
            break;
        }
        if(!!node)
        {
            if(!dialog->getName().isEmpty())
            {
                node->setName(dialog->getName().toStdString());
            }
        }
        ui->tvSceneTree->insertNode(index, node);
    }
}

void MainWindow::on_tvSceneTree_eraseNode(const QModelIndex &index)
{
    if(QMessageBox::Yes == QMessageBox::question(this, tr("Warning"), tr("Erase this node and its children?"), QMessageBox::Yes | QMessageBox::Cancel))
    {
        ui->tvSceneTree->eraseItem(index);
    }
}

void MainWindow::on_tvSceneTree_eraseNodeButChildren(const QModelIndex &index)
{
    if(QMessageBox::Yes == QMessageBox::question(this, tr("Warning"), tr("Erase this node?"), QMessageBox::Yes | QMessageBox::Cancel))
    {
        ui->tvSceneTree->eraseItem(index, false);
    }
}

void MainWindow::on_cbProgramManager_currentIndexChanged(int index)
{
    ui->lvProgramManager->setViewMode((0 == index) ? QListView::ListMode : QListView::IconMode);
}

void MainWindow::on_cbTextureManager_currentIndexChanged(int index)
{
    ui->lvTextureManager->setViewMode((0 == index) ? QListView::ListMode : QListView::IconMode);
}
