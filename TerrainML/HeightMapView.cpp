#include "HeightMapView.h"

#include <QDebug>
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

TerrainML::HeightMapView::HeightMapView(QQuickItem* parent) : QQuickItem(parent), d(new Private)
{
  d->update_map = false;
  setFlag(QQuickItem::ItemHasContents);
}

TerrainML::HeightMapView::~HeightMapView()
{
  delete d;
}


void TerrainML::HeightMapView::setHeightMap(const TerrainML::HeightMap& _map)
{
  qDebug() << "setHeightMap";
  d->heightMap = _map;
  d->update_map = true;
  emit(heightMapChanged());
  update();
}

TerrainML::HeightMap TerrainML::HeightMapView::heightMap() const
{
  return d->heightMap;
}

QSGNode * TerrainML::HeightMapView::updatePaintNode(QSGNode* _oldNode, QQuickItem::UpdatePaintNodeData* _upnd)
{
  QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode*>(_oldNode);
  if (!textureNode)
  {
    textureNode = new QSGSimpleTextureNode;
  }
  textureNode->setRect(0, 0, width(), height());
  qDebug() << d->update_map;
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
