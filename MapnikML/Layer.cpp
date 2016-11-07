#include "Layer.h"

#include "Datasource.h"

using namespace MapnikML;

struct Layer::Private
{
  Datasource* datasource;
};

Layer::Layer(QObject* parent): QObject(parent), d(new Private)
{

}

Layer::~Layer()
{

}

Datasource* Layer::datasource() const
{
  return d->datasource;
}

void Layer::setDatasource(Datasource* _datasource)
{
  d->datasource = _datasource;
  emit(datasourceChanged());
}


#include "moc_Layer.cpp"
