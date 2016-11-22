#include "initialise.h"

#include <QtQml>

#include <gdal/gdal.h>
#include <gdal/ogrsf_frmts.h>

#include <MapnikML/initialise.h>

#include "AbstractFeaturesSource.h"
#include "EditableDatasource.h"

#include "sources/GDALFeaturesSource.h"

void CartographerML::initialise()
{
  GDALAllRegister();
 
  MapnikML::initialise();

  const char* uri = "CartographerML";
  
  qmlRegisterUncreatableType<AbstractFeaturesSource>(uri, 1, 0, "AbstractFeaturesSource", "It is a virtual class");
  qmlRegisterType<GDALFeaturesSource>(uri, 1, 0, "GDALFeaturesSource");
  qmlRegisterType<EditableDatasource>(uri, 1, 0, "EditableDatasource");
}
