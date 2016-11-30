#include "initialise.h"

#include <QtQml>

#include "FeaturesSet.h"
#include "Feature.h"
#include "FeatureAttributesModel.h"
#include "LinearRing.h"
#include "Point.h"
#include "Polygon.h"

void initialise_GeometryML_qrc()
{
  Q_INIT_RESOURCE(GeometryML);
}

void GeometryML::initialise()
{
  initialise_GeometryML_qrc();
  
  const char* uri = "GeometryML";
  qmlRegisterType<FeaturesSet>();
  qmlRegisterType<Feature>();
  qmlRegisterUncreatableType<Geometry>    (uri, 1, 0, "Geometry", "Abstract class");
  qmlRegisterType<FeatureAttributesModel> (uri, 1, 0, "FeatureAttributesModel");
  qmlRegisterType<LinearRing>             (uri, 1, 0, "LinearRing");
  qmlRegisterType<LineString>             (uri, 1, 0, "LineString");
  qmlRegisterType<Point>                  (uri, 1, 0, "Point");
  qmlRegisterType<Polygon>                (uri, 1, 0, "Polygon");

  qmlRegisterType(QUrl("qrc:/qml/GeometryML/FeatureAttributesTable.qml"), uri, 1, 0, "FeatureAttributesTable");
}


