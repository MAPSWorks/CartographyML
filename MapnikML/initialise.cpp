#include "initialise.h"

#include <QtQml>

#include "Datasource.h"
#include "Layer.h"
#include "Map.h"
#include "MapView.h"

void MapnikML::initialise()
{
  const char* uri = "MapnikML";
  qmlRegisterType<Datasource>(uri, 1, 0, "Datasource");
  qmlRegisterType<Layer     >(uri, 1, 0, "Layer");
  qmlRegisterType<Map       >(uri, 1, 0, "Map");
  qmlRegisterType<MapView   >(uri, 1, 0, "MapView");
}

