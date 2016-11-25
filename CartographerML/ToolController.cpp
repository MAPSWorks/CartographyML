#include "ToolController.h"

#include "ToolEvents.h"
#include "AbstractTool.h"

using namespace CartographerML;

struct ToolController::Private
{
  AbstractTool* tool = nullptr;
  MouseToolEvent mte;
};

ToolController::ToolController(QQuickItem* parent): QQuickItem(parent), d(new Private)
{
  setAcceptedMouseButtons(Qt::AllButtons);
}

ToolController::~ToolController()
{
  delete d;
}

AbstractTool* ToolController::tool() const
{
  return d->tool;
}

void ToolController::setTool(AbstractTool* _tool)
{
  d->tool = _tool;
  emit(toolChanged());
}

void ToolController::mouseDoubleClickEvent(QMouseEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mouseDoubleClickEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::mouseDoubleClickEvent(event);
  }
}

void ToolController::mouseMoveEvent(QMouseEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mouseMoveEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::mouseMoveEvent(event);
  }
}

void ToolController::mousePressEvent(QMouseEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mousePressEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::mousePressEvent(event);
  }
}

void ToolController::mouseReleaseEvent(QMouseEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mouseReleaseEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::mouseReleaseEvent(event);
  }
}

#include "moc_ToolController.cpp"
