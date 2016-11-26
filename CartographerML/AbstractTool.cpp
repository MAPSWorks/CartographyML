#include "AbstractTool.h"
#include "ToolEvents.h"

using namespace CartographerML;

AbstractTool::AbstractTool(QObject* _parent): QObject(_parent)
{

}

AbstractTool::~AbstractTool()
{

}

void AbstractTool::mouseDoubleClickEvent(MouseToolEvent* event)
{
  event->setAccepted(false);
}

void AbstractTool::mouseMoveEvent(MouseToolEvent* event)
{
  event->setAccepted(false);
}

void AbstractTool::mousePressEvent(MouseToolEvent* event)
{
  event->setAccepted(false);
}

void AbstractTool::mouseReleaseEvent(MouseToolEvent* event)
{
  event->setAccepted(false);
}

void AbstractTool::wheelEvent(WheelToolEvent* event)
{
  event->setAccepted(false);
}

#include "moc_AbstractTool.cpp"
