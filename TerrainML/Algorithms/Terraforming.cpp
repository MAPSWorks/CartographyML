#include "Terraforming.h"

#include <cmath>

#include <QRectF>

#include "../HeightMap.h"
#include "rand_p.h"
#include <QDebug>
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
    
      namespace details_noise
      {
        float fade(float t)
        {
          return ((2.0*std::abs(t)-3.0)*(t)*(t)+1.0);
        }     
      }
    
      void noise(HeightMap* map, qreal _min, qreal _max, qint32 _seed, float _scale)
      {
        for(int j = 0; j < map->rows(); ++j)
        {
          for(int i = 0; i < map->columns(); ++i)
          {
            const QPointF grid_coord_f = (QPointF(i * map->horizontalResolution(), j * map->verticalResolution()) + map->origin()) * _scale;
            const QPoint grid_coord(std::floor(grid_coord_f.x()), std::floor(grid_coord_f.y()));
            const QPointF weight = grid_coord_f - grid_coord; 
            using namespace details_noise;
            
            qreal r = fade(weight.x())    * ( fade(weight.y())   * TerrainML::Random::floatRandomAt(grid_coord.x(),   grid_coord.y()  , _seed)
                                            + fade(1-weight.y()) * TerrainML::Random::floatRandomAt(grid_coord.x(),   grid_coord.y()+1, _seed) )
                    + fade(1-weight.x())  * ( fade(weight.y())   * TerrainML::Random::floatRandomAt(grid_coord.x()+1, grid_coord.y()  , _seed)
                                            + fade(1-weight.y()) * TerrainML::Random::floatRandomAt(grid_coord.x()+1, grid_coord.y()+1, _seed) );
            map->setAltitude(i, j, map->altitude(i, j) + 0.25 * r * (_max - _min) + _min);
          }
        }
      }
    }
  }
}
