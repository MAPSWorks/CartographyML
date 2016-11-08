#include "Layer.h"

#include "Datasource.h"

#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>

using namespace MapnikML;

struct Layer::Private
{
  QString name, srs;
  QStringList styles;
  Datasource* datasource  = nullptr;
  mapnik::Map* map        = nullptr;
  std::size_t layer_index = -1;
  bool has_layer() { return map and layer_index != std::size_t(-1); }
  mapnik::layer& layer() { return map->get_layer(layer_index); }
};

Layer::Layer(QObject* parent): MapElement(parent), d(new Private)
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
    emit(mapnikLayerChanged());
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
  emit(mapnikLayerChanged());
}

QString Layer::srs() const
{
  return d->srs;
}

void Layer::setSrs(const QString& _srs)
{
  d->srs = _srs;
  if(d->has_layer())
  {
    d->layer().set_srs(_srs.toStdString());
  }
  emit(srsChanged());
  emit(mapnikLayerChanged());
}

QStringList Layer::styles() const
{
  return d->styles;
}

void Layer::setStyles(const QStringList& _styles)
{
  d->styles = _styles;
  applyStyles();
  emit(stylesChanged());
  emit(mapnikLayerChanged());
}

void Layer::applyStyles()
{
  if(d->has_layer())
  {
    mapnik::layer& l = d->layer();
    l.styles().clear();
    for(const QString& style : d->styles)
    {
      l.add_style(style.toStdString());
    }
  }
}

void Layer::setMapnikLayer(mapnik::Map* _map, std::size_t _index)
{
  d->map = _map;
  d->layer_index = _index;
  d->layer().set_name(d->name.toStdString());
  d->layer().set_srs(d->srs.toStdString());
  updateDatasource();
  applyStyles();
}

#include "moc_Layer.cpp"
