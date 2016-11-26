#include "initialise.h"

#include <QtQml>

#include "FeaturesSet.h"

void GeometryML::initialise()
{
  const char* uri = "GeometryML";
  qmlRegisterUncreatableType<FeaturesSet>(uri, 1, 0, "FeaturesSet", "Not useful");
}


