#include "Geometry.h"

namespace GeometryML
{
  struct Geometry::Private
  {
    Private(Type _type) : type(_type) {}
    const Type type;
  };
}
