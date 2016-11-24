#include "LineString_p.h"

#include "Point.h"

using namespace GeometryML;

#define D static_cast<Private*>(d)

LineString::LineString(QObject* parent): LineString(new Private, parent)
{

}

LineString::LineString(LineString::Private* _d, QObject* parent): Geometry(_d, parent)
{

}

void LineString::append(Point* from_gdal)
{
  from_gdal->setParent(this);
  D->points.append(from_gdal);
}

QList<GeometryML::Point *> LineString::points() const
{
  return D->points;
}

QList<QObject *> LineString::pointsAsQObject() const
{
  return *reinterpret_cast<const QList<QObject*>*>(&D->points);
}


#include "moc_LineString.cpp"
