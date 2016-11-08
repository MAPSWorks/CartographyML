#include "initialise.h"

#include <QtQml>

#include <mapnik/datasource_cache.hpp>

#include "config.h"
#include "Datasource.h"
#include "Layer.h"
#include "Map.h"
#include "MapView.h"

void MapnikML::initialise()
{
  if(not mapnik::datasource_cache::instance().register_datasources(MAPNIK_INPUT_PLUGINS_DIR))
  {
    qWarning() << "Failed to register Mapnik datasources " << MAPNIK_INPUT_PLUGINS_DIR;
  }

  const char* uri = "MapnikML";
  qmlRegisterType<Datasource>(uri, 1, 0, "Datasource");
  qmlRegisterType<Layer     >(uri, 1, 0, "Layer");
  qmlRegisterType<Map       >(uri, 1, 0, "Map");
  qmlRegisterType<MapView   >(uri, 1, 0, "MapView");
}

