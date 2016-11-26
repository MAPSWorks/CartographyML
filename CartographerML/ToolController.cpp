#include "ToolController.h"

#include "ToolEvents.h"
#include "AbstractTool.h"

using namespace CartographerML;

struct ToolController::Private
{
  AbstractTool* tool = nullptr;
  MouseToolEvent mte;
  WheelToolEvent wte;
  AbstractFeaturesSource* currentFeaturesSource = nullptr;
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
  if(d->tool)
  {
    disconnect(d->tool, SIGNAL(hoverEnabledChanged()), this, SLOT(toolHoverEnabledHasChanged()));
    d->tool->toolDeactivated();
  }
  d->tool = _tool;
  emit(toolChanged());
  if(d->tool)
  {
    connect(d->tool, SIGNAL(hoverEnabledChanged()), this, SLOT(toolHoverEnabledHasChanged()));
    d->tool->toolActivated();
  }
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

void ToolController::wheelEvent(QWheelEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->wte.reset(*event);
    d->tool->wheelEvent(&d->wte);
    event->setAccepted(d->wte.isAccepted());
  } else {
    QQuickItem::wheelEvent(event);
  }
}

void ToolController::hoverEnterEvent(QHoverEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mouseMoveEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::hoverEnterEvent(event);
  }
}

void ToolController::hoverLeaveEvent(QHoverEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mouseMoveEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::hoverLeaveEvent(event);
  }
}

void ToolController::hoverMoveEvent(QHoverEvent* event)
{
  if(d->tool)
  {
    event->accept();
    d->mte.reset(*event);
    d->tool->mouseMoveEvent(&d->mte);
    event->setAccepted(d->mte.isAccepted());
  } else {
    QQuickItem::hoverMoveEvent(event);
  }
}

void ToolController::toolHoverEnabledHasChanged()
{
  setAcceptHoverEvents(d->tool->isHoverEnabled());
}

AbstractFeaturesSource* ToolController::currentFeaturesSource() const
{
  return d->currentFeaturesSource;
}

void ToolController::setCurrentFeaturesSource(AbstractFeaturesSource* _source)
{
  d->currentFeaturesSource = _source;
  emit(currentFeaturesSourceChanged());
  if(d->tool)
  {
    d->tool->setFeaturesSource(_source);
  }
}

#include "moc_ToolController.cpp"
