#ifndef _GEOMETRYML_POINT_H_
#define _GEOMETRYML_POINT_H_

#include "Geometry.h"

namespace GeometryML
{
  class Point : public Geometry
  {
    Q_OBJECT
  public:
    enum class Dimension
    {
      Zero = 0, Two = 2, Three = 3
    };
    Q_ENUMS(Dimension)
  public:
    explicit Point(QObject* parent = 0);
    explicit Point(qreal _x, qreal _y, QObject* parent = 0);
    explicit Point(qreal _x, qreal _y, qreal _z, QObject* parent = 0);
    virtual ~Point();
  private:
    struct Private;
  };
}

#endif
