#include "LineString_p.h"

#include "Point.h"
#include "rect_utils_p.h"

using namespace GeometryML;

#define D static_cast<Private*>(d)

LineString::LineString(QObject* parent): LineString(new Private, parent)
{

}

LineString::LineString(LineString::Private* _d, QObject* parent): Geometry(_d, parent)
{

}

void LineString::append(const QPointF& _pt)
{
  D->points.append(new Point(_pt.x(), _pt.y(), this));
  emit(pointsChanged());
  emit(geometryChanged());
}

void LineString::append(Point* from_gdal)
{
  from_gdal->setParent(this);
  D->points.append(from_gdal);
  emit(pointsChanged());
  emit(geometryChanged());
}

QList<GeometryML::Point *> LineString::points() const
{
  return D->points;
}

QList<QObject *> LineString::pointsAsQObject() const
{
  return *reinterpret_cast<const QList<QObject*>*>(&D->points);
}

QRectF LineString::enveloppe() const
{
  if(D->points.isEmpty()) return QRectF();
  QRectF r(D->points.first()->toPoint2D(), D->points.first()->toPoint2D());
  for(Point* p : D->points)
  {
    QPointF pt = p->toPoint2D();
    r = unite(r, QRectF(pt, pt));
  }
  return r;
}

#include "moc_LineString.cpp"
