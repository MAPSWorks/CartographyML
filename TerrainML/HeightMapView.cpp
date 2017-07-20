#include "HeightMapView.h"

#include <QSGSimpleTextureNode>
#include <QQuickWindow>

#include "HeightMap.h"

using namespace TerrainML;

struct HeightMapView::Private
{
  HeightMap heightMap;
  bool update_map;
  QSGTexture* texture = nullptr;
};

HeightMapView::HeightMapView(QQuickItem* parent) : QQuickItem(parent), d(new Private)
{
  d->update_map = false;
  setFlag(QQuickItem::ItemHasContents);
}

HeightMapView::~HeightMapView()
{
  delete d;
}


void HeightMapView::setHeightMap(const HeightMap& _map)
{
  d->heightMap = _map;
  d->update_map = true;
  emit(heightMapChanged());
  update();
}

HeightMap HeightMapView::heightMap() const
{
  return d->heightMap;
}

QSGNode * HeightMapView::updatePaintNode(QSGNode* _oldNode, QQuickItem::UpdatePaintNodeData* _upnd)
{
  QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode*>(_oldNode);
  if (!textureNode)
  {
    textureNode = new QSGSimpleTextureNode;
  }
  textureNode->setRect(0, 0, width(), height());

  if(d->update_map)
  {
    if(d->texture)
    {
      d->texture->deleteLater();
    }
    d->texture = window()->createTextureFromImage(d->heightMap.toImage());
    textureNode->setTexture(d->texture);
    d->update_map = false;
  }
  return textureNode;
}

#include "moc_HeightMapView.cpp"
