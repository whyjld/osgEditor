#ifndef PICKHANDLER_H
#define PICKHANDLER_H

#include <osg/Node>
#include <osg/ref_ptr>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventHandler>
#include <osgViewer/View>

#include <functional>

typedef std::function<void(osgGA::GUIEventAdapter::EventType type, osg::ref_ptr<osgViewer::View>& view, float x, float y)> OnMouseEvent_t;

class PickHandler : public osgGA::GUIEventHandler
{
public:
    PickHandler(OnMouseEvent_t onMouseEvent);
    ~PickHandler();

    bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
private:
    OnMouseEvent_t m_MouseEvent;
};

#endif // PICKHANDLER_H
