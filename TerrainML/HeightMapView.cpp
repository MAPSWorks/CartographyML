#include "HeightMapView.h"

#include <QImage>

#include "HeightMap.h"

using namespace TerrainML;

HeightMapView::HeightMapView(QQuickItem* parent) : HeightMapBaseView(parent)
{
}

HeightMapView::~HeightMapView()
{
}

QImage HeightMapView::image() const
{
  return heightMap().toImage();
}


#include "moc_HeightMapView.cpp"
