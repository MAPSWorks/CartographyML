#include "Layer.h"

#include "Datasource.h"

#include <mapnik/layer.hpp>

using namespace MapnikML;

struct Layer::Private
{
  Datasource* datasource  = nullptr;
  mapnik::layer layer     = mapnik::layer("untitled");
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
  d->layer.set_datasource(d->datasource->mapnikDatasource());
}

QString Layer::name() const
{
  return QString::fromStdString(d->layer.name());
}

void Layer::setName(const QString& _name)
{
  d->layer.set_name(_name.toStdString());
  emit(nameChanged());
}

#include "moc_Layer.cpp"
