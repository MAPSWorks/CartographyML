#include "Terraforming.h"

#include <cmath>

#include <QRectF>

#include "../HeightMap.h"

namespace TerrainML
{
  namespace Algorithms
  {
    namespace Terraforming
    {
      void fill(HeightMap* map, float _altitude)
      {
        float* d = map->data();
        for(int i = 0; i < map->columns() * map->rows(); ++i)
        {
          d[i] = _altitude;
        }
      }
      void raise(HeightMap* map, const QPointF& _center, float _altitude, float _radius, float _degree)
      {
        QRectF bb = map->boundingBox();
        QRectF rb(_center.x() - _radius, _center.y() - _radius, 2 * _radius, 2 * _radius);
        QRectF ir = (bb & rb).translated(-map->origin());
        ir = QRectF(ir.left() / map->horizontalResolution(),
                    ir.top() / map->verticalResolution(),
                    ir.width() / map->horizontalResolution(),
                    ir.height() / map->verticalResolution());
        QRect iir = ir.toAlignedRect();
        QPointF offset = map->origin() - _center;
        for(int j = iir.top(); j <= iir.bottom(); ++j)
        {
          for(int i = iir.left(); i <= iir.right(); ++i)
          {
            QPointF pt_to_center = QPointF(i * map->horizontalResolution(), j * map->verticalResolution()) + offset;
            qreal dist = std::sqrt(QPointF::dotProduct(pt_to_center, pt_to_center));
            if(dist < _radius)
            {
              float offset = (1.0 - std::pow(std::sin(dist/_radius * M_PI * 0.5), _degree)) * _altitude;
              map->setAltitude(i, j, map->altitude(i, j) + offset);
            }
          }
        }
      }
    }
  }
}
