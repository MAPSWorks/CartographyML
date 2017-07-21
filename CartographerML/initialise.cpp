#include "initialise.h"

#include <QtQml>

#include <gdal/gdal.h>
#include <gdal/ogrsf_frmts.h>

#include <GeometryML/initialise.h>
#include <MapnikML/initialise.h>

#include "AbstractFeaturesSource.h"
#include "EditableDatasource.h"
#include "Tool.h"
#include "ToolEvents.h"
#include "ToolController.h"
#include "ProxyTool.h"

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
 
  GeometryML::initialise();
  MapnikML::initialise();

  const char* uri = "CartographerML";
  qmlRegisterUncreatableType<AbstractFeaturesSource>(uri, 1, 0, "AbstractFeaturesSource", "It is a virtual class");
  qmlRegisterUncreatableType<AbstractTool>(uri, 1, 0, "AbstractTool", "It is a virtual class");
  qmlRegisterUncreatableType<MouseToolEvent>(uri, 1, 0, "MouseToolEvent", "Not useful");
  qmlRegisterUncreatableType<WheelToolEvent>(uri, 1, 0, "WheelToolEvent", "Not useful");
  
  qmlRegisterType<GDALFeaturesSource> (uri, 1, 0, "GDALFeaturesSource");
  qmlRegisterType<EditableDatasource> (uri, 1, 0, "EditableDatasource");
  qmlRegisterType<Tool>               (uri, 1, 0, "Tool");
  qmlRegisterType<ToolController>     (uri, 1, 0, "ToolController");
  qmlRegisterType<ProxyTool>          (uri, 1, 0, "ProxyTool");
  
  const char* uri_tools = "CartographerML.Tools";
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/NavigationTool.qml"), uri_tools, 1, 0, "NavigationTool");
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/SelectionTool.qml"), uri_tools, 1, 0, "SelectionTool");
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/CreatePointFeatureTool.qml"), uri_tools, 1, 0, "CreatePointFeatureTool");
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/CreateLineStringGeometryTool.qml"), uri_tools, 1, 0, "CreateLineStringGeometryTool");
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/CreateLineStringFeatureTool.qml"), uri_tools, 1, 0, "CreateLineStringFeatureTool");
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Tools/CreatePolygonFeatureTool.qml"), uri_tools, 1, 0, "CreatePolygonFeatureTool");
  
  const char* uri_components = "Car11tographerML.Components";
  qmlRegisterType(QUrl("qrc:/qml/CartographerML/Components/SelectionBox.qml"), uri_components, 1, 0, "SelectionBox");
}
