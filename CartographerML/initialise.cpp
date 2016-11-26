#include "initialise.h"

#include <QtQml>

#include <gdal/gdal.h>
#include <gdal/ogrsf_frmts.h>

#include <MapnikML/initialise.h>

#include "AbstractFeaturesSource.h"
#include "EditableDatasource.h"
#include "Tool.h"
#include "ToolEvents.h"
#include "ToolController.h"

#include "sources/GDALFeaturesSource.h"

void initialise_CartographerML_qrc()
{
  Q_INIT_RESOURCE(CartographerML);
}

void CartographerML::initialise()
{
  initialise_CartographerML_qrc();
  GDALAllRegister();
  OGRRegisterAll();
 
  MapnikML::initialise();

  const char* uri = "CartographerML";
  qmlRegisterUncreatableType<AbstractFeaturesSource>(uri, 1, 0, "AbstractFeaturesSource", "It is a virtual class");
  qmlRegisterUncreatableType<AbstractTool>(uri, 1, 0, "AbstractTool", "It is a virtual class");
  qmlRegisterUncreatableType<MouseToolEvent>(uri, 1, 0, "MouseToolEvent", "Not useful");
  
  qmlRegisterType<GDALFeaturesSource> (uri, 1, 0, "GDALFeaturesSource");
  qmlRegisterType<EditableDatasource> (uri, 1, 0, "EditableDatasource");
  qmlRegisterType<Tool>               (uri, 1, 0, "Tool");
  qmlRegisterType<ToolController>     (uri, 1, 0, "ToolController");
  
  const char* uri_tools = "CartographerML.Tools";
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/NavigationTool.qml"), uri_tools, 1, 0, "NavigationTool");
}
