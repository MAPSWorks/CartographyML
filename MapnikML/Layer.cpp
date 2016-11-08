#include "Layer.h"

#include "Datasource.h"

#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>

using namespace MapnikML;

struct Layer::Private
{
  QString name;
  Datasource* datasource  = nullptr;
  mapnik::Map* map        = nullptr;
  std::size_t layer_index = -1;
  bool has_layer() { return map and layer_index != std::size_t(-1); }
  mapnik::layer& layer() { return map->get_layer(layer_index); }
};

Layer::Layer(QObject* parent): QObject(parent), d(new Private)
{
}

Layer::~Layer()
{
  delete d;
}

Datasource* Layer::datasource() const
{
  return d->datasource;
}

void Layer::setDatasource(Datasource* _datasource)
{
  if(d->datasource) d->datasource->deleteLater();
  d->datasource = _datasource;
  connect(d->datasource, SIGNAL(mapnikDatasourceChanged()), SLOT(updateDatasource()));
  updateDatasource();
  emit(datasourceChanged());
}

void Layer::updateDatasource()
{
  if(d->has_layer())
  {
    d->layer().set_datasource(d->datasource->mapnikDatasource());
  }
}

QString Layer::name() const
{
  return d->name;
}

void Layer::setName(const QString& _name)
{
  d->name = _name;
  if(d->has_layer())
  {
    d->layer().set_name(_name.toStdString());
  }
  emit(nameChanged());
}

void Layer::setMapnikLayer(mapnik::Map* _map, std::size_t _index)
{
  d->map = _map;
  d->layer_index = _index;
  d->layer().set_name(d->name.toStdString());
  updateDatasource();
}

#include "moc_Layer.cpp"
