#ifndef _TERRAINML_HEIGHTMAPVIEW_H_
#define _TERRAINML_HEIGHTMAPVIEW_H_

#include "HeightMapBaseView.h"

namespace TerrainML
{
  class HeightMap;
  class HeightMapView : public HeightMapBaseView
  {
    Q_OBJECT
  public:
    HeightMapView(QQuickItem* parent = 0);
    virtual ~HeightMapView();
  protected:
    virtual QImage image() const;
  };
}

#endif
