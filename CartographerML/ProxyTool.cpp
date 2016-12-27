#include "ProxyTool.h"

#include "ToolEvents.h"

using namespace CartographerML;

struct ProxyTool::Private
{
  AbstractTool* tool;
};

ProxyTool::ProxyTool(QObject* _parent) : AbstractTool(_parent), d(new Private)
{
}

ProxyTool::~ProxyTool()
{
  delete d;
}

AbstractTool * ProxyTool::tool() const
{
  return d->tool;
}

void ProxyTool::setTool(AbstractTool* _tool)
{
  if(d->tool != _tool)
  {
    if(d->tool)
    {
      disconnect(_tool, SIGNAL(hoverEnabledChanged()), this, SLOT(updateHoverEnabled()));
    }
    d->tool = _tool;
    if(d->tool)
    {
      connect(_tool, SIGNAL(hoverEnabledChanged()), this, SLOT(updateHoverEnabled()));
      setHoveredEnabled(d->tool->isHoverEnabled());
    }
    emit(toolChanged());
  }
}

void CartographerML::ProxyTool::updateHoverEnabled()
{
  if(d->tool)
  {
    setHoveredEnabled(d->tool->isHoverEnabled());
  }
}

void CartographerML::ProxyTool::toolActivated()
{
  emit(activated());
}

void CartographerML::ProxyTool::toolDeactivated()
{
  emit(deactivated());
}

#define D_EVENT(_NAME_, _TYPE_)                     \
  void ProxyTool::_NAME_(_TYPE_* _event)            \
  {                                                 \
    AbstractTool* t = d->tool;                      \
    if(t)                                           \
    {                                               \
      t->_NAME_(_event);                            \
      if(t != d->tool and not _event->isAccepted()) \
      {                                             \
        _NAME_(_event);                             \
      }                                             \
    }                                               \
  }

D_EVENT(mouseDoubleClickEvent,  MouseToolEvent)
D_EVENT(mouseMoveEvent,         MouseToolEvent)
D_EVENT(mousePressEvent,        MouseToolEvent)
D_EVENT(mouseReleaseEvent,      MouseToolEvent)
D_EVENT(wheelEvent,             WheelToolEvent)




#include "moc_ProxyTool.cpp"
