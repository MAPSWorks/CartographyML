#include "FeaturesSet.h"

#include "Feature.h"

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
