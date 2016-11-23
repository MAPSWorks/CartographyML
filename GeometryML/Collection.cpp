#include "Collection.h"

#include "Geometry_p.h"

using namespace GeometryML;

struct Collection::Private : Geometry::Private
{
  Private() : Geometry::Private(Geometry::Type::Collection) {}

  QList<Geometry*> elements;
  Type elementsType;
};

#define D static_cast<Private*>(d)

Collection::Collection(QObject* parent): Geometry(new Private, parent)
{

}

Collection::~Collection()
{

}

void Collection::append(Geometry* _geom)
{
  if(D->elements.empty())
  {
    D->elementsType = _geom->type();
  } else if(D->elementsType != _geom->type())
  {
    D->elementsType = Type::Undefined;
  }
  D->elements.append(_geom);
}

QList< Geometry* > Collection::elements() const
{
  return D->elements;
}

