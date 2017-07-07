#include "Geometry.h"

namespace GeometryML
{
  struct Geometry::Private
  {
    Private(Type _type) : type(_type) {}
    const Type type;
  };
  
  inline Geometry::Dimension Geometry::max(Geometry::Dimension _d1, Geometry::Dimension _d2)
  {
    switch(_d1)
    {
      case Dimension::Zero:
        return _d2;
      case Dimension::Two:
        switch(_d2)
        {
          case Dimension::Zero:
          case Dimension::Two:
            return _d1;
          case Dimension::Three:
            return _d2;
        }
      case Dimension::Three:
        return _d1;
    }
    qFatal("impossible");
  }
}
