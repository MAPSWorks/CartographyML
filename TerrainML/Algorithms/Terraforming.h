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
    }
  }
}
