#include "Polygon.h"

#include <QRectF>

#include "Geometry_p.h"
#include "LinearRing.h"

using namespace GeometryML;

struct Polygon::Private : public Geometry::Private
{
  Private() : Geometry::Private(Geometry::Type::Polygon)
  {}
  LinearRing* exterior_ring = nullptr;
  QList<LinearRing*> holes;
};

#define D static_cast<Private*>(d)

Polygon::Polygon(QObject* parent): Geometry(new Private, parent)
{

}

Polygon::Polygon(LinearRing* _ring, QObject* parent) : Polygon(parent)
{
  setExteriorRing(_ring);
}

Polygon::~Polygon()
{

}

void Polygon::setExteriorRing(LinearRing* _ring)
{
  if(D->exterior_ring)
  {
    disconnect(D->exterior_ring, SIGNAL(geometryChanged()), this, SIGNAL(geometryChanged()));
  }
  delete D->exterior_ring;
  D->exterior_ring = _ring;
  if(D->exterior_ring)
  {
    D->exterior_ring->setParent(this);
  }
  connect(_ring, SIGNAL(geometryChanged()), this, SIGNAL(geometryChanged()));
  emit(exteriorRingChanged());
  emit(geometryChanged());
}

LinearRing* Polygon::exteriorRing() const
{
  return D->exterior_ring;
}

void Polygon::appendHole(LinearRing* _ring)
{
  _ring->setParent(this);
  D->holes.append(_ring);
  connect(_ring, SIGNAL(geometryChanged()), this, SIGNAL(geometryChanged()));
  emit(holesChanged());
  emit(geometryChanged());
}

QList<LinearRing *> Polygon::holes() const
{
  return D->holes;
}

QList<QObject *> Polygon::holesAsQObject() const
{
  return *reinterpret_cast<const QList<QObject*>*>(&D->holes);
}

QRectF Polygon::enveloppe() const
{
  if(D->exterior_ring)
  {
    return D->exterior_ring->enveloppe();
  } else {
    return QRectF();
  }
}

GeometryML::Geometry::Dimension GeometryML::Polygon::dimension() const
{
  if(D->exterior_ring)
  {
    Dimension dim = D->exterior_ring->dimension();
    for(LinearRing* h : D->holes)
    {
      if(dim == Dimension::Three) return dim;
      dim = max(dim, h->dimension());
    }
    return dim;
  } else {
    return Dimension::Three;
  }
}

#include "moc_Polygon.cpp"
