#include "LineString.h"

#include "Geometry_p.h"

namespace GeometryML
{
  struct LineString::Private : Geometry::Private
  {
    Private(Type type) : Geometry::Private(type) {}
    Private() : Private(Geometry::Type::LineString) {}
    QList<Point*> points;
  };
}
