#ifndef _MAPNIKML_MAPVIEW_H_
#define _MAPNIKML_MAPVIEW_H_

#include <QQuickItem>

namespace MapnikML
{
  class Map;
  class ViewTransform;
  class MapView : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(MapnikML::Map* map READ map WRITE setMap NOTIFY mapChanged)
    Q_PROPERTY(qreal zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(qreal panX READ panX WRITE setPanX NOTIFY panXChanged)
    Q_PROPERTY(qreal panY READ panY WRITE setPanY NOTIFY panYChanged)
    Q_PROPERTY(MapnikML::ViewTransform* viewTransform READ viewTransform NOTIFY viewTransformChanged)
  public:
    MapView(QQuickItem* parent = 0);
    virtual ~MapView();
  public:
    Map* map() const;
    void setMap(Map* _map);
    ViewTransform* viewTransform() const;
  public: // zoom and pan
    qreal zoom() const;
    Q_INVOKABLE void setZoom(qreal _zoom, bool update_pan = false);
    Q_INVOKABLE void zoomIn(qreal _factor);
    Q_INVOKABLE void zoomOut(qreal _factor);
    Q_INVOKABLE void zoomTo(qreal _pt_x, qreal _pt_y, qreal _zoom, qreal _pan_factor);
    Q_INVOKABLE void panTo(qreal _pt_x, qreal _pt_y, qreal _pan_factor = 1.0);
    qreal panX() const;
    void setPanX(qreal _zoom);
    qreal panY() const;
    void setPanY(qreal _zoom);
  protected:
    QSGNode* updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd);
  signals:
    void mapChanged();
    void zoomChanged();
    void panXChanged();
    void panYChanged();
    void viewTransformChanged();
  private slots:
    void updateMap();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
