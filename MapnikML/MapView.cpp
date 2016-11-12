#include "MapView.h"


#include <QDebug>
#include <QQuickWindow>
#include <QSGTexture>
#include <QSGSimpleTextureNode>

#include <mapnik/agg_renderer.hpp>
#include <mapnik/box2d.hpp>
#include <mapnik/color.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/rule.hpp>

#include "Map.h"

using namespace MapnikML;

struct MapView::Private
{
  bool updateMap = true;
  Map* map;
  mapnik::image_rgba8* buf = new mapnik::image_rgba8();
  QSGTexture* texture = nullptr;
  qreal zoom = 1.0;
  qreal pan_x = 0.0;
  qreal pan_y = 0.0;
};

MapView::MapView(QQuickItem* parent): QQuickItem(parent), d(new Private)
{
  setFlag(QQuickItem::ItemHasContents);
  d->map = nullptr;
}

MapView::~MapView()
{

}

QSGNode* MapView::updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd)
{
  qDebug() << "Updating map view " << d->updateMap;
  QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode*>(_oldNode);
  if (!textureNode) {
      textureNode = new QSGSimpleTextureNode;
  }
  // Stretch the texture node
  textureNode->setRect(0, 0, width(), height());
  if(width() != d->buf->width() or height() != d->buf->height())
  {
    delete d->buf;
    d->buf = nullptr;
    d->updateMap = true;
  }
  if(d->updateMap)
  {
    d->updateMap = false;
    
    mapnik::Map m = d->map->map();
    m.set_width(width());
    m.set_height(height());
    
    // Apply zoom
    m.zoom_all();
    m.zoom(1.0 / d->zoom);
    m.pan(d->pan_x + width() / 2, d->pan_y + height() / 2);
    
    // Render image
    if(not d->buf)
    {
      d->buf = new mapnik::image_rgba8(m.width(),m.height());
    }
    mapnik::agg_renderer<mapnik::image_rgba8> ren(m, *d->buf);
    ren.apply();

    // Update texture
    QImage image((uchar*)d->buf->data(), m.width(), m.height(), QImage::Format_RGBA8888);
    if(d->texture)
    {
      d->texture->deleteLater();
    }
    d->texture = window()->createTextureFromImage(image);
    textureNode->setTexture(d->texture);
  }
  return textureNode;
}

Map* MapView::map() const
{
  return d->map;
}

void MapView::setMap(Map* _map)
{
  if(d->map)
  {
    disconnect(d->map, SIGNAL(mapnikMapChanged()), this, SLOT(updateMap()));
  }
  d->map =_map;
  emit(mapChanged());
  update();
  connect(d->map, SIGNAL(mapnikMapChanged()), SLOT(updateMap()));
}

qreal MapView::zoom() const
{
  return d->zoom;
}

void MapView::setZoom(qreal _zoom)
{
  d->zoom = _zoom;
  if(d->zoom < 1.0)
  {
    d->zoom = 1.0;
  }
  emit(zoomChanged());
  updateMap();
}

qreal MapView::panX() const
{
  return d->pan_x;
}

void MapView::setPanX(qreal _zoom)
{
  d->pan_x = _zoom;
  emit(panXChanged());
  updateMap();
}

qreal MapView::panY() const
{
  return d->pan_y;
}

void MapView::setPanY(qreal _zoom)
{
  d->pan_y = _zoom;
  emit(panYChanged());
  updateMap();
}

void MapView::updateMap()
{
  d->updateMap = true;
  update();
}

#include "moc_MapView.cpp"

