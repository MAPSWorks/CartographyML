#ifndef _TERRAINML_HEIGHTMAPVIEW_H_
#define _TERRAINML_HEIGHTMAPVIEW_H_

#include <QQuickItem>

namespace TerrainML
{
  class HeightMap;
  class HeightMapView : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(TerrainML::HeightMap heightMap READ heightMap WRITE setHeightMap NOTIFY heightMapChanged)
  public:
    HeightMapView(QQuickItem* parent = 0);
    virtual ~HeightMapView();
  public:
    HeightMap heightMap() const;
    void setHeightMap(const HeightMap& _map);
  signals:
    void heightMapChanged();
  protected:
    QSGNode* updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd);
  private:
    struct Private;
    Private* const d;
  };
}

#endif
