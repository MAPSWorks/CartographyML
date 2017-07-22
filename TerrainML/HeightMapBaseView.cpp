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

QPointF HeightMapBaseView::viewToMap(const QPointF& _point)
{
  QRectF bb = d->heightMap.boundingBox();
  return QPointF( _point.x() * bb.width()  / width()  + bb.left(),
                  _point.y() * bb.height() / height() + bb.top());
}

QPointF HeightMapBaseView::mapToView(const QPointF& _point)
{
  QRectF bb = d->heightMap.boundingBox();
  return QPointF( (_point.x() - bb.left()) / bb.width()  * width(),
                  (_point.y() - bb.top() ) / bb.height() * height());
}

#include "moc_HeightMapBaseView.cpp"
