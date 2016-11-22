#include "GDALFeaturesSource.h"

#include <QUrl>
#include <QRectF>

using namespace CartographerML;

struct GDALFeaturesSource::Private
{
  QUrl url;
  QString errorMessage;
};

GDALFeaturesSource::GDALFeaturesSource(QObject* parent): AbstractFeaturesSource(parent), d(new Private)
{

}

GDALFeaturesSource::~GDALFeaturesSource()
{
  delete d;
}

QString GDALFeaturesSource::errorMessage() const
{
  return d->errorMessage;
}

QRectF GDALFeaturesSource::envelope()
{
  return QRectF();
}

QList<Feature*> GDALFeaturesSource::features(const QRectF& _rect)
{
  QList<Feature*> res;
  return res;
}

QList<Feature*> GDALFeaturesSource::featuresAt(const QPointF& _rect)
{
  QList<Feature*> res;
  return res;
}

bool GDALFeaturesSource::load()
{
  d->errorMessage = "unimplemented";
  return false;
}

bool GDALFeaturesSource::save()
{
  d->errorMessage = "unimplemented";
  return false;
}

void GDALFeaturesSource::record(const Feature* _feature)
{

}

void GDALFeaturesSource::setUrl(const QUrl& _name)
{
  d->url = _name;
  emit(urlChanged());
}

QUrl GDALFeaturesSource::url() const
{
  return d->url;
}

#include "moc_GDALFeaturesSource.cpp"