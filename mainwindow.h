#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <osg/ref_ptr>
#include <osgFX/Scribe>
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
    const int c_MaxRecentFile = 10;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void editShader(osg::Shader* shader);

    Ui::MainWindow *getUI() const
    {
        return ui;
    }
private slots:
    void openRecentFile();

    void on_action_Open_triggered();

    void on_action_Clear_files_triggered();

    void on_actionE_xit_triggered();

    void on_tvSceneTree_clicked(const QModelIndex &index);

    void on_tvSceneTree_doubleClicked(const QModelIndex &index);

    void on_owSceneViewer_nodeClicked(QVariant i);

    void on_actionSave_As_triggered();

    void on_action_Save_triggered();

    void on_pbSSSave_clicked();

    void on_action_Find_toggled(bool arg1);

    void on_actionReplace_toggled(bool arg1);

    void on_pbClose_clicked();

    void on_tvSceneTree_createChild(const QModelIndex &index);

    void on_tvSceneTree_eraseNode(const QModelIndex &index);

    void on_tvSceneTree_eraseNodeButChildren(const QModelIndex &index);
    void on_cbProgramManager_currentIndexChanged(int index);

    void on_cbTextureManager_currentIndexChanged(int index);

private:
    void addRecent(const QString& file);
    void initializeRecentItem();
    void updateRecentItem(const QStringList& files);
    void loadSceneFile(const QString& file);

    void onSelectNode(const osg::NodePath& path);
    osg::NodePath treePath(const QModelIndex &index);

    Ui::MainWindow *ui;

    QSettings m_Settings;

    QString m_File;

    osg::ref_ptr<osgGA::TrackballManipulator> m_Manipulator;
    osg::ref_ptr<osgFX::Scribe> m_SelectScribe;
};

#endif // MAINWINDOW_H
