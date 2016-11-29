#include "Feature.h"

#include <QVariantHash>

#include "Geometry.h"

using namespace GeometryML;

struct Feature::Private
{
  qint64 id;
  Geometry* geometry = nullptr;
  QVariantHash attributes;
};

Feature::Feature(qint64 _id, QObject* parent): QObject(parent), d(new Private)
{
  d->id = _id;
}

Feature::~Feature()
{
  delete d;
}

qint64 GeometryML::Feature::id() const
{
  return d->id;
}

void GeometryML::Feature::setId(qint64 _id)
{
  d->id = _id;
  emit(idChanged());
}

QVariant Feature::attribute(const QString& _name) const
{
  return d->attributes.value(_name);
}

QVariantHash Feature::attributes() const
{
  return d->attributes;
}

QStringList Feature::attributeKeys() const
{
  return d->attributes.keys();
}

int Feature::attributesCount() const
{
  return d->attributes.size();
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
