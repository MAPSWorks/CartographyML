#include "initialise.h"

#include <QtQml>

#include "FeaturesSet.h"
#include "Feature.h"
#include "Geometry.h"

void GeometryML::initialise()
{
  const char* uri = "GeometryML";
  qmlRegisterType<FeaturesSet>();
  qmlRegisterType<Feature>();
  qmlRegisterUncreatableType<Geometry>(uri, 1, 0, "Geometry", "For enums");
}


