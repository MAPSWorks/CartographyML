#include "Map.h"

#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>

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

void Map::layer_append(QQmlListProperty<Layer>* _list, Layer* _layer)
{
  Map* m = reinterpret_cast<Map*>(_list->object);
  m->d->layers.append(_layer);
  m->d->map.add_layer(mapnik::layer("untitled"));
  _layer->setMapnikLayer(&m->d->map, m->d->map.layer_count() - 1);
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
  }
  m->d->layers.clear();
}


#include "moc_Map.cpp"
