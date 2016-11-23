#include "Geometry_p.h"

using namespace GeometryML;

Geometry::Geometry(Geometry::Private* _d, QObject* parent): QObject(parent), d(_d)
{

}

Geometry::~Geometry()
{
  delete d;
}

Geometry::Type Geometry::type() const
{
  return d->type;
}

#include "moc_Geometry.cpp"
