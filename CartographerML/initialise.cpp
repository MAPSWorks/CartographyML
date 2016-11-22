#include "initialise.h"

#include "gdal/gdal.h"
#include "gdal/ogrsf_frmts.h"

#include <MapnikML/initialise.h>

void CartographerML::initialise()
{
  GDALAllRegister();
 
  MapnikML::initialise();
  
}
