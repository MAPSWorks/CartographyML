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
#include "ViewTransform.h"

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
  ViewTransform* viewTransform;
};

MapView::MapView(QQuickItem* parent): QQuickItem(parent), d(new Private)
{
  setFlag(QQuickItem::ItemHasContents);
  d->map = nullptr;
  d->viewTransform = new ViewTransform(width(), height(), QRectF(), this);
}

MapView::~MapView()
{

}

QSGNode* MapView::updatePaintNode(QSGNode *_oldNode, UpdatePaintNodeData *_upnd)
{
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
    m.pan(d->pan_x + width() * 0.5, d->pan_y + height() * 0.5);
    
    d->viewTransform->set(width(), height(), QRectF(QPointF(m.get_current_extent().minx(), m.get_current_extent().miny()), QPointF(m.get_current_extent().maxx(), m.get_current_extent().maxy())));
    emit(viewTransformChanged());
    
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

ViewTransform* MapView::viewTransform() const
{
  return d->viewTransform;
}

qreal MapView::zoom() const
{
  return d->zoom;
}

void MapView::zoomToFit()
{
  setPanX(0);
  setPanY(0);
  setZoom(1, false);
}

void MapView::setZoom(qreal _zoom, bool update_pan)
{
  if(_zoom <= 0)
  {
    qWarning() << "Got zoom level" << _zoom << ", expecting strictly positive number";
    return;
  }
  if(std::abs( _zoom - d->zoom) < 1e-3)
  {
    return;
  }
  _zoom = std::max(_zoom, 1.0);
  if(update_pan)
  {
    const qreal factor = _zoom / d->zoom;
    setPanX(d->pan_x * factor);
    setPanY(d->pan_y * factor);
  }
  d->zoom = _zoom;
  emit(zoomChanged());
  updateMap();
}

void MapView::zoomIn(qreal _factor)
{
  setZoom(d->zoom * _factor, true);
}

void MapView::zoomOut(qreal _factor)
{
  setZoom(d->zoom / _factor, true);
}

void MapView::panTo(qreal _pt_x, qreal _pt_y, qreal _pan_factor)
{
  setPanX(d->pan_x + _pan_factor * (_pt_x - 0.5 * width()));
  setPanY(d->pan_y + _pan_factor * (_pt_y - 0.5 * height()));
}

void MapView::zoomTo(qreal _pt_x, qreal _pt_y, qreal _zoom, qreal _pan_factor)
{
  panTo(_pt_x, _pt_y, _pan_factor);
  setZoom(_zoom, true);
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

