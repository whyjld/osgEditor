#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scenetreemodel.h"

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
{
    ui->setupUi(this);

    ui->tvSceneTree->setModel(new SceneTreeModel());

    m_Manipulator->setAllowThrow(false);
    ui->owSceneViewer->getViewer()->setCameraManipulator(m_Manipulator);

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

        addRecent(file);
    }
    else
    {
        QMessageBox::information(NULL, tr("Error"), tr("Can't load scene file."));
    }
}

void MainWindow::on_action_Open_triggered()
{
    //todo:Open file
    std::shared_ptr<QFileDialog> openDialog(new QFileDialog(this));
    openDialog->setWindowTitle(tr("Open Project"));
    openDialog->setDirectory(".");
    openDialog->setFileMode(QFileDialog::ExistingFile);

    QStringList filters;
    filters << tr("Scene Files(*.osg *.osgb)") << tr("OSG Files(*.osg)") << tr("OSG Binary Files(*.osgb)") << tr("All Files(*.*)");
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
