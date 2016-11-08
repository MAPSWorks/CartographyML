#include "Map.h"

#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>

#include <QColor>

#include "Layer.h"

using namespace MapnikML;

struct Map::Private
{
  QList<Layer*> layers;
  mapnik::Map map;
};

Map::Map(QObject* parent): QObject(parent), d(new Private)
{

}

Map::~Map()
{

}

QQmlListProperty<Layer> Map::layers() const
{
  return QQmlListProperty<Layer>(const_cast<Map*>(this), 0, Map::layer_append, Map::layer_count, Map::layer_at, Map::layer_clear);
}

const mapnik::Map& Map::map() const
{
  return d->map;
}

QString Map::srs() const
{
  return QString::fromStdString(d->map.srs());
}

void Map::setSrs(const QString& _srs)
{
  d->map.set_srs(_srs.toStdString());
  emit(srsChanged());
  emit(mapnikMapChanged());
}

QColor Map::backgroundColor() const
{
  if(d->map.background())
  {
    return QColor(d->map.background()->red(), d->map.background()->green(), d->map.background()->blue(), d->map.background()->alpha());
  } else {
    return QColor();
  }
}

void Map::setBackgroundColor(const QColor& _color)
{
  d->map.set_background(mapnik::color(_color.red(), _color.green(), _color.blue(), _color.alpha()));
  emit(backgroundColorChanged());
  emit(mapnikMapChanged());
}

// static layer_* functions

void Map::layer_append(QQmlListProperty<Layer>* _list, Layer* _layer)
{
  Map* m = reinterpret_cast<Map*>(_list->object);
  m->d->layers.append(_layer);
  m->d->map.add_layer(mapnik::layer("untitled"));
  _layer->setMapnikLayer(&m->d->map, m->d->map.layer_count() - 1);
  connect(_layer, SIGNAL(mapnikLayerChanged()), m, SIGNAL(mapnikMapChanged()));
  emit(m->mapnikMapChanged());
}

int Map::layer_count(QQmlListProperty<Layer>* _list)
{
  Map* m = reinterpret_cast<Map*>(_list->object);
  return m->d->layers.count();
}

Layer* Map::layer_at(QQmlListProperty<Layer>* _list, int _index)
{
  Map* m = reinterpret_cast<Map*>(_list->object);
  return m->d->layers[_index];
}

void Map::layer_clear(QQmlListProperty<Layer>* _list)
{
  Map* m = reinterpret_cast<Map*>(_list->object);
  for(Layer* l : m->d->layers)
  {
    l->setMapnikLayer(nullptr, -1);
    disconnect(l, SIGNAL(mapnikLayerChanged()), m, SIGNAL(mapnikMapChanged()));
  }
  m->d->layers.clear();
}

#include "moc_Map.cpp"
