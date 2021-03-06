#ifndef _GEOMETRYML_POINT_H_
#define _GEOMETRYML_POINT_H_

#include "Geometry.h"

namespace GeometryML
{
  class Point : public Geometry
  {
    Q_OBJECT
  public:
    Q_ENUMS(Dimension)
    Q_PROPERTY(Dimension dimension READ dimension NOTIFY dimensionChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged)
  public:
    explicit Point(QObject* parent = 0);
    explicit Point(qreal _x, qreal _y, QObject* parent = 0);
    explicit Point(qreal _x, qreal _y, qreal _z, QObject* parent = 0);
    explicit Point(const QPointF& _pt, QObject* parent = 0);
    explicit Point(const QPointF& _pt, qreal _z, QObject* parent = 0);
    virtual ~Point();
    Dimension dimension() const override;
    qreal x() const;
    void setX(qreal _x);
    qreal y() const;
    void setY(qreal _y);
    qreal z() const;
    void setZ(qreal _z);
    virtual QRectF enveloppe() const;
    QPointF toPoint2D() const;
  signals:
    void dimensionChanged();
    void xChanged();
    void yChanged();
    void zChanged();
  private:
    struct Private;
  };
}

#endif
