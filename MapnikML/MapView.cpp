#include "MapView.h"

#include "Map.h"

using namespace MapnikML;

struct MapView::Private
{
  Map* map;
};

MapView::MapView(QQuickItem* parent): QQuickItem(parent), d(new Private)
{
  d->map = nullptr;
}

MapView::~MapView()
{

}

Map* MapView::getMap() const
{
  return d->map;
}

void MapView::setMap(Map* _map)
{
  d->map =_map;
}


#include "moc_MapView.cpp"

