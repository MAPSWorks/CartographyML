#include "Feature.h"

#include <QVariantHash>

#include "Geometry.h"

using namespace GeometryML;

struct Feature::Private
{
  Geometry* geometry = nullptr;
  QVariantHash attributes;
};

Feature::Feature(QObject* parent): QObject(parent), d(new Private)
{

}

Feature::~Feature()
{

}

QVariant Feature::attribute(const QString& _name)
{
  return d->attributes.value(_name);
}

QVariantHash Feature::attributes() const
{
  return d->attributes;
}

Geometry* Feature::geometry() const
{
  return d->geometry;
}

void Feature::setAttribute(const QString& _name, const QVariant& _value)
{
  d->attributes[_name] = _value;
  emit(attributesChanged());
}

void Feature::setGeometry(Geometry* _geometry)
{
  delete d->geometry;
  d->geometry = _geometry;
  if(d->geometry)
  {
    d->geometry->setParent(this);
  }
  emit(geometryChanged());
}

#include "moc_Feature.cpp"
