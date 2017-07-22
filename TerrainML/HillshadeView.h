#ifndef _TERRAINML_HILLSHADEVIEW_H_
#define _TERRAINML_HILLSHADEVIEW_H_

#include "HeightMapBaseView.h"

namespace TerrainML
{
  class HeightMap;
  class HillshadeView : public HeightMapBaseView
  {
    Q_OBJECT
    Q_PROPERTY(qreal altitude READ altitude WRITE setAltitude NOTIFY altitudeChanged)
    Q_PROPERTY(qreal azimuth READ azimuth WRITE setAzimuth NOTIFY azimuthChanged)
  public:
    HillshadeView(QQuickItem* parent = 0);
    virtual ~HillshadeView();
  public:
    qreal azimuth() const;
    void setAzimuth(qreal _azimuth);
    qreal altitude() const;
    void setAltitude(qreal _altitude);
  signals:
    void azimuthChanged();
    void altitudeChanged();
  protected:
    virtual QImage image() const;
  private:
    struct Private;
  };
}

#endif
