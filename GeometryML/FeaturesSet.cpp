#include "FeaturesSet.h"

#include <QRectF>

#include "Feature.h"
#include "Geometry.h"

using namespace GeometryML;

struct FeaturesSet::Private
{
  QList<Feature*> features;
};

FeaturesSet::FeaturesSet(QObject* parent): QObject(parent), d(new Private)
{

}

FeaturesSet::FeaturesSet(const QList<Feature*>& _features, QObject* parent): QObject(parent), d(new Private)
{
  d->features = _features;
  for(Feature* f : d->features)
  {
    f->setParent(this);
  }
}

FeaturesSet::~FeaturesSet()
{
  delete d;
}

Feature* FeaturesSet::feature(int _index) const
{
  return d->features.at(_index);
}

QList<Feature*> FeaturesSet::features() const
{
  return d->features;
}

int FeaturesSet::featuresCount() const
{
  return d->features.size();
}

QList<QObject*> FeaturesSet::featuresAsQObject()
{
  return *reinterpret_cast<const QList<QObject*>*>(&d->features);
}

QRectF FeaturesSet::enveloppe() const
{
  if(d->features.isEmpty()) return QRectF();
  QRectF rect = d->features.first()->geometry()->enveloppe();
  for(Feature* f : d->features)
  {
    rect |= f->geometry()->enveloppe();
  }
  return rect;
}

#include "moc_FeaturesSet.cpp"
