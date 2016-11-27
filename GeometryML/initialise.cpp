#include "initialise.h"

#include <QtQml>

#include "FeaturesSet.h"
#include "Geometry.h"

void GeometryML::initialise()
{
  const char* uri = "GeometryML";
  qmlRegisterType<FeaturesSet>();
  qmlRegisterUncreatableType<Geometry>(uri, 1, 0, "Geometry", "For enums");
}


