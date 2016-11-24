#ifndef _GEOMETRYML_LINESEGMENT_H_
#define _GEOMETRYML_LINESEGMENT_H_

#include "Geometry.h"

namespace GeometryML
{
  class Point;
  class LineString : public Geometry
  {
    Q_OBJECT
  protected:
    struct Private;
    explicit LineString(Private* _d, QObject* parent = 0);
  public:
    explicit LineString(QObject* parent = 0);
    void append(Point* from_gdal);
  };
}

#endif
