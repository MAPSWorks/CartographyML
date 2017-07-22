#include "HeightMapBaseView_p.h"

#include <QSGSimpleTextureNode>
#include <QQuickWindow>

using namespace TerrainML;

HeightMapBaseView::HeightMapBaseView(Private* _d, QQuickItem* parent) : QQuickItem(parent), d(_d)
{
  d->update_map = false;
  setFlag(QQuickItem::ItemHasContents);
}

HeightMapBaseView::HeightMapBaseView(QQuickItem* parent) : HeightMapBaseView(new Private, parent)
{
}

HeightMapBaseView::~HeightMapBaseView()
{
  delete d;
}


void HeightMapBaseView::setHeightMap(const HeightMap& _map)
{
  d->heightMap = _map;
  d->update_map = true;
  emit(heightMapChanged());
  update();
}

HeightMap HeightMapBaseView::heightMap() const
{
  return d->heightMap;
}

QSGNode * HeightMapBaseView::updatePaintNode(QSGNode* _oldNode, QQuickItem::UpdatePaintNodeData* _upnd)
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
    d->texture = window()->createTextureFromImage(image());
    textureNode->setTexture(d->texture);
    d->update_map = false;
  }
  return textureNode;
}

#include "moc_HeightMapBaseView.cpp"
