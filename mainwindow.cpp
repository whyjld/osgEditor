#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scenetreeitem.h"
#include "scenetreemodel.h"
#include "propertytreemodel.h"
#include "propertytreedelegate.h"

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <QFileDialog>
#include <QMessageBox>

#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Settings("./config.ini", QSettings::IniFormat)
    , m_Manipulator(new osgGA::TrackballManipulator())
    , m_SelectScribe(new osgFX::Scribe())
{
    ui->setupUi(this);

    ui->tvSceneTree->setModel(new SceneTreeModel());
    ui->tvProperty->setModel(new PropertyTreeModel(this));
    ui->tvProperty->setItemDelegate(new PropertyTreeDelegate(ui->tvProperty));

    m_Manipulator->setAllowThrow(false);
    ui->owSceneViewer->getViewer()->setCameraManipulator(m_Manipulator);

    ui->wSearch->setVisible(false);
    ui->wReplace->setVisible(false);

    ui->qsShaderSource->setSearchWidget(ui->wSearch, ui->leSearch, ui->leReplace);
    connect(ui->pbNext, SIGNAL(clicked()), ui->qsShaderSource, SLOT(searchNext()));
    connect(ui->pbReplace, SIGNAL(clicked()), ui->qsShaderSource, SLOT(replace()));
    connect(ui->pbReplaceAll, SIGNAL(clicked()), ui->qsShaderSource, SLOT(replaceAll()));

    m_SelectScribe->setEnabled(true);
    m_SelectScribe->setWireframeColor(osg::Vec4(0.0, 0.0, 1.0, 1.0));

    initializeRecentItem();
    QStringList files = m_Settings.value("recentFileList").toStringList();
    updateRecentItem(files);
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
        ((SceneTreeModel*)ui->tvSceneTree->model())->setSceneNode(newNode);
        ui->tvSceneTree->reset();
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
        ui->lblNode->setText(name + QString(" : ") + QString(node->className()));
        ui->tvProperty->reset();
        ((PropertyTreeModel*)ui->tvProperty->model())->setObject(node.get());
        ui->tvProperty->reset();
        ui->tvProperty->resizeColumnToContents(0);
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
        ui->tvSceneTree->selectionModel()->setCurrentIndex(((SceneTreeModel*)ui->tvSceneTree->model())->index(intersection.nodePath), QItemSelectionModel::SelectCurrent);
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

void MainWindow::on_dwSceneTree_visibilityChanged(bool visible)
{
    if(ui->actionScene_Tree->isChecked() != visible)
    {
        ui->actionScene_Tree->setChecked(visible);
    }
}

void MainWindow::on_dwProperty_visibilityChanged(bool visible)
{
    if(ui->action_Property->isChecked() != visible)
    {
        ui->action_Property->setChecked(visible);
    }
}

void MainWindow::on_dwSource_visibilityChanged(bool visible)
{
    if(ui->actionShader_Source->isChecked() != visible)
    {
        ui->actionShader_Source->setChecked(visible);
    }
}

void MainWindow::on_actionScene_Tree_toggled(bool arg1)
{
    if(ui->dwSceneTree->isVisible() != arg1)
    {
        ui->dwSceneTree->setVisible(arg1);
    }
}

void MainWindow::on_action_Property_toggled(bool arg1)
{
    if(ui->dwProperty->isVisible() != arg1)
    {
        ui->dwProperty->setVisible(arg1);
    }
}

void MainWindow::on_actionShader_Source_toggled(bool arg1)
{
    if(ui->dwSource->isVisible() != arg1)
    {
        ui->dwSource->setVisible(arg1);
    }
}

void MainWindow::on_pbSSApply_clicked()
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
