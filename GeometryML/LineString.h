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
    Q_INVOKABLE void append(const QPointF& _pt);
    Q_INVOKABLE void append(Point* _pt);
    virtual QList<Point*> points() const;
    QRectF enveloppe() const override;
    Dimension dimension() const override;
  private:
    QList<QObject*> pointsAsQObject() const;
  signals:
    void pointsChanged();    
  };
}

#endif
