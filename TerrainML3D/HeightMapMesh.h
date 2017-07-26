#ifndef _TERRAINML3D_HEIGHTMAPMESH_H_
#define _TERRAINML3D_HEIGHTMAPMESH_H_

#include <Qt3DRender/QGeometryRenderer>

namespace TerrainML
{
  class HeightMap;
}

namespace TerrainML3D
{

  class HeightMapMesh : public Qt3DRender::QGeometryRenderer
  {
    Q_OBJECT
    Q_PROPERTY(TerrainML::HeightMap heightMap READ heightMap WRITE setHeightMap NOTIFY heightMapChanged)
    Q_PROPERTY(qreal baseAltitude READ baseAltitude WRITE setBaseAltitude NOTIFY baseAltitudeChanged)
  public:
    HeightMapMesh(Qt3DCore::QNode *parent = nullptr);
    ~HeightMapMesh();
  public:
    TerrainML::HeightMap heightMap() const;
    void setHeightMap(const TerrainML::HeightMap& _map);
    qreal baseAltitude() const;
    void setBaseAltitude(qreal _baseAltitude);
  signals:
    void heightMapChanged();
    void baseAltitudeChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
