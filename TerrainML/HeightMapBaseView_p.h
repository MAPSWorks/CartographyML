#include "HeightMapBaseView.h"

class QSGTexture;

#include "HeightMap.h"

namespace TerrainML
{
  struct HeightMapBaseView::Private
  {
    HeightMap heightMap;
    bool update_map;
    QSGTexture* texture = nullptr;
  };
}
