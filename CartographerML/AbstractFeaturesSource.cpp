#include "AbstractFeaturesSource.h"

#include <QRectF>

using namespace CartographerML;

AbstractFeaturesSource::AbstractFeaturesSource(QObject* parent): QObject(parent)
{

}

AbstractFeaturesSource::~AbstractFeaturesSource()
{

}

GeometryML::FeaturesSet* AbstractFeaturesSource::featuresAt(qreal _x, qreal _y, qreal _tol)
{
  return featuresAt(QPointF(_x, _y), _tol);
}

#include "moc_AbstractFeaturesSource.cpp"
