#ifndef _TERRAINML_HEIGHTMAPBASEVIEW_H_
#define _TERRAINML_HEIGHTMAPBASEVIEW_H_

#include <QQuickItem>

namespace TerrainML
{
  class HeightMap;
  class HeightMapBaseView : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(TerrainML::HeightMap heightMap READ heightMap WRITE setHeightMap NOTIFY heightMapChanged)
  protected:
    struct Private;
    HeightMapBaseView(Private* _d, QQuickItem* parent = 0);
  public:
    HeightMapBaseView(QQuickItem* parent = 0);
    virtual ~HeightMapBaseView();
  public:
    HeightMap heightMap() const;
    void setHeightMap(const HeightMap& _map);
  public:
    Q_INVOKABLE QPointF viewToMap(const QPointF& _point);
    Q_INVOKABLE QPointF mapToView(const QPointF& _point);
  signals:
    void heightMapChanged();
  protected:
    virtual QImage image() const = 0;
    QSGNode* updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd);
  protected:
    Private* const d;
  };
}

#endif
