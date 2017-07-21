#include <TerrainML/AbstractDatasource.h>

#include <TerrainML/HeightMap.h>

class TestDatasource : public TerrainML::AbstractDatasource
{
public:
  TestDatasource(QObject* _parent = nullptr);
  ~TestDatasource();
public:
  QList<TerrainML::HeightMap> heightMaps(const QRectF & _rect) const override;
private:
  QList<TerrainML::HeightMap> m_maps;
};
