#ifndef QOSGWIDGET_H
#define QOSGWIDGET_H

#include <QOpenGLWidget>
#include <QVector>
#include <QVariant>
#include <osg/ref_ptr>
#include <osg/Switch>
#include <osg/MatrixTransform>
#include <osgGA/EventQueue>
#include <osgUtil/LineSegmentIntersector>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>

#include <osgManipulator/Selection>
#include <osgManipulator/CommandManager>
#include <osgManipulator/TrackballDragger>
#include <osgManipulator/TranslateAxisDragger>

Q_DECLARE_METATYPE(osgUtil::LineSegmentIntersector::Intersection)

class PickHandler;

class QOSGWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QOSGWidget(QWidget *parent = nullptr);
    ~QOSGWidget();

    osgViewer::Viewer* getViewer() const
    {
        return m_OSGViewer.get();
    }
signals:
    void nodeClicked(QVariant intersection);

public slots:

private:
    virtual void paintGL();
    virtual void resizeGL(int, int);
    virtual void initializeGL();

    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual bool event(QEvent* event);

    osg::GraphicsContext::Traits* CreateTraits();

    void OnOSGMouseEvent(osgGA::GUIEventAdapter::EventType type, osg::ref_ptr<osgViewer::View>& view, float x, float y);

    osgGA::EventQueue* getEventQueue() const
    {
        return m_OSGGraphicsWindow->getEventQueue();
    }

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_OSGGraphicsWindow;
    osg::ref_ptr<osgViewer::Viewer> m_OSGViewer;

    qreal m_ScaleX, m_ScaleY;

    float m_MouseX, m_MouseY;
    PickHandler* m_PickHandler;
};

#endif // QOSGWIDGET_H
