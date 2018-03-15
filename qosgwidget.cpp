#include "qosgwidget.h"
#include "pickhandler.h"

#include <cmath>
#include <QMouseEvent>

#include <osg/Geode>
#include <osg/Camera>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osgUtil/Optimizer>

QOSGWidget::QOSGWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_OSGGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(CreateTraits()))
    , m_OSGViewer(new osgViewer::Viewer)
    , m_ScaleX(1.0f)
    , m_ScaleY(1.0f)
    , m_PickHandler(new PickHandler(std::bind(&QOSGWidget::OnOSGMouseEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)))
{
    qRegisterMetaType<QVariant>("QVariant");

    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width(), this->height() );
    camera->setClearColor( osg::Vec4( 0.9f, 0.9f, 0.9f, 1.0f ) );
    float aspectRatio = static_cast<float>( this->width()) / static_cast<float>( this->height() );
    camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( m_OSGGraphicsWindow );
    m_OSGViewer->setCamera(camera);
    m_OSGViewer->addEventHandler(m_PickHandler);
    m_OSGViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    m_OSGViewer->realize();

    this->setMouseTracking(true);
}

QOSGWidget::~QOSGWidget()
{

}

void QOSGWidget::paintGL()
{
    m_OSGViewer->frame();
}

void QOSGWidget::resizeGL( int width, int height )
{
    getEventQueue()->windowResize(this->x() * m_ScaleX, this->y() * m_ScaleY, width * m_ScaleX, height * m_ScaleY);
    m_OSGGraphicsWindow->resized(this->x() * m_ScaleX, this->y() * m_ScaleY, width * m_ScaleX, height * m_ScaleY);
    osg::Camera* camera = m_OSGViewer->getCamera();
    camera->setViewport(0, 0, this->width() * m_ScaleX, this->height() * m_ScaleY);
}

void QOSGWidget::initializeGL()
{
}

void QOSGWidget::mouseMoveEvent(QMouseEvent* event)
{
    getEventQueue()->mouseMotion(event->x() * m_ScaleX, event->y() * m_ScaleY);
}

void QOSGWidget::mousePressEvent(QMouseEvent* event)
{
    unsigned int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    getEventQueue()->mouseButtonPress(event->x() * m_ScaleX, event->y() * m_ScaleY, button);
}

void QOSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    unsigned int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    getEventQueue()->mouseButtonRelease(event->x() * m_ScaleX, event->y() * m_ScaleY, button);
}

void QOSGWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    unsigned int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    getEventQueue()->mouseDoubleButtonPress(event->x() * m_ScaleX, event->y() * m_ScaleY, button);
}

void QOSGWidget::wheelEvent(QWheelEvent* event)
{
    int delta = event->delta();
    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
    getEventQueue()->mouseScroll(motion);
}

bool QOSGWidget::event(QEvent* event)
{
    bool handled = QOpenGLWidget::event(event);
    this->update();
    return handled;
}

osg::GraphicsContext::Traits* QOSGWidget::CreateTraits()
{
    osg::GraphicsContext::Traits* traits= new osg::GraphicsContext::Traits;

    traits->x = this->x();
    traits->y = this->y();
    traits->width = this->width();
    traits->height = this->height();
    traits->glContextVersion = "3.3";
    traits->glContextProfileMask = 1;

    return traits;
}

void QOSGWidget::OnOSGMouseEvent(osgGA::GUIEventAdapter::EventType type, osg::ref_ptr<osgViewer::View>& view, float x, float y)
{
    QVariant intersection;
    switch(type)
    {
    case osgGA::GUIEventAdapter::PUSH:
    case osgGA::GUIEventAdapter::DOUBLECLICK:
        if(true)
        {
            osgUtil::LineSegmentIntersector::Intersections intersections;
            if(view->computeIntersections(x, y, intersections))
            {
                intersection.setValue(*intersections.begin());
            }
            if(osgGA::GUIEventAdapter::PUSH == type)
            {
                emit nodeClicked(intersection);
            }
            else
            {
                emit nodeDoubleClicked(intersection);
            }
        }
        break;
    default:
        break;
    }
}

