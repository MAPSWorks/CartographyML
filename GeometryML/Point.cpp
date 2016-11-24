#include "Point.h"

#include "Geometry_p.h"

using namespace GeometryML;

struct Point::Private : Geometry::Private
{
  Private() : Geometry::Private(Geometry::Type::Point) {}
  
  qreal x, y, z;
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

#include "moc_Point.cpp"
