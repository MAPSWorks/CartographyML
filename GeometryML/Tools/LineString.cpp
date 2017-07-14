#include "LineString.h"

#include <cmath>

#include <QPointF>

#include "../LineString.h"
#include "../Point.h"

namespace GeometryML
{
  class LineString;
  namespace Tools
  {
    namespace LineString
    {
      namespace details
      {
        QPointF dir(const QPointF& _p1, const QPointF& _p2)
        {
          QPointF d = _p2 - _p1;
          qreal l = QPointF::dotProduct(d, d);
          return d / std::sqrt(l);
        }
      }
      QPointF tangeant(const GeometryML::LineString* _line, int _index)
      {
        if(_line->points().size() < 2) return QPointF();
        if(_index == 0)
        {
          return details::dir(_line->points()[0]->toPoint2D(), _line->points()[1]->toPoint2D());
        } else if(_index == _line->points().size() - 1) {
          return details::dir(_line->points()[_index - 1]->toPoint2D(), _line->points()[_index]->toPoint2D());
        } else {
          return details::dir(_line->points()[_index - 1]->toPoint2D(), _line->points()[_index + 1]->toPoint2D());
        }
      }
    }
  }
}

