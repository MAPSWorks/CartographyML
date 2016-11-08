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
  Map* map;
  mapnik::image_rgba8* buf = nullptr;
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
  qDebug() << "Updating map view";
  
  mapnik::Map m = d->map->map();
  m.set_background(mapnik::color(255, 255, 255));
  
  mapnik::box2d<double> extent;
  
  for(std::size_t i = 0; i < m.layer_count(); ++i)
  {
    extent.expand_to_include(m.get_layer(i).envelope());
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

  m.zoom_to_box(extent);
  
  if(not d->buf)
  {
    d->buf = new mapnik::image_rgba8(m.width(),m.height());
  }
  
  mapnik::agg_renderer<mapnik::image_rgba8> ren(m, *d->buf);
  ren.apply();

  QImage image((uchar*)d->buf->data(), m.width(), m.height(), QImage::Format_RGBA8888);

  QSGTexture* texture = window()->createTextureFromImage(image);

  // Just for debuging purposes:
  QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode*>(_oldNode);
  if (!textureNode) {
      textureNode = new QSGSimpleTextureNode;
  }
  textureNode->setTexture(texture);
  textureNode->setRect(0, 0, width(), height());
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
    disconnect(d->map, SIGNAL(mapnikMapChanged()), this, SLOT(update()));
  }
  d->map =_map;
  emit(mapChanged());
  update();
  connect(d->map, SIGNAL(mapnikMapChanged()), SLOT(update()));
}


#include "moc_MapView.cpp"

