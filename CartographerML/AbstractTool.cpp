#include "AbstractTool.h"
#include "ToolEvents.h"

using namespace CartographerML;

struct AbstractTool::Private
{
  bool hoverEnabled = false;
};

AbstractTool::AbstractTool(QObject* _parent): QObject(_parent), d(new Private)
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

bool AbstractTool::isHoverEnabled() const
{
  return d->hoverEnabled;
}

void AbstractTool::setHoveredEnabled(bool _v)
{
  d->hoverEnabled = _v;
  emit(hoverEnabledChanged());
}


#include "moc_AbstractTool.cpp"
