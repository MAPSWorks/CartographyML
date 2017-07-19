#include "HeightMap.h"

#include <cmath>

#include <limits>

#include <QBuffer>
#include <QDataStream>
#include <QImage>
#include <QPointF>
#include <QRectF>
#include <QVector>

using namespace TerrainML;

struct HeightMap::Private : public QSharedData
{
  quint16 width, height;
  qreal resolution;
  QPointF origin;
  QVector<float> altitudes;
};

TerrainML::HeightMap::HeightMap() : d(new Private)
{
  d->width  = 0;
  d->height = 0;
  d->resolution = 0.0;
}

HeightMap::HeightMap(int _width, int _height, qreal _resolution) : d(new Private)
{
  d->width      = _width;
  d->height     = _height;
  d->resolution = _resolution;
  d->altitudes.resize(d->width * d->height);
}

HeightMap::HeightMap(qreal _origin_x, qreal _origin_y, int _width, int _height, qreal  _resolution) : HeightMap(_width, _height, _resolution)
{
  d->origin = QPointF(_origin_x, _origin_y);
}

HeightMap::HeightMap(const HeightMap& _rhs) : d(_rhs.d)
{
}

HeightMap& HeightMap::operator=(const HeightMap& _rhs)
{
  d = _rhs.d;
  return *this;
}

HeightMap::~HeightMap()
{
}

QPair<float, float> HeightMap::minmax() const
{
  float min = std::numeric_limits<float>::max();
  float max = -std::numeric_limits<float>::max();
  for(float a : d->altitudes)
  {
    min = std::min(min, a);
    max = std::max(max, a);
  }
  return QPair<float, float>(min, max);
}

QImage HeightMap::toImage() const
{
  QImage img(d->width, d->height, QImage::Format_Grayscale8);
  
  const QPair<float, float> mm = minmax();
  const float coef = 255.0 / (mm.second - mm.first);

  for(int y = 0; y < d->height; ++y)
  {
    for(int x = 0; x < d->width; ++x)
    {
      img.scanLine(y)[x] = coef * (altitude(x, y) - mm.first);
    }
  }
  
  return img;
}

QByteArray HeightMap::toByteArray() const
{
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  QDataStream stream(&buffer);
  stream << MAGIC_START;
  stream << (float)d->origin.x() << (float)d->origin.y();
  stream << d->width << d->height;
  stream << (float)d->resolution;
  stream << MAGIC_HEADER_END;
  for(int j = 0; j < d->altitudes.size(); ++j)
  {
    stream << d->altitudes[j];
  }
  stream << MAGIC_END;
  return buffer.buffer();
}

HeightMap HeightMap::fromByteArray(const QByteArray& _data)
{
  QBuffer buffer;
  buffer.setData(_data);
  buffer.open(QIODevice::ReadOnly);
  QDataStream stream(&buffer);
  quint16 n;
  stream >> n;
  if(n != MAGIC_START) return HeightMap();
  float ox, oy;
  stream >> ox >> oy;
  quint16 w, h;
  stream >> w >> h;
  float r;
  stream >> r;
  stream >> n;
  if(n != MAGIC_HEADER_END) return HeightMap();
  HeightMap hm(ox, oy, w, h, r);
  for(int i = 0; i < hm.d->altitudes.size(); ++i)
  {
    stream >> hm.d->altitudes[i];
  }
  stream >> n;
  if(n != MAGIC_END) return HeightMap();
  return hm;
}

int HeightMap::width() const
{
  return d->width;
}

int HeightMap::height() const
{
  return d->height;
}

qreal HeightMap::resolution() const
{
  return d->resolution;
}

QPointF HeightMap::origin() const
{
  return d->origin;
}

QRectF HeightMap::boundingBox() const
{
  return QRectF(d->origin, QSizeF(d->width * d->resolution, d->height * d->resolution));
}

void HeightMap::setAltitude(int _x, int _y, float _altitude)
{
  Q_ASSERT(_x >= 0 and _y >= 0 and _x < d->width and _y < d->height);
  d->altitudes[_y * d->width + _x] = _altitude;
}

float HeightMap::altitude(int _x, int _y) const
{
  Q_ASSERT(_x >= 0 and _y >= 0 and _x < d->width and _y < d->height);
  return d->altitudes[_y * d->width + _x];
}

float HeightMap::altitude(qreal _x, qreal _y) const
{
  const float left = std::floor(_x - d->origin.x());
  const float top = std::floor(_y - d->origin.y());
  const int ix = int(left / d->resolution);
  const int iy = int(top / d->resolution);
  if(ix < 0 or iy < 0 or ix >= d->width - 1 or iy >= d->height - 1) return NAN;
  float alt1, alt2, alt3, alt4;
  const float cx = _x - left;
  const float cy = _y - top;
  
  alt1 = altitude(ix, iy);
  alt2 = altitude(ix + 1, iy);
  alt3 = altitude(ix, iy + 1);
  alt4 = altitude(ix + 1, iy + 1);
  
  return cx * cy * alt1 + (1.0f - cx) * cy * alt2 + cx * (1.0f - cy) * alt3 + (1.0f - cx) * (1.0f - cy) * alt4;
}

float* HeightMap::data()
{
  return d->altitudes.data();
}

bool HeightMap::operator==(const HeightMap& _rhs) const
{
  return d->width == _rhs.d->width and d->height == _rhs.d->height and d->resolution == _rhs.d->resolution
        and d->origin == _rhs.d->origin and d->altitudes == _rhs.d->altitudes;
}
