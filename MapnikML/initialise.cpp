#include "initialise.h"

#include <QtQml>

#include <mapnik/color.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/symbolizer.hpp>

#include "config.h"
#include "Datasource.h"
#include "Keys.h"
#include "Layer.h"
#include "MapnikEnums_p.h"
#include "Map.h"
#include "MapView.h"
#include "Rule.h"
#include "Utils.h"
#include "UtilsAttachedProperty.h"
#include "Style.h"
#include "Symbolizers.h"
#include "ViewTransform.h"

template<typename _T_>
void qmlRegisterSymbolizer(const char* _uri, int versionMajor, int versionMinor, const char* _qmlName)
{
  qmlRegisterType<MapnikML::Symbolizer<_T_>>(_uri, versionMajor, versionMinor, _qmlName);
}

template<mapnik::keys _T_, typename _TValue_>
void qmlRegisterKey(const char* _uri, int versionMajor, int versionMinor, const char* _qmlName)
{
  qmlRegisterType<MapnikML::Key<_T_, _TValue_>>(_uri, versionMajor, versionMinor, _qmlName);
}

void MapnikML::initialise()
{
  if(not mapnik::datasource_cache::instance().register_datasources(MAPNIK_INPUT_PLUGINS_DIR))
  {
    qWarning() << "Failed to register Mapnik datasources " << MAPNIK_INPUT_PLUGINS_DIR;
  }

  const char* uri = "MapnikML";
  qmlRegisterUncreatableType<MapnikEnums>(uri, 1, 0, "Mapnik", "Just for enums");
  qmlRegisterUncreatableType<AbstractDatasource>(uri, 1, 0, "AbstractDatasource", "Is a pure virtual class.");
  qmlRegisterType<ViewTransform>();
  qmlRegisterType<Datasource>(uri, 1, 0, "Datasource");
  qmlRegisterType<Layer     >(uri, 1, 0, "Layer");
  qmlRegisterType<Map       >(uri, 1, 0, "Map");
  qmlRegisterType<MapView   >(uri, 1, 0, "MapView");
  qmlRegisterType<Rule      >(uri, 1, 0, "Rule");
  qmlRegisterType<Style     >(uri, 1, 0, "Style");
  qmlRegisterType<Utils     >(uri, 1, 0, "Utils");
  
  qmlRegisterSymbolizer<mapnik::dot_symbolizer    >(uri, 1, 0, "DotSymbolizer");
  qmlRegisterSymbolizer<mapnik::line_symbolizer   >(uri, 1, 0, "LineSymbolizer");
  qmlRegisterSymbolizer<mapnik::point_symbolizer  >(uri, 1, 0, "PointSymbolizer");
  qmlRegisterSymbolizer<mapnik::polygon_symbolizer>(uri, 1, 0, "PolygonSymbolizer");
  qmlRegisterSymbolizer<mapnik::text_symbolizer   >(uri, 1, 0, "TextSymbolizer");
  
  qmlRegisterKey<mapnik::keys::width            , double                  >(uri, 1, 0, "WidthKey");
  qmlRegisterKey<mapnik::keys::height           , double                  >(uri, 1, 0, "HeightKey");
  qmlRegisterKey<mapnik::keys::fill             , mapnik::color           >(uri, 1, 0, "FillKey");
  qmlRegisterKey<mapnik::keys::stroke           , mapnik::color           >(uri, 1, 0, "StrokeKey");
  qmlRegisterKey<mapnik::keys::stroke_linecap   , mapnik::line_cap_enum   >(uri, 1, 0, "StrokeLinecapKey");
  qmlRegisterKey<mapnik::keys::stroke_linejoin  , mapnik::line_join_enum  >(uri, 1, 0, "StrokeLinejoinKey");
}

