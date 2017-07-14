#include "Polygon.h"

#include <QPointF>

#include "../LinearRing.h"
#include "../LineString.h"
#include "../Point.h"
#include "../Polygon.h"

#include "LineString.h"

namespace GeometryML
{
  class LineString;
  class Polygon;
  namespace Tools
  {
    namespace Polygon
    {
      GeometryML::Polygon* from(const GeometryML::LineString* _line, const QList<qreal>& _thickness)
      {
        QList<GeometryML::Point*> points;
        for(int i = 0; i < _line->points().size(); ++i)
        {
          const Point* pt = _line->points()[i];
          QPointF pt_tangeant = LineString::tangeant(_line, i);
          QPointF pt_tangeant_ortho(-pt_tangeant.y(), pt_tangeant.x());
          QPointF pt_pt = pt->toPoint2D();
          QPointF p1 = pt_pt - _thickness[i] * pt_tangeant_ortho;
          QPointF p2 = pt_pt + _thickness[i] * pt_tangeant_ortho;
          switch(pt->dimension())
          {
            case Geometry::Dimension::Zero:
              break;
            case Geometry::Dimension::Two:
              points.append(new GeometryML::Point(p1));
              points.prepend(new GeometryML::Point(p2));
              break;
            case Geometry::Dimension::Three:
              points.append(new GeometryML::Point(p1, pt->z()));
              points.prepend(new GeometryML::Point(p2, pt->z()));
              break;
          }
        }
        return new GeometryML::Polygon(new LinearRing(points));
      }
      GeometryML::Polygon* from(const QList<QPointF>& _line, const QList<qreal>& _thickness)
      {
        GeometryML::LineString ls;
        std::for_each(_line.begin(), _line.end(), [&ls](const QPointF& _pt) { ls.append(_pt); });
        return from(&ls, _thickness);
      }
      GeometryML::Polygon* from(const QList<QPointF>& _line, qreal _thickness)
      {
        QList<qreal> thickness;
        for(int i = 0; i < _line.size(); ++i) thickness.append(_thickness);
        return from(_line, thickness);
      }
    }
  }
}
