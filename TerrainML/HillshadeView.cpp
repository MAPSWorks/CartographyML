#include "HillshadeView.h"

#include <cmath>

#include <QImage>

#include "HeightMapBaseView_p.h"
#include "Algorithms/Hillshade.h"

using namespace TerrainML;

struct HillshadeView::Private : HeightMapBaseView::Private
{
  qreal altitude  = 45.0;
  qreal azimuth   = 0.0;
  qreal intensity = 255.0;
};

#define D static_cast<Private*>(d)

HillshadeView::HillshadeView(QQuickItem* parent) : HeightMapBaseView(new Private, parent)
{
}

HillshadeView::~HillshadeView()
{
}

qreal HillshadeView::azimuth() const
{
  return D->azimuth;
}

void HillshadeView::setAzimuth(qreal _azimuth)
{
  D->azimuth = _azimuth;
  emit(azimuthChanged());
  D->update_map = true;
  update();
}

qreal HillshadeView::altitude() const
{
  return D->altitude;
}

void HillshadeView::setAltitude(qreal _altitude)
{
  D->altitude = _altitude;
  emit(altitudeChanged());
  D->update_map = true;
  update();
}

qreal HillshadeView::intensity() const
{
  return D->intensity;
}

void HillshadeView::setIntensity(qreal _intensity)
{
  D->intensity = _intensity;
  emit(intensityChanged());
  D->update_map = true;
  update();
}


QImage HillshadeView::image() const
{
  return Algorithms::hillshade(heightMap(), D->altitude * M_PI / 180.0, D->azimuth * M_PI / 180.0, D->intensity );
}


#include "moc_HillshadeView.cpp"
