#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <osg/ref_ptr>
#include <osgGA/TrackballManipulator>

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    const int c_MaxRecentFile = 10;
private slots:
    void openRecentFile();

    void on_action_Open_triggered();

    void on_action_Clear_files_triggered();

    void on_actionE_xit_triggered();

    void on_tvSceneTree_clicked(const QModelIndex &index);

    void on_tvSceneTree_doubleClicked(const QModelIndex &index);

    void on_owSceneViewer_nodeClicked(QVariant i);

private:
    void addRecent(const QString& file);
    void initializeRecentItem();
    void updateRecentItem(const QStringList& files);
    void loadSceneFile(const QString& file);

    Ui::MainWindow *ui;

    QSettings m_Settings;

    osg::ref_ptr<osgGA::TrackballManipulator> m_Manipulator;
};

#endif // MAINWINDOW_H
