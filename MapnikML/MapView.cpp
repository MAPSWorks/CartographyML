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
    m.set_background(mapnik::color(255, 255, 255));
    
    for(std::size_t i = 0; i < m.layer_count(); ++i)
    {
      m.get_layer(i).add_style("test");
    }

    mapnik::feature_type_style roads34_style;
    {
      mapnik::rule r;
      {
        mapnik::line_symbolizer line_sym;
        put(line_sym,mapnik::keys::stroke,mapnik::color(0,0,0));
        put(line_sym,mapnik::keys::stroke_linecap,mapnik::ROUND_CAP);
        put(line_sym,mapnik::keys::stroke_linejoin,mapnik::ROUND_JOIN);
        r.append(std::move(line_sym));
      }
      roads34_style.add_rule(std::move(r));
    }
    m.insert_style("test", std::move(roads34_style));

    m.zoom_all();
    
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

Map* MapView::getMap() const
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

void MapView::updateMap()
{
  d->updateMap = true;
  update();
}

#include "moc_MapView.cpp"

