#ifndef _TERRAINML_HEIGHTMAPWRAPPER_H_
#define _TERRAINML_HEIGHTMAPWRAPPER_H_
#include <QObject>

namespace TerrainML
{
  class HeightMap;
  class HeightMapWrapper : public QObject
  {
    Q_OBJECT
  public:
    Q_INVOKABLE TerrainML::HeightMap create(qreal _x, qreal _y, int _Width, int _height, qreal _resolution);
    Q_INVOKABLE QRectF boundingBox(const TerrainML::HeightMap& _map);
    Q_INVOKABLE TerrainML::HeightMap fill(const TerrainML::HeightMap& _map, float _altitude);
    Q_INVOKABLE TerrainML::HeightMap raise(const TerrainML::HeightMap& _map, qreal _x, qreal _y, float _altitude, float _radius, float _degree);
  };
}

#endif
