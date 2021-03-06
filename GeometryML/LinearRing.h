#ifndef _GEOMETRYML_LINEARRING_H_
#define _GEOMETRYML_LINEARRING_H_

#include "LineString.h"

namespace GeometryML
{
  class Point;
  class LinearRing : public LineString
  {
    Q_OBJECT
  public:
    explicit LinearRing(QObject* parent = 0);
    explicit LinearRing(const QList<Point*>& _points, QObject* parent = 0);
    virtual ~LinearRing();
  public:
    QList<Point*> points() const override;    
  };
}

#endif
