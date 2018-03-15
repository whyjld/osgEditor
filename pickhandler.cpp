#include "pickhandler.h"

PickHandler::PickHandler(OnMouseEvent_t onMouseEvent)
 : m_MouseEvent(onMouseEvent)
{

}

PickHandler::~PickHandler()
{

}

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
    osg::ref_ptr<osgViewer::View> view = dynamic_cast<osgViewer::View*>(&aa);
    if (!view)
    {
        return false;
    }

    if(!!m_MouseEvent)
    {
        m_MouseEvent(ea.getEventType(), view, ea.getX(), ea.getY());
    }

    return false;
}
