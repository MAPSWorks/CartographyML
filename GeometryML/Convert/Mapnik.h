
#include <mapnik/feature.hpp>
#include <mapnik/geometry.hpp>

namespace GeometryML
{
  class Feature;
  class Geometry;
  
  mapnik::feature_ptr toMapnik(const Feature* _feature);
  mapnik::geometry::geometry<double> toMapnik(const Geometry* _geometry);  
}

