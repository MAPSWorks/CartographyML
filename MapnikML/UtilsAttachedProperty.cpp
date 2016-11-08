#include "UtilsAttachedProperty.h"

#include "gdal/cpl_string.h"
#include "gdal/ogr_spatialref.h"

using namespace MapnikML;

UtilsAttachedProperty::UtilsAttachedProperty(QObject* _parent) : QObject(_parent)
{

}

UtilsAttachedProperty::~UtilsAttachedProperty()
{

}

QString UtilsAttachedProperty::wktToProj4(const QString& _srs)
{
  OGRSpatialReference osr;
  QByteArray srs_wkt_8bit = _srs.toLocal8Bit();
  char* srs_wkt = srs_wkt_8bit.data();
  osr.importFromWkt(&srs_wkt);
  char* srs_proj4 = nullptr;
  osr.exportToProj4(&srs_proj4);
  QString srs_qproj4 = QString::fromLocal8Bit(srs_proj4);
  CPLFree(srs_proj4);
  return srs_qproj4;
}

#include "moc_UtilsAttachedProperty.cpp"
