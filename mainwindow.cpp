#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scenetreemodel.h"

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <QFileDialog>
#include <QMessageBox>

#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tvSceneTree->setModel(new SceneTreeModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{
    //todo:Open file
    std::shared_ptr<QFileDialog> openDialog(new QFileDialog(this));
    openDialog->setWindowTitle(tr("Open Project"));
    openDialog->setDirectory(".");
    openDialog->setFileMode(QFileDialog::ExistingFile);

    QStringList filters;
    filters << tr("OSG Files(*.osg)") << tr("OSG Binary Files(*.osgb)") << tr("All Files(*.*)");
    openDialog->setNameFilters(filters);
    if(QDialog::Accepted == openDialog->exec())
    {
        QString file = openDialog->selectedFiles()[0];

        osg::ref_ptr<osg::Node> newNode(osgDB::readNodeFile(file.toStdString().c_str()));
        if(!!newNode)
        {
            ui->owSceneViewer->getViewer()->setSceneData(newNode);
            ((SceneTreeModel*)ui->tvSceneTree->model())->setSceneNode(newNode);
            ui->tvSceneTree->reset();
        }
        else
        {
            QMessageBox::information(NULL, tr("Error"), tr("Can't load scene file."));
        }
    }
}
