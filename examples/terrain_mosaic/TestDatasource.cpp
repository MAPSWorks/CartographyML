#include "TestDatasource.h"

TestDatasource::TestDatasource(QObject* _parent) : AbstractDatasource(_parent)
{
}

TestDatasource::~TestDatasource()
{
}

QList<TerrainML::HeightMap> TestDatasource::heightMaps(const QRectF & _rect) const
{
  QList<TerrainML::HeightMap> maps;
  
  return maps;
}
