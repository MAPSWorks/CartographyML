#ifndef _TERRAINML_HILLSHADEVIEW_H_
#define _TERRAINML_HILLSHADEVIEW_H_

#include <QQuickItem>

namespace TerrainML
{
  class HeightMap;
  class HillshadeView : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(TerrainML::HeightMap heightMap READ heightMap WRITE setHeightMap NOTIFY heightMapChanged)
    Q_PROPERTY(qreal altitude READ altitude WRITE setAltitude NOTIFY altitudeChanged)
    Q_PROPERTY(qreal azimuth READ azimuth WRITE setAzimuth NOTIFY azimuthChanged)
  public:
    HillshadeView(QQuickItem* parent = 0);
    virtual ~HillshadeView();
  public:
    HeightMap heightMap() const;
    void setHeightMap(const HeightMap& _map);
    qreal azimuth() const;
    void setAzimuth(qreal _azimuth);
    qreal altitude() const;
    void setAltitude(qreal _altitude);
  signals:
    void heightMapChanged();
    void azimuthChanged();
    void altitudeChanged();
  protected:
    QSGNode* updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd);
  private:
    struct Private;
    Private* const d;
  };
}

#endif
