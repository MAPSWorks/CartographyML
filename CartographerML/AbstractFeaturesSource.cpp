#include "AbstractFeaturesSource.h"

#include <QRectF>

using namespace CartographerML;

AbstractFeaturesSource::AbstractFeaturesSource(QObject* parent): QObject(parent)
{

}

AbstractFeaturesSource::~AbstractFeaturesSource()
{

}

#include "moc_AbstractFeaturesSource.cpp"