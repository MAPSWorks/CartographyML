#include "GDALFeaturesSource.h"

#include <QUrl>
#include <QRectF>

#include <gdal/ogrsf_frmts.h>
#include <gdal/gdal_priv.h>

#include <GeometryML/Convert/Gdal.h>
#include <GeometryML/FeaturesSet.h>
#include <GeometryML/Feature.h>

using namespace CartographerML;

struct GDALFeaturesSource::Private
{
  QUrl url;
  QString errorMessage;
#if GDAL_VERSION_MAJOR >= 2
  GDALDataset* gdalDataset = nullptr;
#else
  OGRDataset* gdalDataset = nullptr;
#endif
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
    OGRErr err = d->gdalDataset->GetLayer(0)->GetExtent(&env);
    Q_UNUSED(err);
    return QRectF(QPointF(env.MinX, env.MinY), QPointF(env.MaxX, env.MaxY));
  } else {
    return QRectF();
  }
}

GeometryML::FeaturesSet* GDALFeaturesSource::features(const QRectF& _rect)
{
  QList<GeometryML::Feature*> res;
  
  if(d->gdalDataset)
  {
    OGRLayer* layer = d->gdalDataset->GetLayer(0);
    layer->SetSpatialFilterRect(_rect.left(), _rect.top(), _rect.right(), _rect.bottom());
    layer->ResetReading();
    while(OGRFeature* ofeature = layer->GetNextFeature())
    {
      res.append(GeometryML::fromGdal(ofeature));
    }
  }
  return new GeometryML::FeaturesSet(res);
}

GeometryML::FeaturesSet* GDALFeaturesSource::featuresAt(const QPointF& _rect, qreal _tol)
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
#if GDAL_VERSION_MAJOR >= 2
  d->gdalDataset = (GDALDataset*) GDALOpenEx( d->url.toLocalFile().toLatin1().constData(), GDAL_OF_VECTOR | GDAL_OF_UPDATE, NULL, NULL, NULL );
#else
  d->gdalDataset = OGRSFDriverRegistrar::Open( d->url.toLocalFile().toLatin1().constData(), TRUE );
#endif
  
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
#if GDAL_VERSION_MAJOR >= 2
    d->gdalDataset->FlushCache();
    return true;
#else
    if(d->gdalDataset->SyncToDisk() == 0)
    {
      return true;
    } else {
      d->errorMessage = "Failed to sync to disk.";
      return false;
    }
#endif
  } else {
    d->errorMessage = "No dataset.";
    return false;
  }
}

bool GDALFeaturesSource::record(GeometryML::Feature* _feature)
{
  OGRErr err;
  OGRLayer* layer = d->gdalDataset->GetLayer(0);
  OGRFeature* ogr_feature = GeometryML::toGdal(_feature, layer->GetLayerDefn());
  if(_feature->id() != GeometryML::Feature::NO_ID)
  {
    err = layer->SetFeature(ogr_feature);
  } else {
    err = layer->CreateFeature(ogr_feature);
    _feature->setId(ogr_feature->GetFID());
  }
  delete ogr_feature;
  emit(featuresChanged());
  return err == OGRERR_NONE;
}

GeometryML::Feature* GDALFeaturesSource::createFeature()
{
  OGRLayer* layer = d->gdalDataset->GetLayer(0);
  return GeometryML::fromGdal(layer->GetLayerDefn());
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
