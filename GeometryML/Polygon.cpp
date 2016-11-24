#include "Polygon.h"

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

Polygon::~Polygon()
{

}

void Polygon::setExteriorRing(LinearRing* _ring)
{
  delete D->exterior_ring;
  D->exterior_ring = _ring;
  if(D->exterior_ring)
  {
    D->exterior_ring->setParent(this);
  }
}

void Polygon::appendHole(LinearRing* _ring)
{
  _ring->setParent(this);
  D->holes.append(_ring);
}

#include "moc_Polygon.cpp"
