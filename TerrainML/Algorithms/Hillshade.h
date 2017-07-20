#include <QtGlobal>

class QImage;

namespace TerrainML
{
  class HeightMap;
  namespace Algorithms
  {
    QImage hillshade(const HeightMap& _map, qreal _altitude, qreal _azimuth);
  }
}
