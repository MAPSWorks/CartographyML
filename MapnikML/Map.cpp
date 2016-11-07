#include "Map.h"

using namespace MapnikML;

#include "Layer.h"

struct Map::Private
{
  QList<Layer*> layers;
};

Map::Map(QObject* parent): QObject(parent), d(new Private)
{

}

Map::~Map()
{

}

QQmlListProperty<Layer> Map::layers() const
{
  return QQmlListProperty<Layer>(const_cast<Map*>(this), d->layers);
}

#include "moc_Map.cpp"
