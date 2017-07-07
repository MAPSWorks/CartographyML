#include "Collection.h"

#include "Geometry_p.h"
#include "rect_utils_p.h"

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
    emit(elementsTypeChanged());
  } else if(D->elementsType != Type::Undefined and D->elementsType != _geom->type())
  {
    D->elementsType = Type::Undefined;
    emit(elementsTypeChanged());
  }
  D->elements.append(_geom);
  emit(elementsChanged());
}

QList< Geometry* > Collection::elements() const
{
  return D->elements;
}

QList<QObject *> Collection::elementsAsQObject()
{
  return *reinterpret_cast<const QList<QObject*>*>(&D->elements);
}

Geometry::Type Collection::elementsType() const
{
  return D->elementsType;
}

QRectF Collection::enveloppe() const
{
  if(D->elements.isEmpty()) return QRectF();
  QRectF r = D->elements.first()->enveloppe();
  for(Geometry* g : D->elements)
  {
    r = unite(r, g->enveloppe());
  }
  return r;
}

Geometry::Dimension Collection::dimension() const
{
  Dimension dim = Dimension::Zero;
  for(Geometry* g : D->elements)
  {
    dim = max(dim, g->dimension());
    if(dim == Dimension::Three) return dim;
  }
  return dim;
}

#include "moc_Collection.cpp"
