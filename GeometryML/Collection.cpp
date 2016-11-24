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

#include "moc_Collection.cpp"
