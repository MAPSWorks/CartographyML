#include "HeightMapWrapper.h"

#include <QPointF>
#include <QRectF>

#include "HeightMap.h"
#include "Algorithms/Terraforming.h"

using namespace TerrainML;

HeightMap HeightMapWrapper::create(qreal _x, qreal _y, int _Width, int _height, qreal _resolution)
{
  return TerrainML::HeightMap(_x, _y, _Width, _height, _resolution);
}

QRectF HeightMapWrapper::boundingBox(const TerrainML::HeightMap& _map)
{
  return _map.boundingBox();
}

HeightMap HeightMapWrapper::fill(const HeightMap& _map, float _altitude)
{
  HeightMap m = _map;
  Algorithms::Terraforming::fill(&m, _altitude);
  return m;
}

HeightMap HeightMapWrapper::raise(const HeightMap& _map, qreal _x, qreal _y, float _altitude, float _radius, float _degree)
{
  HeightMap m = _map;
  Algorithms::Terraforming::raise(&m, QPointF(_x, _y), _altitude, _radius, _degree);
  return m;
}

TerrainML::HeightMap HeightMapWrapper::noise(const TerrainML::HeightMap& _map, qreal _min, qreal _max, qint32 _seed, float _scale)
{
  HeightMap m = _map;
  Algorithms::Terraforming::noise(&m, _min, _max, _seed, _scale);
  return m;
}


#include "moc_HeightMapWrapper.cpp"
