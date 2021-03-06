#include "AbstractTool.h"

#include "ToolEvents.h"

using namespace CartographerML;

struct AbstractTool::Private
{
  bool hoverEnabled = false;
  AbstractFeaturesSource* featuresSource = nullptr;
  QQmlComponent* optionsComponent = nullptr;
  QQmlComponent* overlayComponent = nullptr;
  MapnikML::MapView* mapView = nullptr;
  QList<QObject*> children;
};

AbstractTool::AbstractTool(QObject* _parent): QObject(_parent), d(new Private)
{

}

AbstractTool::~AbstractTool()
{

}

void AbstractTool::toolActivated()
{

}

void AbstractTool::toolDeactivated()
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

AbstractFeaturesSource* AbstractTool::featuresSource() const
{
  return d->featuresSource;
}

void AbstractTool::setFeaturesSource(AbstractFeaturesSource* _source)
{
  d->featuresSource = _source;
  emit(featuresSourceChanged());
}

MapnikML::MapView* AbstractTool::mapView() const
{
  return d->mapView;
}

void AbstractTool::setMapView(MapnikML::MapView* _mapView)
{
  d->mapView = _mapView;
  emit(mapViewChanged());
}

QQmlComponent* AbstractTool::optionsComponent() const
{
  return d->optionsComponent;
}

void AbstractTool::setOptionsComponent(QQmlComponent* _component)
{
  d->optionsComponent = _component;
  emit(optionsComponentChanged());
}

QQmlComponent* AbstractTool::overlayComponent() const
{
  return d->overlayComponent;
}

void AbstractTool::setOverlayComponent(QQmlComponent* _component)
{
  d->overlayComponent = _component;
  emit(overlayComponentChanged());
}

QQmlListProperty<QObject> AbstractTool::childrenList() const
{
  return QQmlListProperty<QObject>(const_cast<AbstractTool*>(this), 0, AbstractTool::children_append, AbstractTool::children_count, AbstractTool::children_at, AbstractTool::children_clear);
}

// static children_* functions

void AbstractTool::children_append(QQmlListProperty<QObject>* _tool, QObject* _child)
{
  _child->setParent(_tool->object);
}

int AbstractTool::children_count(QQmlListProperty<QObject>* _tool)
{
  return _tool->object->children().count();
}

QObject* AbstractTool::children_at(QQmlListProperty<QObject>* _tool, int _index)
{
  return _tool->object->children()[_index];
}

void AbstractTool::children_clear(QQmlListProperty<QObject>* _tool)
{
  for(QObject* obj : _tool->object->children())
  {
    obj->setParent(nullptr);
    obj->deleteLater();
  }
}


#include "moc_AbstractTool.cpp"
