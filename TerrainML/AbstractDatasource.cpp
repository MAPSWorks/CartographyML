#include "AbstractDatasource.h"

#include <QRectF>
#include <QVariant>

#include "HeightMap.h"

using namespace TerrainML;

AbstractDatasource::AbstractDatasource(QObject* _parent) : QObject(_parent)
{
}

AbstractDatasource::~AbstractDatasource()
{
}

QVariant AbstractDatasource::heightMaps_(const QRectF& _rect) const
{
  QList<HeightMap> hms = heightMaps(_rect);
  QVariantList l;
  for(const HeightMap& hm : hms)
  {
    l.append(QVariant::fromValue(hm));
  }
  
  return l;
}

QVariant AbstractDatasource::heightMaps_(qreal _x, qreal _y, qreal _width, qreal _height) const
{
  return heightMaps_(QRectF(_x, _y, _width, _height));
}

#include "moc_AbstractDatasource.cpp"
