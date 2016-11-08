#ifndef _MAPNIKML_MAPVIEW_H_
#define _MAPNIKML_MAPVIEW_H_

#include <QQuickItem>

namespace MapnikML
{
  class Map;
  class MapView : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(MapnikML::Map* map READ getMap WRITE setMap NOTIFY mapChanged)
  public:
    MapView(QQuickItem* parent = 0);
    virtual ~MapView();
  public:
    Map* getMap() const;
    void setMap(Map* _map);
  protected:
    QSGNode* updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd);
  signals:
    void mapChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
