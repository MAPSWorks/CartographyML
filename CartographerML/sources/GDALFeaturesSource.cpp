#include "GDALFeaturesSource.h"

#include <QUrl>
#include <QRectF>

#include <gdal/ogrsf_frmts.h>
#include <gdal/gdal_priv.h>

#include <GeometryML/Convert.h>

using namespace CartographerML;

struct GDALFeaturesSource::Private
{
  QUrl url;
  QString errorMessage;
  OGRDataSource* gdalDataset = nullptr;
};

GDALFeaturesSource::GDALFeaturesSource(QObject* parent): AbstractFeaturesSource(parent), d(new Private)
{

}

GDALFeaturesSource::~GDALFeaturesSource()
{
  delete d->gdalDataset;
  delete d;
}

QString GDALFeaturesSource::errorMessage() const
{
  return d->errorMessage;
}

QRectF GDALFeaturesSource::envelope()
{
  if(d->gdalDataset)
  {
    OGREnvelope env;
    d->gdalDataset->GetLayer(0)->GetExtent(&env);
    return QRectF(QPointF(env.MinX, env.MinY), QPointF(env.MaxX, env.MaxY));
  } else {
    return QRectF();
  }
}

QList<GeometryML::Feature*> GDALFeaturesSource::features(const QRectF& _rect)
{
  QList<GeometryML::Feature*> res;
  
  if(d->gdalDataset)
  {
    OGRLayer* layer = d->gdalDataset->GetLayer(0);
    layer->SetSpatialFilterRect(_rect.left(), _rect.top(), _rect.right(), _rect.bottom());
    layer->ResetReading();
    while(OGRFeature* ofeature = layer->GetNextFeature())
    {
      res.append(GeometryML::from_gdal(ofeature));
    }
  }
  return res;
}

QList<GeometryML::Feature*> GDALFeaturesSource::featuresAt(const QPointF& _rect, qreal _tol)
{
  QPointF tol(_tol, _tol);
  return features(QRectF(_rect - tol, _rect+tol));
}

bool GDALFeaturesSource::load()
{
  if(d->gdalDataset)
  {
    delete d->gdalDataset;
    d->gdalDataset = nullptr;
  }
  d->gdalDataset = OGRSFDriverRegistrar::Open( d->url.toLocalFile().toLatin1().constData(), TRUE );
  
  if(d->gdalDataset == nullptr)
  {
    d->errorMessage = "Failed to open file!";
    return false;
  }
  
  if(d->gdalDataset->GetLayerCount() != 1)
  {
    delete d->gdalDataset;
    d->gdalDataset = nullptr;
    d->errorMessage = "Invalid number of layers!";
    return false;
  }
  
  emit(featuresChanged());
  return true;
}

bool GDALFeaturesSource::save()
{
  if(d->gdalDataset)
  {
    if(d->gdalDataset->SyncToDisk() == 0)
    {
      return true;
    } else {
      d->errorMessage = "Failed to sync to disk.";
      return false;
    }
  } else {
    d->errorMessage = "No dataset.";
    return false;
  }
}

void GDALFeaturesSource::record(const GeometryML::Feature* _feature)
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
