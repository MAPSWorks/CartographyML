#include <QtGlobal>

class QPointF;

namespace TerrainML
{
  class HeightMap;
  namespace Algorithms
  {
    namespace Terraforming
    {
      void fill(HeightMap* map, float _altitude);
      void raise(HeightMap* map, const QPointF& _center, float _altitude, float _radius, float _degree);
      void noise(HeightMap* map, qreal _min, qreal _max, qint32 _seed, float _scale = 0.2);
    }
  }
}
