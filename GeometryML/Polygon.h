#ifndef _GEOMETRYML_POLYGON_H_
#define _GEOMETRYML_POLYGON_H_

#include "Geometry.h"

namespace GeometryML
{
  class LinearRing;
  class Polygon : public Geometry
  {
    Q_OBJECT
  public:
    explicit Polygon(QObject* parent = 0);
    virtual ~Polygon();
    void setExteriorRing(LinearRing* _ring);
    void appendHole(LinearRing* _ring);
  private:
    struct Private;
  };
}

#endif
