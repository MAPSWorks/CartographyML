class OGRFeature;
class OGRGeometry;
class OGRPoint;

#include <mapnik/feature.hpp>
#include <mapnik/geometry.hpp>

namespace GeometryML
{
  class Feature;
  class Geometry;
  class Point;
  
  // GDAL
  Feature* from_gdal(OGRFeature* _feature);
  Geometry* from_gdal(OGRGeometry* _geometry);
  Point* from_gdal(OGRPoint* _point);
  OGRFeature* to_gdal(const Feature* _feature);
  OGRGeometry* to_gdal(const Geometry* _geometry);

  // Mapnik
  mapnik::feature_ptr* to_mapnik(const Feature* _feature);
  mapnik::geometry::geometry<double> to_mapnik(const Geometry* _geometry);
}
