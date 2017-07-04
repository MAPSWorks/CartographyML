class OGRFeature;
class OGRFeatureDefn;
class OGRGeometry;
class OGRPoint;

class QByteArray;

namespace GeometryML
{
  class Feature;
  class Geometry;
  class Point;
  
  // GDAL
  Feature* fromGdal(OGRFeature* _feature);
  Geometry* fromGdal(OGRGeometry* _geometry);
  Point* fromGdal(OGRPoint* _point);
  Feature* fromGdal(OGRFeatureDefn* _definition);
  OGRFeature* toGdal(const Feature* _feature, OGRFeatureDefn* _definition);
  OGRGeometry* toGdal(const Geometry* _geometry);
  OGRPoint* toGdal(const Point* _point);
  
}
