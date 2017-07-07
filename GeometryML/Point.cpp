#include "Point.h"

#include <QRectF>

#include "Geometry_p.h"

using namespace GeometryML;

struct Point::Private : Geometry::Private
{
  Private() : Geometry::Private(Geometry::Type::Point) {}
  
  qreal x = 0.0, y = 0.0, z = 0.0;
  Dimension dim = Dimension::Zero;
};

#define D static_cast<Private*>(d)

Point::Point(QObject* parent): Geometry(new Private, parent)
{
}

Point::Point(qreal _x, qreal _y, qreal _z, QObject* parent): Geometry(new Private, parent)
{
  D->dim = Dimension::Three;
  D->x = _x;
  D->y = _y;
  D->z = _z;
}

Point::Point(qreal _x, qreal _y, QObject* parent): Geometry(new Private, parent)
{
  D->dim = Dimension::Two;
  D->x = _x;
  D->y = _y;
}

Point::~Point()
{

}

GeometryML::Point::Dimension GeometryML::Point::dimension() const
{
  return D->dim;
}

#define UPDATE_DIMENSION(_dim_)   \
  if(Dimension::_dim_ != D->dim)  \
  {                               \
    D->dim = Dimension::_dim_;    \
    emit(dimensionChanged());     \
  }

qreal GeometryML::Point::x() const
{
  return D->x;
}

void GeometryML::Point::setX(qreal _x)
{
  if(_x != D->x)
  {
    D->x = _x;
    emit(xChanged());
    emit(geometryChanged());
  }
  UPDATE_DIMENSION(Two)
}

qreal GeometryML::Point::y() const
{
  return D->y;
}

void GeometryML::Point::setY(qreal _y)
{
  if(_y != D->y)
  {
    D->y = _y;
    emit(yChanged());
    emit(geometryChanged());
  }
  UPDATE_DIMENSION(Two)
}

qreal GeometryML::Point::z() const
{
  return D->z;
}

void GeometryML::Point::setZ(qreal _z)
{
  if(_z != D->z)
  {
    D->z = _z;
    emit(zChanged());
    emit(geometryChanged());
  }
  UPDATE_DIMENSION(Three)
}

QRectF Point::enveloppe() const
{
  QPointF pt = toPoint2D();
  return QRectF(pt, pt);
}

QPointF Point::toPoint2D() const
{
  return QPointF(D->x, D->y);
}

#include "moc_Point.cpp"
