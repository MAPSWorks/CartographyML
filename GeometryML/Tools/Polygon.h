#include <QList>

class QPointF;

namespace GeometryML
{
  class LineString;
  class Polygon;
  namespace Tools
  {
    namespace Polygon
    {
      GeometryML::Polygon* from(const LineString* _line, const QList<qreal>& _thickness);
      GeometryML::Polygon* from(const QList<QPointF>& _line, const QList<qreal>& _thickness);
      GeometryML::Polygon* from(const QList<QPointF>& _line, qreal _thickness);
    }
  }
}
