#include "TestDatasource.h"

#include <QRectF>

#include <TerrainML/Algorithms/Terraforming.h>

TestDatasource::TestDatasource(QObject* _parent) : AbstractDatasource(_parent)
{
  m_maps.append(TerrainML::HeightMap(-2.0, -2.0, 2.0, 2.0, 0.01));
  m_maps.append(TerrainML::HeightMap( 0.0, -2.0, 2.0, 2.0, 0.01));
  m_maps.append(TerrainML::HeightMap(-2.0,  0.0, 2.0, 2.0, 0.01));
  m_maps.append(TerrainML::HeightMap( 0.0,  0.0, 2.0, 2.0, 0.01));
  for(TerrainML::HeightMap& hm : m_maps)
  {
    TerrainML::Algorithms::Terraforming::fill(&hm, 0.0);
    TerrainML::Algorithms::Terraforming::raise(&hm, QPointF(0.0, 0.0), 0.5, 1.0, 2.0);
  }
}

TestDatasource::~TestDatasource()
{
}

QList<TerrainML::HeightMap> TestDatasource::heightMaps(const QRectF & _rect) const
{
  QList<TerrainML::HeightMap> maps;
  
  for(const TerrainML::HeightMap& hm : m_maps)
  {
    if(hm.boundingBox().intersects(_rect))
    {
      maps.append(hm);
    }
  }

  return maps;
}
