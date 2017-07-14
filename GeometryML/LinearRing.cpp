#include "LinearRing.h"

#include "LineString_p.h"

using namespace GeometryML;

LinearRing::LinearRing(QObject* parent) : LineString(new LineString::Private(Type::LinearRing), parent)
{

}

LinearRing::LinearRing(const QList<Point*>& _points, QObject* parent)
  : LineString(_points, new LineString::Private(Type::LinearRing), parent)
{
}

LinearRing::~LinearRing()
{

}

QList<Point*> LinearRing::points() const
{
  QList<Point*> pts = LineString::points();
  if(not pts.isEmpty())
  {
    pts.append(pts.first());
  }
  return pts;
}

#include "moc_LinearRing.cpp"
