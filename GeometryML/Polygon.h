#ifndef _GEOMETRYML_POLYGON_H_
#define _GEOMETRYML_POLYGON_H_

#include "Geometry.h"

namespace GeometryML
{
  class LinearRing;
  class Polygon : public Geometry
  {
    Q_OBJECT
    Q_PROPERTY(GeometryML::LinearRing* exteriorRing READ exteriorRing WRITE setExteriorRing NOTIFY exteriorRingChanged)
    Q_PROPERTY(QList<QObject*> holes READ holesAsQObject NOTIFY holesChanged)
  public:
    explicit Polygon(QObject* parent = 0);
    explicit Polygon(LinearRing* _ring, QObject* parent = 0);
    virtual ~Polygon();
    void setExteriorRing(LinearRing* _ring);
    LinearRing* exteriorRing() const;
    void appendHole(LinearRing* _ring);
    QList<LinearRing*> holes() const;
    QRectF enveloppe() const override;
    Dimension dimension() const override;
  signals:
    void exteriorRingChanged();
    void holesChanged();
  private:
    QList<QObject*> holesAsQObject() const;
  private:
    struct Private;
  };
}

#endif
