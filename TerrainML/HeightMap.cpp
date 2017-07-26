#include "HeightMap.h"

#include <cmath>

#include <limits>

#include <QBuffer>
#include <QDataStream>
#include <QImage>
#include <QPointF>
#include <QRectF>
#include <QVector>
#include <QVector3D>

using namespace TerrainML;

struct HeightMap::Private : public QSharedData
{
  quint16 columns, rows;
  qreal verticalResolution, horizontalResolution;
  QPointF origin;
  QVector<float> altitudes;
};

TerrainML::HeightMap::HeightMap() : d(new Private)
{
  d->columns  = 0;
  d->rows     = 0;
  d->verticalResolution   = 0.0;
  d->horizontalResolution = 0.0;
}

HeightMap::HeightMap(qreal _width, qreal _height, qreal _resolution) : d(new Private)
{
  d->columns    = std::ceil(  _width / _resolution );
  d->rows       = std::ceil( _height / _resolution );
  d->horizontalResolution   = _width / d->columns;
  d->verticalResolution = _height / d->rows;
  d->altitudes.resize(d->columns * d->rows);
}

HeightMap::HeightMap(qreal _origin_x, qreal _origin_y, qreal _width, qreal _height, qreal  _resolution) : HeightMap(_width, _height, _resolution)
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
  QImage img(d->rows, d->columns, QImage::Format_Grayscale8);
  
  const QPair<float, float> mm = minmax();
  const float coef = 255.0 / (mm.second - mm.first);

  for(int y = 0; y < d->rows; ++y)
  {
    for(int x = 0; x < d->columns; ++x)
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
  stream << d->columns << d->rows;
  stream << (float)d->horizontalResolution << (float)d->verticalResolution;
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
  float hr, vr;
  stream >> hr >> vr;
  stream >> n;
  if(n != MAGIC_HEADER_END) return HeightMap();
  HeightMap hm;
  hm.d->columns = w;
  hm.d->rows    = h;
  hm.d->horizontalResolution = hr;
  hm.d->verticalResolution   = vr;
  hm.d->origin = QPointF(ox, oy);
  hm.d->altitudes.resize(w * h);
  for(int i = 0; i < hm.d->altitudes.size(); ++i)
  {
    stream >> hm.d->altitudes[i];
  }
  stream >> n;
  if(n != MAGIC_END) return HeightMap();
  return hm;
}

int HeightMap::columns() const
{
  return d->columns;
}

int HeightMap::rows() const
{
  return d->rows;
}

qreal HeightMap::horizontalResolution() const
{
  return d->horizontalResolution;
}

qreal HeightMap::verticalResolution() const
{
  return d->verticalResolution;
}

QPointF HeightMap::origin() const
{
  return d->origin;
}

QRectF HeightMap::boundingBox() const
{
  return QRectF(d->origin, QSizeF(d->columns * d->horizontalResolution, d->rows * d->verticalResolution));
}

void HeightMap::setAltitude(int _x, int _y, float _altitude)
{
  Q_ASSERT(_x >= 0 and _y >= 0 and _x < d->columns and _y < d->rows);
  d->altitudes[_y * d->columns + _x] = _altitude;
}

float HeightMap::altitude(int _x, int _y) const
{
  Q_ASSERT(_x >= 0 and _y >= 0 and _x < d->columns and _y < d->rows);
  return d->altitudes[_y * d->columns + _x];
}

float HeightMap::altitude(qreal _x, qreal _y) const
{
  const float left = std::floor(_x - d->origin.x());
  const float top = std::floor(_y - d->origin.y());
  const int ix = int(left / d->horizontalResolution);
  const int iy = int(top / d->verticalResolution);
  if(ix < 0 or iy < 0 or ix >= d->columns - 1 or iy >= d->rows - 1) return NAN;
  float alt1, alt2, alt3, alt4;
  const float cx = _x - left;
  const float cy = _y - top;
  
  alt1 = altitude(ix, iy);
  alt2 = altitude(ix + 1, iy);
  alt3 = altitude(ix, iy + 1);
  alt4 = altitude(ix + 1, iy + 1);
  
  return cx * cy * alt1 + (1.0f - cx) * cy * alt2 + cx * (1.0f - cy) * alt3 + (1.0f - cx) * (1.0f - cy) * alt4;
}

QVector3D HeightMap::normal(int _x, int _y) const
{
  const float l = _x == 0 ? altitude(_x, _y) : altitude(_x - 1, _y);
  const float r = _x == d->columns - 1 ? altitude(_x, _y) : altitude(_x + 1, _y);
  const float t = _y == 0 ? altitude(_x, _y) : altitude(_x, _y - 1);
  const float b = _y == d->rows - 1 ? altitude(_x, _y) : altitude(_x, _y + 1);
  
  QVector3D h(2.0, 0.0, r - l);
  QVector3D v(0.0, 2.0, b - t);

  return QVector3D::crossProduct(h, v).normalized();
}


float* HeightMap::data()
{
  return d->altitudes.data();
}

bool HeightMap::operator==(const HeightMap& _rhs) const
{
  return d->columns == _rhs.d->columns and d->rows == _rhs.d->rows
        and d->horizontalResolution == _rhs.d->horizontalResolution
        and d->verticalResolution   == _rhs.d->verticalResolution
        and d->origin == _rhs.d->origin and d->altitudes == _rhs.d->altitudes;
}
