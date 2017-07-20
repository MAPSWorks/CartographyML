#include "HillshadeView.h"

#include <cmath>

#include <QSGSimpleTextureNode>
#include <QQuickWindow>

#include "HeightMap.h"
#include "Algorithms/Hillshade.h"

using namespace TerrainML;

struct HillshadeView::Private
{
  HeightMap heightMap;
  bool update_map;
  QSGTexture* texture = nullptr;
  qreal altitude, azimuth;
};

HillshadeView::HillshadeView(QQuickItem* parent) : QQuickItem(parent), d(new Private)
{
  d->update_map = false;
  setFlag(QQuickItem::ItemHasContents);
}

HillshadeView::~HillshadeView()
{
  delete d;
}


void HillshadeView::setHeightMap(const HeightMap& _map)
{
  d->heightMap = _map;
  d->update_map = true;
  emit(heightMapChanged());
  update();
}

HeightMap HillshadeView::heightMap() const
{
  return d->heightMap;
}

qreal HillshadeView::azimuth() const
{
  return d->azimuth;
}

void HillshadeView::setAzimuth(qreal _azimuth)
{
  d->azimuth = _azimuth;
  emit(azimuthChanged());
  d->update_map = true;
  update();
}

qreal HillshadeView::altitude() const
{
  return d->altitude;
}

void HillshadeView::setAltitude(qreal _altitude)
{
  d->altitude = _altitude;
  emit(altitudeChanged());
  d->update_map = true;
  update();
}

QSGNode * HillshadeView::updatePaintNode(QSGNode* _oldNode, QQuickItem::UpdatePaintNodeData* _upnd)
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
    d->texture = window()->createTextureFromImage(Algorithms::hillshade(d->heightMap, d->altitude * M_PI / 180.0, d->azimuth * M_PI / 180.0 ));
    textureNode->setTexture(d->texture);
    d->update_map = false;
  }
  return textureNode;
}

#include "moc_HillshadeView.cpp"
