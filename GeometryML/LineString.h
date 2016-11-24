#ifndef _GEOMETRYML_LINESEGMENT_H_
#define _GEOMETRYML_LINESEGMENT_H_

#include "Geometry.h"

namespace GeometryML
{
  class Point;
  class LineString : public Geometry
  {
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> points READ pointsAsQObject NOTIFY pointsChanged);
  protected:
    struct Private;
    explicit LineString(Private* _d, QObject* parent = 0);
  public:
    explicit LineString(QObject* parent = 0);
    void append(Point* from_gdal);
    QList<Point*> points() const;
  private:
    QList<QObject*> pointsAsQObject() const;
  signals:
    void pointsChanged();    
  };
}

#endif
